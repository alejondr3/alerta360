#include "SistemaAlerta360.h"
#include "MapaVisual.h"
#include "UbicacionesCampus.h"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <limits>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace {
void exigir(bool condicion, const std::string& descripcion, std::ostream& out) {
    out << "  " << descripcion << " | esperado: OK | obtenido: " << (condicion ? "OK" : "FALLO") << '\n';
    if (!condicion) throw std::runtime_error(descripcion);
}
bool orden(const SistemaAlerta360& s, const int* esperados, int total) {
    int ids[128]{};
    if (total > 128 || s.proximos(ids, 128) != total) return false;
    for (int i = 0; i < total; ++i) if (ids[i] != esperados[i]) return false;
    return true;
}
bool rutaIgual(const Ruta& ruta, const int* nodos, int total, long long costo) {
    if (!ruta.existe || ruta.longitud != total || ruta.costo != costo) return false;
    for (int i = 0; i < total; ++i) if (ruta.nodos[i] != nodos[i]) return false;
    return true;
}
void ingresar(SistemaAlerta360& s, int id, int zona, std::ostream& log) {
    if (!s.registrar(id, "Falla tecnica de prueba", Tipo::RED, zona, log))
        throw std::runtime_error("No se pudo preparar incidencia " + std::to_string(id));
}
}

