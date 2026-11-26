#include "SistemaAlerta360.h"
#include "MapaVisual.h"
#include "UbicacionesCampus.h"
#include <limits>
#include <ostream>
#include <stdexcept>

namespace {
std::string limpiarCampo(const std::string& texto) {
    const auto inicio=texto.find_first_not_of(" \t\r\n");
    if (inicio==std::string::npos) return {};
    return texto.substr(inicio,texto.find_last_not_of(" \t\r\n")-inicio+1);
}
bool campoValido(const std::string& texto, std::size_t limite) {
    if (texto.empty() || longitudTexto(texto)>limite) return false;
    for (unsigned char c:texto) if (c<32 || c==127) return false;
    return true;
}
}

bool SistemaAlerta360::registrar(int id, const std::string& d, Tipo tipo, int zona, std::ostream& out) {
    bool contenido = false;
    for (char c : d) if (c != ' ' && c != '\t' && c != '\r' && c != '\n') contenido = true;
    const int t = static_cast<int>(tipo);
    if (id <= 0 || longitudTexto(d) < 10 || longitudTexto(d) > 120 || !contenido
        || t < 1 || t > 6 || zona < 1 || zona > 7) {
        out << "Datos invalidos: ID positivo, descripcion de 10 a 120 caracteres, tipo 1-6 y zona 1-7.\n";
        return false;
    }
    return crearRegistro(id,d,tipo,zona,out);
}
bool SistemaAlerta360::crearRegistro(int id, const std::string& d, Tipo tipo, int zona, std::ostream& out) {
    if (indice_.buscar(id)) { out << "El ID ya existe.\n"; return false; }
    if (secuencia_ == std::numeric_limits<long long>::max()) {
        out << "Contador de ingresos agotado.\n"; return false;
    }
    Incidencia& dato = lista_.agregar(id, d, tipo, zona, secuencia_ + 1);
    if (!indice_.insertar(dato)) throw std::logic_error("ID duplicado al insertar en BST.");
    cola_.encolar(id);
    ++secuencia_;
    out << "Registrada " << id << ": RECIBIDA, secuencia " << secuencia_ << ".\n";
    return true;
}
bool SistemaAlerta360::registrarAula(const std::string& bloque, const std::string& aula,
                                   int id, int gravedad, std::ostream& out) {
    std::string b=normalizarBloqueCampus(bloque);
    std::string a=limpiarCampo(aula);
    if (!campoValido(b,20) || !campoValido(a,30) || id<=0 || gravedad<1 || gravedad>5) {
        out << "Datos invalidos: bloque (1-20 caracteres), aula (1-30), ID positivo y gravedad 1-5.\n";
        return false;
    }
    for (char& c:b) if (c>='a' && c<='z') c=static_cast<char>(c-'a'+'A');
    const std::string descripcion="Incidencia en bloque "+b+", aula "+a;
    // -1: todavia no hay una correspondencia verificada con el grafo.
    // No se inventa que un bloque sea Biblioteca, Coliseo u otra zona antigua.
    if (!crearRegistro(id,descripcion,Tipo::OTRO,-1,out)) return false;
    Incidencia* dato=indice_.buscar(id);
    dato->bloque=b;
    dato->aula=a;
    dato->gravedadRegistro=gravedad;
    const auto* lugar=buscarAulaCampus(b,a);
    if (lugar) dato->ubicacionCampus=lugar->id;
    clasificarRegistrosConGravedad(out);
    out << "Registro listo: ID " << id << " | bloque " << b << " | aula " << a
        << " | gravedad " << gravedad << ".\n";
    if (lugar) out << "Aula reconocida: " << lugar->nombre << " | " << lugar->planta << ".\n";
    else out << "Aula no verificada en el catalogo; se conserva el bloque y aula ingresados.\n";
    return true;
}
void SistemaAlerta360::clasificarRegistrosConGravedad(std::ostream& out) {
    saltarCanceladas(out);
    int id=0;
    while (cola_.frente(id)) {
        const auto* dato=indice_.buscar(id);
        if (!dato || dato->gravedadRegistro==0) break;
        if (!clasificarSiguiente(dato->gravedadRegistro,out)) break;
        saltarCanceladas(out);
    }
}
void SistemaAlerta360::saltarCanceladas(std::ostream& out) {
    int id = 0;
    while (cola_.frente(id)) {
        const Incidencia* dato = indice_.buscar(id);
        if (!dato) throw std::logic_error("ID de cola inexistente en BST.");
        if (dato->estado != Estado::CANCELADA) break;
        cola_.desencolar(id);
        out << "Se ignora " << id << " porque esta CANCELADA.\n";
    }
}
int SistemaAlerta360::siguienteClasificacion(std::ostream& out) {
    saltarCanceladas(out);
    int id = 0;
    if (!cola_.frente(id)) { out << "No hay incidencias por clasificar.\n"; return 0; }
    return id;
}
bool SistemaAlerta360::clasificarSiguiente(int gravedad, std::ostream& out) {
    if (gravedad < 1 || gravedad > 5) { out << "Gravedad invalida (1-5).\n"; return false; }
    const int id = siguienteClasificacion(out);
    if (!id) return false;
    Incidencia* dato = indice_.buscar(id);
    if (dato->estado != Estado::RECIBIDA) throw std::logic_error("Estado invalido en cola.");
    dato->gravedad = gravedad;
    dato->estado = Estado::PENDIENTE;
    try { heap_.insertar(*dato); }
    catch (...) { dato->estado = Estado::RECIBIDA; dato->gravedad = 0; throw; }
    int retirado = 0;
    cola_.desencolar(retirado);
    dato->gravedadRegistro=0;
    out << "Clasificada " << id << ": PENDIENTE, gravedad " << gravedad << ".\n";
    return true;
}
bool SistemaAlerta360::cambiarGravedad(int id, int gravedad, std::ostream& out) {
    Incidencia* dato = indice_.buscar(id);
    if (!dato) { out << "ID inexistente.\n"; return false; }
    if (dato->estado != Estado::PENDIENTE) { out << "Solo se cambia gravedad de una PENDIENTE.\n"; return false; }
    if (gravedad < 1 || gravedad > 5) { out << "Gravedad invalida (1-5).\n"; return false; }
    if (gravedad == dato->gravedad) { out << "La gravedad ya tiene ese valor; no se guarda correccion.\n"; return false; }
    pila_.apilar({id, dato->gravedad});
    if (!heap_.cambiarGravedad(*dato, gravedad)) throw std::logic_error("Pendiente ausente en heap.");
    out << "Gravedad de " << id << " actualizada a " << gravedad << ".\n";
    return true;
}
bool SistemaAlerta360::deshacerGravedad(std::ostream& out) {
    Correccion c{};
    if (!pila_.desapilar(c)) { out << "Pila de deshacer vacia.\n"; return false; }
    Incidencia* dato = indice_.buscar(c.id);
    if (!dato || dato->estado != Estado::PENDIENTE) {
        out << "Correccion de " << c.id << " descartada: ";
        if (dato) out << "estado " << nombreEstado(dato->estado);
        else out << "ID inexistente";
        out << "; ya no esta PENDIENTE.\n";
        return false;
    }
    if (!heap_.cambiarGravedad(*dato, c.gravedadAnterior)) throw std::logic_error("Heap inconsistente al deshacer.");
    out << "Deshecho: " << c.id << " vuelve a gravedad " << c.gravedadAnterior << ".\n";
    return true;
}
bool SistemaAlerta360::asignarSiguiente(std::ostream& out) {
    int id = 0;
    if (!heap_.cima(id)) { out << "No hay incidencias PENDIENTES (heap vacio).\n"; return false; }
    Incidencia* dato = indice_.buscar(id);
    if (!dato || dato->estado != Estado::PENDIENTE) throw std::logic_error("Cima del heap invalida.");
    if (dato->zona==-1) {
        out << "Falta configurar la ruta del bloque " << dato->bloque
            << " con el nuevo mapa. La incidencia " << id << " permanece PENDIENTE.\n";
        return false;
    }
    const Ruta ruta = grafo_.dijkstra(0, dato->zona);
    if (!ruta.existe) {
        out << "Sin ruta a zona " << dato->zona << ": " << id << " permanece PENDIENTE en el heap.\n";
        return false;
    }
    heap_.extraer(id);
    dato->ruta = ruta;
    dato->estado = Estado::ASIGNADA;
    out << "Asignada " << id << ". Ruta: ";
    for (int i = 0; i < ruta.longitud; ++i) out << (i ? " -> " : "") << ruta.nodos[i];
    out << "; costo " << ruta.costo << " min.\n";
    return true;
}
bool SistemaAlerta360::resolver(int id, std::ostream& out) {
    Incidencia* dato = indice_.buscar(id);
    if (!dato) { out << "ID inexistente.\n"; return false; }
    if (dato->estado != Estado::ASIGNADA) { out << "Solo se resuelve una ASIGNADA; estado actual: " << nombreEstado(dato->estado) << ".\n"; return false; }
    dato->estado = Estado::RESUELTA;
    out << "Resuelta " << id << "; conservada en historial.\n";
    return true;
}
bool SistemaAlerta360::cancelar(int id, std::ostream& out) {
    Incidencia* dato = indice_.buscar(id);
    if (!dato) { out << "ID inexistente.\n"; return false; }
    if (dato->estado != Estado::RECIBIDA && dato->estado != Estado::PENDIENTE) {
        out << "No se cancela una " << nombreEstado(dato->estado) << ".\n"; return false;
    }
    if (dato->estado == Estado::PENDIENTE && !heap_.retirar(*dato))
        throw std::logic_error("Pendiente ausente en heap al cancelar.");
    dato->estado = Estado::CANCELADA;
    out << "Cancelada " << id << "; conservada en historial.\n";
    return true;
}
void SistemaAlerta360::mostrarFicha(const Incidencia& d, std::ostream& out) {
    out << "ID " << d.id << " | " << nombreEstado(d.estado) << " | gravedad " << d.gravedad
        << " | ingreso " << d.secuenciaIngreso << "\n  " << nombreTipo(d.tipo)
        << " | ";
    if (d.zona==-1) out << "ruta por configurar con el nuevo mapa";
    else out << "zona " << d.zona << " (" << GrafoCampus::nombreZona(d.zona) << ")";
    out << "\n  " << d.descripcion << '\n';
    if (!d.bloque.empty()) out << "  Bloque: " << d.bloque << " | Aula: " << d.aula << '\n';
    if (d.gravedadRegistro) out << "  Gravedad elegida: " << d.gravedadRegistro << " (en cola de clasificacion).\n";
    if (const auto* lugar = buscarUbicacionCampus(d.ubicacionCampus))
        out << "  Ubicacion UPSA #" << lugar->id << ": " << lugar->nombre << " | "
            << lugar->bloque << " | " << lugar->planta << '\n';
    if (const auto* referencia = nombreReferenciaPlano(d.referenciaPlano))
        out << "  Plano oficial #" << d.referenciaPlano << ": " << referencia << '\n';
    if (d.ruta.existe) {
        out << "  Ruta registrada: ";
        for (int i = 0; i < d.ruta.longitud; ++i) out << (i ? " -> " : "") << d.ruta.nodos[i];
        out << "; costo registrado " << d.ruta.costo << " min.\n";
    }
}
void SistemaAlerta360::mostrarIncidencia(int id, std::ostream& out) const {
    const Incidencia* dato = indice_.buscar(id);
    if (dato) mostrarFicha(*dato, out);
    else out << "ID inexistente.\n";
}
void SistemaAlerta360::mostrarInformes(std::ostream& out) const {
    int estados[5]{};
    out << "--- Historial hacia adelante ---\n";
    for (const auto* n = lista_.cabeza(); n; n = n->siguiente) {
        mostrarFicha(n->dato, out);
        ++estados[static_cast<int>(n->dato.estado)];
    }
    out << "--- Historial hacia atras (IDs) ---\n";
    for (const auto* n = lista_.cola(); n; n = n->anterior) out << n->dato.id << ' ';
    out << "\n--- BST inorden (IDs) ---\n";
    indice_.inorden([](const Incidencia& d, void* contexto) {
        *static_cast<std::ostream*>(contexto) << d.id << ' ';
    }, &out);
    out << "\nAltura BST (niveles): " << indice_.altura() << '\n';
    for (int i = 0; i < 5; ++i) out << nombreEstado(static_cast<Estado>(i)) << ": " << estados[i] << '\n';
    int ids[5];
    const int total = heap_.proximos(ids, 5);
    out << "Proximas " << total << " pendientes: ";
    for (int i = 0; i < total; ++i) out << ids[i] << (i + 1 == total ? "" : ", ");
    out << "\nEn cola: " << cola_.cantidad() << " (incluye canceladas sin descartar). Correcciones: "
        << pila_.cantidad() << ".\n";
}
bool SistemaAlerta360::validarConsistencia() const {
    if (!lista_.validar() || !indice_.validar() || !cola_.validar() || !pila_.validar()
        || !heap_.validar(indice_) || !grafo_.validar() || lista_.cantidad() != indice_.cantidad()) return false;
    int pendientes = 0;
    std::size_t enCola = 0;
    long long anterior = 0;
    for (const auto* n = lista_.cabeza(); n; n = n->siguiente) {
        const auto& d = n->dato;
        if (d.ubicacionCampus && !buscarUbicacionCampus(d.ubicacionCampus)) return false;
        if (d.referenciaPlano && !nombreReferenciaPlano(d.referenciaPlano)) return false;
        if (d.ubicacionCampus && d.referenciaPlano) return false;
        const bool zonaValida=(d.zona>=1 && d.zona<=7)
            || (d.zona==-1 && campoValido(d.bloque,20) && campoValido(d.aula,30));
        if (indice_.buscar(d.id) != &d || d.id <= 0 || !zonaValida
            || d.secuenciaIngreso <= anterior || d.secuenciaIngreso > secuencia_) return false;
        anterior = d.secuenciaIngreso;
        const int ocurrencias = cola_.ocurrencias(d.id);
        if (ocurrencias > 1) return false;
        enCola += static_cast<std::size_t>(ocurrencias);
        if (d.gravedadRegistro<0 || d.gravedadRegistro>5) return false;
        if (d.gravedadRegistro && d.estado!=Estado::RECIBIDA && d.estado!=Estado::CANCELADA) return false;
        if (d.estado == Estado::RECIBIDA) {
            if (d.gravedad != 0 || ocurrencias != 1) return false;
        } else if (d.estado != Estado::CANCELADA && (d.gravedad < 1 || d.gravedad > 5)) return false;
        if (d.estado == Estado::PENDIENTE) {
            ++pendientes;
            if (d.posicionHeap < 0) return false;
        } else if (d.posicionHeap != -1) return false;
        if (d.estado != Estado::RECIBIDA && d.estado != Estado::CANCELADA && ocurrencias != 0) return false;
        const bool asignada = d.estado == Estado::ASIGNADA || d.estado == Estado::RESUELTA;
        if (asignada != d.ruta.existe) return false;
        if (asignada && (d.ruta.longitud < 2 || d.ruta.longitud > 8 || d.ruta.costo <= 0
            || d.ruta.nodos[0] != 0 || d.ruta.nodos[d.ruta.longitud - 1] != d.zona)) return false;
    }
    return pendientes == heap_.cantidad() && enCola == cola_.cantidad();
}
void SistemaAlerta360::cerrar(std::ostream& out) {
    // Los indices no propietarios se vacian antes de destruir los registros.
    out << "Liberacion: heap=" << heap_.limpiar() << ", pila=" << pila_.limpiar()
        << ", cola=" << cola_.limpiar() << ", BST=" << indice_.limpiar()
        << ", lista=" << lista_.limpiar() << ".\n";
    secuencia_ = 0;
}

