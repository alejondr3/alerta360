#include "SistemaAlerta360.h"
#include "MapaVisual.h"
#include "UbicacionesCampus.h"
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

int ejecutarPruebas(std::ostream&);

namespace {
struct FinEntrada {};

// Se consume una linea completa: evita bucles por failbit y acepta EOF limpio.
int leerEntero(const std::string& mensaje, int minimo, int maximo) {
    for (;;) {
        std::cout << mensaje;
        std::string linea;
        if (!std::getline(std::cin, linea)) throw FinEntrada{};
        std::size_t inicio = linea.find_first_not_of(" \t\r");
        std::size_t final = linea.find_last_not_of(" \t\r");
        if (inicio != std::string::npos) {
            try {
                const std::string valor = linea.substr(inicio, final - inicio + 1);
                std::size_t usados = 0;
                long long numero = std::stoll(valor, &usados);
                if (usados == valor.size() && numero >= minimo && numero <= maximo)
                    return static_cast<int>(numero);
            } catch (const std::invalid_argument&) {
            } catch (const std::out_of_range&) {}
        }
        std::cout << "Entrada invalida. Ingrese un entero entre " << minimo << " y " << maximo << ".\n";
    }
}
std::string leerDescripcion() {
    for (;;) {
        std::cout << "Descripcion (10-120 caracteres): ";
        std::string linea;
        if (!std::getline(std::cin, linea)) throw FinEntrada{};
        const auto primero = linea.find_first_not_of(" \t\r");
        const auto ultimo = linea.find_last_not_of(" \t\r");
        if (primero != std::string::npos) linea = linea.substr(primero, ultimo - primero + 1);
        if (primero != std::string::npos && longitudTexto(linea) >= 10 && longitudTexto(linea) <= 120) return linea;
        std::cout << "Descripcion invalida.\n";
    }
}
void gestionarRutas(GrafoCampus& grafo) {
    grafo.mostrar(std::cout);
    const int opcion = leerEntero("1 Cambiar costo/reabrir | 2 Cerrar | 3 Restaurar ultimo costo | 0 Volver: ", 0, 3);
    if (!opcion) return;
    const int a = leerEntero("Zona A (0-7): ", 0, 7);
    const int b = leerEntero("Zona B (0-7): ", 0, 7);
    bool ok = false;
    if (opcion == 1) {
        const int minutos = leerEntero("Costo positivo (minutos): ", 1, std::numeric_limits<int>::max());
        ok = grafo.cambiarCosto(a, b, minutos);
    } else if (opcion == 2) ok = grafo.cerrar(a, b);
    else ok = grafo.restaurar(a, b);
    std::cout << (ok ? "Via actualizada en ambos sentidos.\n" : "Operacion rechazada: verifique conexion, zonas y estado de la via.\n");
}
void menu() {
    std::cout << "\n=== ALERTA360 ===\n"
        "01 Registrar incidencia\n02 Clasificar siguiente\n03 Cambiar gravedad\n"
        "04 Deshacer gravedad\n05 Asignar siguiente\n06 Resolver\n07 Cancelar\n"
        "08 Buscar por ID\n09 Listados e indicadores\n10 Gestionar rutas\n"
        "11 Abrir mapa visual numerado\n12 Ubicar incidencia en el campus\n00 Salir\n";
}
}

