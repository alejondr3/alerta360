#pragma once
#include <iosfwd>
#include <string>

class SistemaAlerta360;
// Escapa tambien <, > y &: los datos no pueden cerrar el bloque script del HTML.
void escribirCadenaJSON(std::ostream& out, const std::string& valor);
bool guardarMapaVisual(const SistemaAlerta360& sistema, const std::string& archivo,
                       std::string& error);
bool abrirMapaVisual(const std::string& archivo);