bool SistemaAlerta360::ubicarEnCampus(int id, int ubicacion, std::ostream& out) {
    Incidencia* dato = indice_.buscar(id);
    if (!dato) { out << "ID inexistente.\n"; return false; }
    const auto* lugar = buscarUbicacionCampus(ubicacion);
    if (ubicacion != 0 && (!lugar || !lugar->tienePosicion)) {
        out << "Ubicacion inexistente o sin posicion en el mapa oficial.\n";
        return false;
    }
    dato->ubicacionCampus = ubicacion;
    dato->referenciaPlano = 0;
    out << "Incidencia " << id << ": ";
    if (lugar) out << "ubicada en #" << lugar->id << " " << lugar->nombre;
    else out << "ubicacion exacta retirada";
    out << ". La zona de atencion sigue siendo " << dato->zona << ".\n";
    return true;
}
bool SistemaAlerta360::ubicarEnPlano(int id, int referencia, std::ostream& out) {
    Incidencia* dato = indice_.buscar(id);
    if (!dato) { out << "ID inexistente.\n"; return false; }
    const char* nombre = nombreReferenciaPlano(referencia);
    if (referencia != 0 && !nombre) { out << "Referencia del plano invalida (1-36).\n"; return false; }
    dato->referenciaPlano = referencia;
    dato->ubicacionCampus = 0;
    out << "Incidencia " << id << ": ";
    if (nombre) out << "plano oficial #" << referencia << " " << nombre;
    else out << "referencia del plano retirada";
    out << ". La zona de atencion sigue siendo " << dato->zona << ".\n";
    return true;
}
void SistemaAlerta360::exportarDatosMapa(std::ostream& out) const {
    out << "{\"incidencias\":[";
    bool primera = true;
    for (const auto* n = lista_.cabeza(); n; n = n->siguiente) {
        const auto& d = n->dato;
        if (!primera) out << ',';
        primera = false;
        out << "{\"id\":" << d.id << ",\"zona\":" << d.zona << ",\"ubicacion\":" << d.ubicacionCampus
            << ",\"referenciaPlano\":" << d.referenciaPlano
            << ",\"gravedad\":" << d.gravedad << ",\"secuencia\":" << d.secuenciaIngreso << ",\"estado\":";
        escribirCadenaJSON(out,nombreEstado(d.estado));
        out << ",\"descripcion\":"; escribirCadenaJSON(out,d.descripcion);
        out << ",\"bloque\":"; escribirCadenaJSON(out,d.bloque);
        out << ",\"aula\":"; escribirCadenaJSON(out,d.aula);
        out << ",\"tipo\":"; escribirCadenaJSON(out,nombreTipo(d.tipo));
        out << ",\"ruta\":[";
        for (int i = 0; i < d.ruta.longitud; ++i) out << (i ? "," : "") << d.ruta.nodos[i];
        out << "],\"costo\":" << d.ruta.costo << '}';
    }
    out << "],\"zonas\":[";
    for (int z = 0; z < 8; ++z) {
        out << (z ? "," : ""); escribirCadenaJSON(out,GrafoCampus::nombreZona(z));
    }
    out << "],\"aristas\":[";
    primera = true;
    for (int a = 0; a < 8; ++a) for (int b = a+1; b < 8; ++b) {
        const int costo = grafo_.costo(a,b);
        if (costo <= 0) continue;
        out << (primera ? "" : ",") << '[' << a << ',' << b << ',' << costo << ']';
        primera = false;
    }
    out << "]}";
}
