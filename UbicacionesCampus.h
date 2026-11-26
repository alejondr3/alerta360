#pragma once
#include <iosfwd>
#include <string>

struct UbicacionCampus {
    int id;
    const char* nombre;
    const char* bloque;
    const char* planta;
    double x;
    double y;
    bool tienePosicion;
    bool docente=false;
};
const UbicacionCampus* buscarUbicacionCampus(int id);
void listarUbicacionesCampus(std::ostream& out);
void escribirUbicacionesCampusJSON(std::ostream& out);
const char* nombreReferenciaPlano(int numero);
void listarReferenciasPlano(std::ostream& out);
std::string normalizarBloqueCampus(const std::string& bloque);
const UbicacionCampus* buscarAulaCampus(const std::string& bloque, const std::string& aula);
