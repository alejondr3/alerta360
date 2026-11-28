#pragma once
#include <iosfwd>
#include <string>
// Serializacion conservada para exportar datos y comprobar el catalogo.
void escribirCadenaJSON(std::ostream&, const std::string&);
