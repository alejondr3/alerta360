#pragma once
#include <string>

// En texto UTF-8, los bytes de continuacion no inician un caracter nuevo.
inline std::size_t longitudTexto(const std::string& texto) {
    std::size_t cantidad = 0;
    for (unsigned char c : texto) if ((c & 0xC0) != 0x80) ++cantidad;
    return cantidad;
}

enum class Estado { RECIBIDA, PENDIENTE, ASIGNADA, RESUELTA, CANCELADA };
enum class Tipo { ENERGIA = 1, RED, EQUIPO, CLIMA, INFRAESTRUCTURA, OTRO };

inline const char* nombreEstado(Estado e) {
    switch (e) {
        case Estado::RECIBIDA: return "RECIBIDA";
        case Estado::PENDIENTE: return "PENDIENTE";
        case Estado::ASIGNADA: return "ASIGNADA";
        case Estado::RESUELTA: return "RESUELTA";
        case Estado::CANCELADA: return "CANCELADA";
    }
    return "DESCONOCIDO";
}
inline const char* nombreTipo(Tipo t) {
    switch (t) {
        case Tipo::ENERGIA: return "Energia";
        case Tipo::RED: return "Red";
        case Tipo::EQUIPO: return "Equipo";
        case Tipo::CLIMA: return "Clima";
        case Tipo::INFRAESTRUCTURA: return "Infraestructura";
        case Tipo::OTRO: return "Otro";
    }
    return "Desconocido";
}

struct Ruta {
    bool existe = false;
    int nodos[8]{};
    int longitud = 0;
    long long costo = 0;
};

struct Incidencia {
    int id;
    std::string descripcion;
    Tipo tipo;
    int zona;
    int gravedad = 0;
    long long secuenciaIngreso;
    Estado estado = Estado::RECIBIDA;
    Ruta ruta;
    // Referencia inversa al heap, -1 si no pertenece a el.
    int posicionHeap = -1;
    // ID opcional del catalogo UPSA (1-205); 0 = ubicacion exacta sin elegir.
    // No modifica la zona 1-7 del grafo obligatorio.
    int ubicacionCampus = 0;
    // Numeracion 1-36 impresa en la foto oficial; independiente del catalogo.
    int referenciaPlano = 0;
    std::string bloque;
    std::string aula;
    // Solo mientras espera clasificacion automatica en la cola FIFO.
    int gravedadRegistro = 0;

    Incidencia(int id_, const std::string& desc, Tipo tipo_, int zona_, long long sec)
        : id(id_), descripcion(desc), tipo(tipo_), zona(zona_), secuenciaIngreso(sec) {}
};

class NoCopiable {
protected:
    NoCopiable() = default;
    ~NoCopiable() = default;
public:
    NoCopiable(const NoCopiable&) = delete;
    NoCopiable& operator=(const NoCopiable&) = delete;
};
