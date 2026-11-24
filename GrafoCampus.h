#pragma once
#include "Incidencia.h"
#include <iosfwd>

class GrafoCampus {
    int costos_[8][8]{};
    int restaurables_[8][8]{};
public:
    static constexpr int ZONAS = 8;
    GrafoCampus();
    static const char* nombreZona(int zona);
    int costo(int a, int b) const;
    bool cambiarCosto(int a, int b, int minutos);
    bool cerrar(int a, int b);
    bool restaurar(int a, int b);
    Ruta dijkstra(int origen, int destino) const;
    void mostrar(std::ostream&) const;
    bool validar() const;
};
