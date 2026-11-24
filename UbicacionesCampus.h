#pragma once
#include <iosfwd>

struct UbicacionCampus {
    int id;
    const char* nombre;
    const char* bloque;
    const char* planta;
    double x;
    double y;
    bool tienePosicion;
};
const UbicacionCampus* buscarUbicacionCampus(int id);
void listarUbicacionesCampus(std::ostream& out);
void escribirUbicacionesCampusJSON(std::ostream& out);
const char* nombreReferenciaPlano(int numero);
void listarReferenciasPlano(std::ostream& out);