int ejecutarPruebas(std::ostream& out) {
    int aprobadas = 0, fallidas = 0;
    auto prueba = [&](const char* id, const char* titulo, auto cuerpo) {
        out << '\n' << id << " - " << titulo << '\n';
        try { cuerpo(); ++aprobadas; out << "Resultado: APROBADA\n"; }
        catch (const std::exception& e) { ++fallidas; out << "Resultado: FALLIDA - " << e.what() << '\n'; }
    };
    SistemaAlerta360 s;
    std::ostringstream log;
    prueba("T01", "Registrar 101 zona 3, 102 zona 7 y 103 zona 2", [&] {
        ingresar(s,101,3,log); ingresar(s,102,7,log); ingresar(s,103,2,log);
        for (int i = 0; i < 3; ++i) {
            const auto* d = s.buscar(101+i);
            exigir(d && d->estado == Estado::RECIBIDA && d->secuenciaIngreso == i+1,
                    "Registro y secuencia " + std::to_string(101+i), out);
        }
        exigir(s.validarConsistencia(), "Lista/BST/cola consistentes", out);
    });
    prueba("T02", "Clasificar FIFO con gravedades 5,5,3", [&] {
        exigir(s.clasificarSiguiente(5,log) && s.clasificarSiguiente(5,log)
            && s.clasificarSiguiente(3,log), "Tres clasificaciones", out);
        const int ids[] = {101,102,103};
        exigir(orden(s,ids,3) && s.buscar(103)->gravedad == 3, "Prioridad 101,102,103", out);
        exigir(s.validarConsistencia(), "Invariantes", out);
    });
    prueba("T03", "Cambiar gravedad de 103: 3 a 5", [&] {
        exigir(s.cambiarGravedad(103,5,log), "Cambio aceptado", out);
        const int ids[] = {101,102,103};
        exigir(orden(s,ids,3) && s.correcciones() == 1, "Antiguedad y una correccion en pila", out);
        exigir(s.validarConsistencia(), "Invariantes", out);
    });
    prueba("T04", "Deshacer cambio de 103", [&] {
        exigir(s.deshacerGravedad(log) && s.buscar(103)->gravedad == 3,
                "Gravedad restaurada a 3", out);
        const int ids[] = {101,102,103};
        exigir(orden(s,ids,3) && s.correcciones() == 0 && s.validarConsistencia(), "Heap y pila consistentes", out);
    });
    prueba("T05", "Asignar 101 con ruta de control", [&] {
        exigir(s.asignarSiguiente(log), "Asignacion aceptada", out);
        const int ruta[] = {0,2,1,3}; const int ids[] = {102,103};
        exigir(s.buscar(101)->estado == Estado::ASIGNADA && rutaIgual(s.buscar(101)->ruta,ruta,4,8),
                "Ruta 0->2->1->3, costo 8", out);
        exigir(orden(s,ids,2) && s.validarConsistencia(), "101 sale del heap", out);
    });
    prueba("T06", "Resolver 101 dos veces", [&] {
        exigir(s.resolver(101,log) && !s.resolver(101,log), "Primera aceptada y segunda rechazada", out);
        exigir(s.buscar(101)->estado == Estado::RESUELTA && s.cantidad() == 3
            && s.validarConsistencia(), "Historial conservado", out);
    });
    prueba("T07", "Cerrar 5-7 y 6-7; asignacion sin ruta", [&] {
        exigir(s.grafo().cerrar(5,7) && s.grafo().cerrar(6,7), "Vias cerradas", out);
        exigir(!s.asignarSiguiente(log), "Asignacion rechazada", out);
        const int ids[] = {102,103};
        exigir(s.buscar(102)->estado == Estado::PENDIENTE && !s.buscar(102)->ruta.existe
            && orden(s,ids,2) && s.validarConsistencia(), "102 permanece en heap sin ruta ficticia", out);
    });
    prueba("T08", "Restaurar 6-7 y asignar 102", [&] {
        exigir(s.grafo().restaurar(6,7) && s.asignarSiguiente(log), "Via restaurada y asignacion aceptada", out);
        const int ruta[] = {0,2,1,3,4,6,7};
        exigir(rutaIgual(s.buscar(102)->ruta,ruta,7,13) && s.validarConsistencia(),
                "Ruta 0->2->1->3->4->6->7, costo 13", out);
    });
    prueba("T09", "Cancelar 104 RECIBIDA y saltarla en cola", [&] {
        ingresar(s,104,1,log);
        exigir(s.cancelar(104,log) && !s.clasificarSiguiente(5,log), "104 ignorada al clasificar", out);
        const int ids[] = {103};
        exigir(orden(s,ids,1) && s.buscar(104)->estado == Estado::CANCELADA
            && s.validarConsistencia(), "104 nunca ingresa al heap", out);
    });
    prueba("T10", "ID inexistente, cancelar resuelta y heap vacio", [&] {
        exigir(!s.buscar(999) && !s.cancelar(101,log), "Busqueda y cancelacion rechazadas", out);
        exigir(s.asignarSiguiente(log) && !s.asignarSiguiente(log), "Ultima pendiente y heap vacio", out);
        exigir(s.validarConsistencia(), "Sin corrupcion", out);
    });
    prueba("T11", "Validaciones y transiciones prohibidas", [&] {
        SistemaAlerta360 x;
        exigir(!x.registrar(0,"Descripcion valida",Tipo::RED,1,log)
            && !x.registrar(1,"corta",Tipo::RED,1,log)
            && !x.registrar(1,std::string(121,'a'),Tipo::RED,1,log)
            && !x.registrar(1,std::string(10,' '),Tipo::RED,1,log)
            && !x.registrar(1,"Descripcion valida",static_cast<Tipo>(9),1,log)
            && !x.registrar(1,"Descripcion valida",Tipo::RED,0,log), "Datos invalidos rechazados", out);
        ingresar(x,1,1,log);
        exigir(!x.registrar(1,"Descripcion repetida",Tipo::RED,1,log) && x.cantidad() == 1,
                "ID duplicado rechazado", out);
        exigir(!x.resolver(1,log) && !x.cambiarGravedad(1,5,log)
            && !x.clasificarSiguiente(0,log) && !x.clasificarSiguiente(6,log),
                "RECIBIDA protegida; gravedades invalidas rechazadas", out);
        exigir(x.clasificarSiguiente(2,log) && !x.resolver(1,log)
            && x.asignarSiguiente(log) && !x.cancelar(1,log) && !x.cambiarGravedad(1,3,log)
            && x.resolver(1,log) && x.validarConsistencia(), "Transiciones validas unicamente", out);
    });
    prueba("T12", "Cancelar desde heap y corregir prioridades repetidas", [&] {
        SistemaAlerta360 x;
        for (int id = 1; id <= 5; ++id) { ingresar(x,id,2,log); x.clasificarSiguiente(id,log); }
        exigir(x.cancelar(3,log) && x.cancelar(5,log) && x.cancelar(1,log), "Eliminar medio, cima y hoja", out);
        exigir(x.cambiarGravedad(2,5,log) && x.cambiarGravedad(2,1,log)
            && x.cambiarGravedad(2,3,log), "Subidas y bajadas de prioridad", out);
        exigir(x.deshacerGravedad(log) && x.buscar(2)->gravedad == 1
            && x.deshacerGravedad(log) && x.buscar(2)->gravedad == 5
            && x.deshacerGravedad(log) && x.buscar(2)->gravedad == 2,
                "Tres deshacer en orden LIFO", out);
        const int ids[] = {4,2};
        exigir(orden(x,ids,2) && x.validarConsistencia(), "Heap sin duplicados", out);
    });
    prueba("T13", "Pila vacia y correcciones de incidencias que ya no estan pendientes", [&] {
        SistemaAlerta360 x;
        exigir(!x.deshacerGravedad(log), "Pila vacia rechazada", out);
        ingresar(x,1,2,log); x.clasificarSiguiente(2,log); x.cambiarGravedad(1,4,log);
        x.asignarSiguiente(log);
        exigir(!x.deshacerGravedad(log) && x.buscar(1)->gravedad == 4 && x.correcciones() == 0,
                "Correccion de ASIGNADA descartada", out);
        ingresar(x,2,2,log); x.clasificarSiguiente(1,log); x.cambiarGravedad(2,3,log); x.cancelar(2,log);
        exigir(!x.deshacerGravedad(log) && x.buscar(2)->gravedad == 3
            && x.correcciones() == 0 && x.validarConsistencia(), "Correccion de CANCELADA descartada", out);
    });
    prueba("T14", "Crecimiento del heap y consultas sin efectos secundarios", [&] {
        SistemaAlerta360 x;
        for (int id = 1; id <= 40; ++id) { ingresar(x,id,1,log); x.clasificarSiguiente(id%5+1,log); }
        const int esperados[] = {4,9,14,19,24}; int ids[5];
        exigir(x.proximos(ids,5) == 5, "Cinco resultados", out);
        for (int i = 0; i < 5; ++i) exigir(ids[i] == esperados[i], "Posicion " + std::to_string(i+1), out);
        std::ostringstream antes, despues;
        x.mostrarInformes(antes); x.mostrarInformes(despues);
        exigir(antes.str() == despues.str() && x.validarConsistencia(), "Informes repetibles sin mutacion", out);
        exigir(x.asignarSiguiente(log) && x.buscar(4)->estado == Estado::ASIGNADA
            && x.validarConsistencia(), "La siguiente asignada sigue siendo 4", out);
    });
    prueba("T15", "BST ascendente frente a insercion equilibrada", [&] {
        SistemaAlerta360 a,b;
        for (int i = 1; i <= 7; ++i) ingresar(a,i,1,log);
        const int ids[] = {4,2,6,1,3,5,7};
        for (int id : ids) ingresar(b,id,1,log);
        exigir(a.alturaBST() == 7 && b.alturaBST() == 3, "Alturas 7 y 3 niveles", out);
        for (int i = 1; i <= 7; ++i) exigir(a.buscar(i) && b.buscar(i), "Busqueda ID " + std::to_string(i), out);
        exigir(a.validarConsistencia() && b.validarConsistencia(), "Indices consistentes", out);
    });
    prueba("T16", "Origen a si mismo, aislamiento y validaciones del grafo", [&] {
        GrafoCampus g;
        const int origen[] = {0};
        exigir(rutaIgual(g.dijkstra(0,0),origen,1,0), "Ruta 0->0 con costo cero", out);
        exigir(!g.cambiarCosto(0,1,0) && !g.cambiarCosto(0,1,-1) && !g.cambiarCosto(1,1,2)
            && !g.cerrar(-1,2) && !g.restaurar(8,1) && !g.dijkstra(0,9).existe,
                "Entradas invalidas rechazadas", out);
        exigir(g.cerrar(0,1) && g.cerrar(0,2) && !g.dijkstra(0,7).existe,
                "Base completamente desconectada", out);
        exigir(g.restaurar(0,2) && g.costo(2,0) == 2 && g.dijkstra(0,7).costo == 13
            && g.validar(), "Restauracion simetrica y ruta recuperada", out);
    });
    prueba("T17", "Ruta historica independiente de cambios posteriores", [&] {
        SistemaAlerta360 x;
        ingresar(x,1,3,log); x.clasificarSiguiente(5,log); x.asignarSiguiente(log);
        exigir(x.grafo().cerrar(1,3) && x.grafo().cambiarCosto(0,2,100), "Mapa modificado", out);
        const int ruta[] = {0,2,1,3};
        exigir(rutaIgual(x.buscar(1)->ruta,ruta,4,8) && x.validarConsistencia(), "Ruta y costo asignados conservados", out);
    });
    prueba("T18", "Limpieza explicita, reutilizacion y destruccion repetida", [&] {
        for (int vuelta = 0; vuelta < 100; ++vuelta) {
            SistemaAlerta360 x;
            for (int id = 1; id <= 20; ++id) ingresar(x,id,1,log);
            for (int i = 0; i < 10; ++i) x.clasificarSiguiente(3,log);
            x.cambiarGravedad(1,5,log); x.cancelar(2,log);
            if (vuelta % 2 == 0) {
                x.cerrar(log); x.cerrar(log);
                if (!x.validarConsistencia() || x.cantidad() != 0) throw std::runtime_error("Limpieza inconsistente");
                ingresar(x,1,1,log);
                if (x.buscar(1)->secuenciaIngreso != 1) throw std::runtime_error("Contador no reiniciado");
            }
            if (!x.validarConsistencia()) throw std::runtime_error("Destruccion preparada incorrectamente");
        }
        exigir(true, "100 ciclos con lista, cola, BST, heap y pila; doble cierre seguro", out);
    });
    prueba("T19", "Empate defensivo de gravedad y secuencia en heap aislado", [&] {
        ListaIncidencias lista; IndiceBST indice; HeapPrioridad heap;
        for (int id = 3; id >= 1; --id) {
            auto& d = lista.agregar(id,"Prueba empate artificial",Tipo::RED,1,1);
            d.estado = Estado::PENDIENTE; d.gravedad = 5; indice.insertar(d); heap.insertar(d);
        }
        int ids[3];
        exigir(heap.proximos(ids,3) == 3 && ids[0] == 1 && ids[1] == 2 && ids[2] == 3,
                "ID ascendente como tercer criterio defensivo", out);
        for (int i = 1; i <= 3; ++i) {
            int id = 0;
            exigir(heap.extraer(id) && id == i && heap.validar(indice), "Extraer " + std::to_string(i), out);
        }
    });
    prueba("T20", "Costos grandes sin desbordamiento de int", [&] {
        GrafoCampus g;
        for (int a = 0; a < 8; ++a)
            for (int b = a+1; b < 8; ++b)
                if (g.costo(a,b) > 0) g.cambiarCosto(a,b,std::numeric_limits<int>::max());
        exigir(g.dijkstra(0,7).costo == 4LL * std::numeric_limits<int>::max()
            && g.validar(), "Costo 8589934588 almacenado en long long", out);
    });
    prueba("T21", "FIFO con varias canceladas y deshacer una sola entrada por intento", [&] {
        SistemaAlerta360 x;
        for (int i = 1; i <= 4; ++i) ingresar(x,i,1,log);
        x.cancelar(1,log); x.cancelar(2,log);
        exigir(x.siguienteClasificacion(log) == 3 && x.clasificarSiguiente(1,log)
            && x.siguienteClasificacion(log) == 4 && x.clasificarSiguiente(2,log), "Se saltan 1 y 2, se clasifican 3 y 4", out);
        x.cambiarGravedad(3,3,log); x.cambiarGravedad(4,4,log); x.cancelar(4,log);
        exigir(!x.deshacerGravedad(log) && x.correcciones() == 1 && x.buscar(3)->gravedad == 3,
                "Descarta solo la ultima correccion invalida", out);
        exigir(x.deshacerGravedad(log) && x.buscar(3)->gravedad == 1 && x.validarConsistencia(),
                "El siguiente intento restaura la correccion anterior", out);
    });
    prueba("T22", "Longitud UTF-8 y cambio de gravedad al mismo valor", [&] {
        SistemaAlerta360 x;
        std::string texto;
        for (int i = 0; i < 120; ++i) texto += "\xC3\xA1";
        exigir(longitudTexto(texto) == 120 && x.registrar(1,texto,Tipo::ENERGIA,1,log),
                "120 letras acentuadas aceptadas como 120 caracteres", out);
        texto += "\xC3\xA1";
        exigir(!x.registrar(2,texto,Tipo::ENERGIA,1,log), "121 caracteres rechazados", out);
        x.clasificarSiguiente(3,log);
        exigir(!x.cambiarGravedad(1,3,log) && x.correcciones() == 0 && x.validarConsistencia(),
                "Mismo valor no crea una correccion ficticia", out);
    });
    prueba("T23", "Ubicacion exacta independiente de la zona del grafo", [&] {
        SistemaAlerta360 x;
        ingresar(x,1,3,log);
        const auto* original=x.buscar(1);
        exigir(x.ubicarEnCampus(1,173,log) && x.buscar(1)==original
            && x.buscar(1)->ubicacionCampus==173 && x.buscar(1)->zona==3,
                "Biblioteca #173 vinculada sin copiar registro ni cambiar zona 3", out);
        exigir(!x.ubicarEnCampus(999,173,log) && !x.ubicarEnCampus(1,999,log)
            && !x.ubicarEnCampus(1,202,log) && x.buscar(1)->ubicacionCampus==173,
                "Rechaza ID inexistente, lugar invalido y punto sin coordenadas", out);
        exigir(x.ubicarEnCampus(1,0,log) && x.buscar(1)->ubicacionCampus==0
            && x.validarConsistencia(), "Quitar ubicacion no modifica estado ni estructuras", out);
    });
    prueba("T24", "Exportacion segura y sin efectos sobre el sistema", [&] {
        SistemaAlerta360 x;
        x.registrar(1,"Falla </script><script>alert(1)</script> & \\\"\\n",Tipo::RED,3,log);
        x.clasificarSiguiente(5,log); x.ubicarEnCampus(1,49,log);
        std::ostringstream datos;
        x.exportarDatosMapa(datos);
        exigir(datos.str().find("</script>")==std::string::npos
            && datos.str().find("\\u003c/script\\u003e")!=std::string::npos,
                "Descripcion no puede cerrar el bloque JSON ni ejecutar HTML", out);
        exigir(datos.str().find("\"ubicacion\":49")!=std::string::npos
            && x.buscar(1)->estado==Estado::PENDIENTE && x.validarConsistencia(),
                "Exportacion incluye lugar y preserva prioridades y estado", out);
        std::ostringstream catalogo;
        escribirUbicacionesCampusJSON(catalogo);
        exigir(buscarUbicacionCampus(173) && buscarUbicacionCampus(205)
            && !buscarUbicacionCampus(206) && catalogo.str().find("\"id\":205")!=std::string::npos,
                "Catalogo de 205 lugares disponible sin internet", out);
    });
    prueba("T25", "Archivo del mapa completo, reemplazo y error de escritura", [&] {
        namespace fs = std::filesystem;
        const auto dir=fs::temp_directory_path()/ ("alerta360-prueba-"+std::to_string(
            std::chrono::steady_clock::now().time_since_epoch().count()));
        fs::create_directory(dir);
        try {
            SistemaAlerta360 x;
            ingresar(x,1,3,log); x.ubicarEnCampus(1,49,log);
            std::string error;
            const auto archivo=dir/"mapa.html";
            exigir(guardarMapaVisual(x,archivo.string(),error), "Crear HTML autosuficiente", out);
            x.clasificarSiguiente(5,log);
            exigir(guardarMapaVisual(x,archivo.string(),error), "Reemplazar instantanea existente", out);
            std::ifstream entrada(archivo,std::ios::binary);
            std::ostringstream contenido;contenido<<entrada.rdbuf();entrada.close();
            exigir(contenido.str().find("\"estado\":\"PENDIENTE\"")!=std::string::npos
                && contenido.str().find("Campus UPSA")!=std::string::npos
                && contenido.str().find("id=\"imagen-campus\"")!=std::string::npos
                && contenido.str().find("data:image/jpeg;base64,/9j/")!=std::string::npos
                && contenido.str().find("id=\"imagen-limpia\"")!=std::string::npos
                && contenido.str().find("data:image/png;base64,iVBORw0KGgo")!=std::string::npos
                && contenido.str().size()>476136
                && contenido.str().find("</body></html>")!=std::string::npos,
                    "Archivo actualizado, con foto JPEG incorporada, plantilla y cierre completo", out);
            exigir(!guardarMapaVisual(x,(dir/"no-existe"/"mapa.html").string(),error)
                && !error.empty() && x.validarConsistencia(), "Error de carpeta no corrompe datos", out);
            exigir(!guardarMapaVisual(x,dir.string(),error) && fs::is_directory(dir),
                    "Nunca reemplaza ni elimina una carpeta con el mapa", out);
            fs::remove_all(dir);
        } catch (...) {fs::remove_all(dir);throw;}
    });
    prueba("T26", "Referencias 1-36 de la foto sin alterar estados ni prioridades", [&] {
        SistemaAlerta360 x;
        ingresar(x,1,3,log);x.clasificarSiguiente(5,log);
        exigir(x.ubicarEnPlano(1,26,log) && x.buscar(1)->referenciaPlano==26
            && x.buscar(1)->zona==3 && x.buscar(1)->estado==Estado::PENDIENTE,
                "Referencia 26 Biblioteca vinculada; estado y zona conservados", out);
        exigir(!x.ubicarEnPlano(1,37,log) && !x.ubicarEnPlano(999,26,log)
            && x.buscar(1)->referenciaPlano==26, "Numeros invalidos rechazados sin cambiar referencia", out);
        std::ostringstream datos;x.exportarDatosMapa(datos);
        exigir(datos.str().find("\"referenciaPlano\":26")!=std::string::npos,
                "Exportacion conserva numero impreso en la imagen", out);
        exigir(x.ubicarEnCampus(1,173,log) && x.buscar(1)->referenciaPlano==0
            && x.ubicarEnPlano(1,31,log) && x.buscar(1)->ubicacionCampus==0
            && x.ubicarEnPlano(1,0,log) && x.buscar(1)->referenciaPlano==0,
                "Cambiar de identificador o quitarlo evita referencias contradictorias", out);
        exigir(nombreReferenciaPlano(1) && nombreReferenciaPlano(36)
            && !nombreReferenciaPlano(0) && !nombreReferenciaPlano(37) && x.validarConsistencia(),
                "Catalogo de 36 referencias valido; heap consistente", out);
    });
    prueba("T27", "Registro de cuatro campos y clasificacion automatica", [&] {
        SistemaAlerta360 x;
        exigir(x.registrarAula(" d "," 203 ",501,5,log), "Bloque, aula, ID y gravedad aceptados", out);
        const auto* d=x.buscar(501);
        exigir(d && d->bloque=="D" && d->aula=="203" && d->gravedad==5
            && d->estado==Estado::PENDIENTE && d->zona==-1 && d->gravedadRegistro==0,
                "Registro PENDIENTE con campos guardados y ruta sin inventar", out);
        exigir(!x.asignarSiguiente(log) && x.buscar(501)->estado==Estado::PENDIENTE
            && !x.buscar(501)->ruta.existe, "Asignacion espera la configuracion del nuevo mapa", out);
        exigir(x.registrarAula("A","101",502,2,log)
            && x.registrarAula("B","202",503,5,log), "Otros registros con prioridad inicial", out);
        const int ids[]={501,503,502};
        exigir(orden(x,ids,3) && x.validarConsistencia(), "Heap por gravedad y antiguedad", out);
        std::ostringstream datos;x.exportarDatosMapa(datos);
        exigir(datos.str().find("\"bloque\":\"D\"")!=std::string::npos
            && datos.str().find("\"aula\":\"203\"")!=std::string::npos,
                "Mapa recibe bloque y aula sin inventar coordenadas", out);
    });
    prueba("T28", "Validaciones del registro simplificado sin datos parciales", [&] {
        SistemaAlerta360 x;
        exigir(!x.registrarAula(" ","101",1,3,log)
            && !x.registrarAula("A"," ",1,3,log)
            && !x.registrarAula(std::string(21,'A'),"101",1,3,log)
            && !x.registrarAula("A",std::string(31,'1'),1,3,log)
            && !x.registrarAula("A","10\n1",1,3,log)
            && !x.registrarAula("A","101",0,3,log)
            && !x.registrarAula("A","101",1,6,log)
            && x.cantidad()==0, "Rechaza campos invalidos antes de insertar", out);
        exigir(x.registrarAula("A","101",1,3,log)
            && !x.registrarAula("B","202",1,5,log)
            && x.buscar(1)->bloque=="A" && x.buscar(1)->gravedad==3,
                "ID duplicado no sobrescribe el reporte", out);
        exigir(x.cambiarGravedad(1,5,log) && x.deshacerGravedad(log)
            && x.buscar(1)->gravedad==3 && x.cancelar(1,log) && x.validarConsistencia(),
                "Correccion, deshacer y cancelacion siguen funcionando", out);
    });
    prueba("T29", "Registros nuevos respetan recibidas anteriores de la cola", [&] {
        SistemaAlerta360 x;
        ingresar(x,1,1,log);
        exigir(x.registrarAula("B","201",2,4,log)
            && x.buscar(2)->estado==Estado::RECIBIDA && x.buscar(2)->gravedadRegistro==4,
                "Guarda gravedad sin saltarse a una recibida anterior", out);
        exigir(x.cancelar(1,log) && x.registrarAula("C","301",3,2,log),
                "Omite cancelada anterior y continua clasificacion FIFO", out);
        const int ids[]={2,3};
        exigir(x.buscar(2)->estado==Estado::PENDIENTE && x.buscar(2)->gravedad==4
            && x.buscar(3)->estado==Estado::PENDIENTE && orden(x,ids,2)
            && x.validarConsistencia(), "Ambas gravedades preservadas sin duplicados", out);
    });
    prueba("T30", "Catalogo docente verificado por bloque y planta", [&] {
        int espacios=0,aulas=0,codigos=0;
        int bloques[5]{};
        for (int id=1;id<=205;++id) {
            const auto* p=buscarUbicacionCampus(id);
            if (!p || !p->docente) continue;
            ++espacios;
            const std::string nombre=p->nombre;
            if (nombre.find("Aula")!=std::string::npos) ++aulas;
            if (nombre.size()>4 && nombre[1]=='-') ++codigos;
            const std::string b=normalizarBloqueCampus(p->bloque);
            if (b.size()==1 && b[0]>='A' && b[0]<='E') ++bloques[b[0]-'A'];
        }
        exigir(espacios==122 && aulas==72 && codigos==121,
                "122 espacios docentes, 72 etiquetados Aula y 121 codigos de sala",out);
        exigir(bloques[0]==32 && bloques[1]==49 && bloques[2]==5 && bloques[3]==18 && bloques[4]==18,
                "Conteos oficiales A32 B49 C5 D18 E18",out);
        const auto* p=buscarAulaCampus(" Bloque d "," d-203 ");
        exigir(p && p->id==131 && p->docente && std::string(p->planta)=="2da. Planta",
                "D-203 se reconoce como Laboratorio de Redes de segunda planta",out);
        const auto* aulaA=buscarAulaCampus("A","108");
        const auto* aulaE=buscarAulaCampus("E","117");
        exigir(aulaA && aulaA->id==18 && aulaE && aulaE->id==70
            && !buscarAulaCampus("A","D-203") && !buscarAulaCampus("D","999")
            && !buscarAulaCampus("Central","101"),"No inventa coincidencias de aulas",out);
    });
    prueba("T31", "Vinculacion automatica del aula sin nuevas preguntas", [&] {
        SistemaAlerta360 x;
        exigir(x.registrarAula("Bloque d","D-203",901,5,log),"Cuatro campos suficientes",out);
        const auto* p=x.buscar(901);
        exigir(p && p->bloque=="D" && p->ubicacionCampus==131 && p->gravedad==5
            && p->estado==Estado::PENDIENTE && p->zona==-1,
                "Aula reconocida conserva gravedad y no inventa ruta",out);
        exigir(x.registrarAula("E","999",902,2,log) && x.buscar(902)->ubicacionCampus==0,
                "Aula no catalogada se conserva sin asignar otra sala",out);
        std::ostringstream datos,catalogo;
        x.exportarDatosMapa(datos);escribirUbicacionesCampusJSON(catalogo);
        exigir(datos.str().find("\"ubicacion\":131")!=std::string::npos
            && catalogo.str().find("\"docente\":true")!=std::string::npos
            && x.validarConsistencia(),"Vista recibe el aula y su clasificacion docente",out);
    });
    out << "\n=== Resumen: " << aprobadas << " aprobadas, " << fallidas << " fallidas ===\n";
    out << "\n--- Registro de operaciones y entradas de prueba ---\n" << log.str();
    return fallidas == 0 ? 0 : 1;
}