int main(int argc, char* argv[]) {
    try {
        if (argc == 2 && std::string(argv[1]) == "--pruebas") return ejecutarPruebas(std::cout);
        const bool soloMapa = argc == 2 && std::string(argv[1]) == "--mapa";
        const bool inicioVisual = argc == 2 && std::string(argv[1]) == "--visual";
        if (argc != 1 && !soloMapa && !inicioVisual) { std::cerr << "Uso: alerta360 [--pruebas | --mapa | --visual]\n"; return 2; }
        SistemaAlerta360 sistema;
        const std::string archivoMapa = "mapa_alerta360.html";
        bool mapaActivo = false;
        auto actualizarMapa = [&]() {
            std::string error;
            if (guardarMapaVisual(sistema,archivoMapa,error)) return true;
            std::cerr << "No se pudo actualizar el mapa: " << error << '\n';
            return false;
        };
        if (soloMapa) {
            if (!actualizarMapa()) return 1;
            if (!abrirMapaVisual(archivoMapa)) std::cout << "Abra manualmente " << archivoMapa << ".\n";
            return 0;
        }
        if (inicioVisual && actualizarMapa()) {
            mapaActivo = true;
            if (!abrirMapaVisual(archivoMapa)) std::cout << "Abra manualmente " << archivoMapa << ".\n";
        }
        try {
            bool seguir = true;
            while (seguir) {
                menu();
                const int opcion = leerEntero("Opcion: ", 0, 12);
                switch (opcion) {
                    case 0: seguir = false; break;
                    case 1: {
                        const int id = leerEntero("ID positivo: ", 1, std::numeric_limits<int>::max());
                        if (sistema.buscar(id)) { std::cout << "El ID ya existe.\n"; break; }
                        std::cout << "1 Energia | 2 Red | 3 Equipo | 4 Clima | 5 Infraestructura | 6 Otro\n";
                        const auto tipo = static_cast<Tipo>(leerEntero("Tipo: ", 1, 6));
                        const std::string descripcion = leerDescripcion();
                        const int zona = leerEntero("Zona (1-7): ", 1, 7);
                        sistema.registrar(id, descripcion, tipo, zona, std::cout);
                        break;
                    }
                    case 2: {
                        const int id = sistema.siguienteClasificacion(std::cout);
                        if (id) {
                            sistema.mostrarIncidencia(id, std::cout);
                            const int gravedad = leerEntero("Gravedad (1-5, 5 es mayor urgencia): ", 1, 5);
                            sistema.clasificarSiguiente(gravedad, std::cout);
                        }
                        break;
                    }
                    case 3: {
                        const int id = leerEntero("ID: ", 1, std::numeric_limits<int>::max());
                        const int gravedad = leerEntero("Nueva gravedad (1-5): ", 1, 5);
                        sistema.cambiarGravedad(id, gravedad, std::cout);
                        break;
                    }
                    case 4: sistema.deshacerGravedad(std::cout); break;
                    case 5: sistema.asignarSiguiente(std::cout); break;
                    case 6: {
                        const int id = leerEntero("ID a resolver: ", 1, std::numeric_limits<int>::max());
                        sistema.resolver(id, std::cout); break;
                    }
                    case 7: {
                        const int id = leerEntero("ID a cancelar: ", 1, std::numeric_limits<int>::max());
                        sistema.cancelar(id, std::cout); break;
                    }
                    case 8: {
                        const int id = leerEntero("ID a buscar: ", 1, std::numeric_limits<int>::max());
                        sistema.mostrarIncidencia(id, std::cout); break;
                    }
                    case 9: sistema.mostrarInformes(std::cout); break;
                    case 10: gestionarRutas(sistema.grafo()); break;
                    case 11:
                        if (actualizarMapa()) {
                            mapaActivo = true;
                            std::cout << "Mapa numerado: " << archivoMapa << ". Se actualiza con esta sesion.\n";
                            if (!abrirMapaVisual(archivoMapa)) std::cout << "Abra ese archivo con su navegador.\n";
                        }
                        break;
                    case 12: {
                        const int id = leerEntero("ID de la incidencia: ", 1, std::numeric_limits<int>::max());
                        if (!sistema.buscar(id)) { std::cout << "ID inexistente.\n"; break; }
                        std::cout << "Elija el numero del lugar en el mapa (opcion 11).\n";
                        const int lugar = leerEntero("Lugar UPSA (1-205; 0 quitar; 206 listar catalogo): ",0,206);
                        if (lugar == 206) {
                            listarUbicacionesCampus(std::cout);
                            const int elegido = leerEntero("Lugar UPSA (0-205): ",0,205);
                            sistema.ubicarEnCampus(id,elegido,std::cout);
                        } else sistema.ubicarEnCampus(id,lugar,std::cout);
                        break;
                    }
                }
                if (mapaActivo && opcion != 0 && opcion != 11) actualizarMapa();
            }
        } catch (const FinEntrada&) {
            std::cout << "\nFin de entrada; cierre seguro.\n";
        }
        // Conserva la ultima vista como instantanea al cerrar la sesion.
        if (mapaActivo) actualizarMapa();
        sistema.cerrar(std::cout);
        return 0;
    } catch (const std::bad_alloc&) {
        std::cerr << "Memoria insuficiente. Se liberaron las estructuras al cerrar.\n";
        return 1;
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
