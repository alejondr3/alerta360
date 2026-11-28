#pragma once
#include "Estructuras.h"
#include <iosfwd>
#include <string>

// Vista de solo lectura: no cambia estados, prioridades ni rutas.
void dibujarMapaConsola(const ListaIncidencias&, std::ostream&,
                        const std::string& bloque = {});
