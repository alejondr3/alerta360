#pragma once
#include "Estructuras.h"
#include "GrafoCampus.h"
#include <iosfwd>

class SistemaAlerta360 : private NoCopiable {
    // Orden deliberado: la lista se destruye AL FINAL (orden inverso de miembros).
    ListaIncidencias lista_;
    IndiceBST indice_;
    ColaIngreso cola_;
    HeapPrioridad heap_;
    PilaDeshacer pila_;
    GrafoCampus grafo_;
    long long secuencia_ = 0;
    void saltarCanceladas(std::ostream&);
    bool crearRegistro(int id, const std::string&, Tipo, int zona, std::ostream&);
    void clasificarRegistrosConGravedad(std::ostream&);
public:
    SistemaAlerta360() = default;
    bool registrar(int id, const std::string& descripcion, Tipo tipo, int zona, std::ostream&);
    bool registrarAula(const std::string& bloque, const std::string& aula,
                      int id, int gravedad, std::ostream&);
    int siguienteClasificacion(std::ostream&);
    bool clasificarSiguiente(int gravedad, std::ostream&);
    bool cambiarGravedad(int id, int gravedad, std::ostream&);
    bool deshacerGravedad(std::ostream&);
    bool asignarSiguiente(std::ostream&);
    bool resolver(int id, std::ostream&);
    bool cancelar(int id, std::ostream&);
    const Incidencia* buscar(int id) const { return indice_.buscar(id); }
    int proximos(int* ids, int limite) const { return heap_.proximos(ids, limite); }
    void mostrarIncidencia(int id, std::ostream&) const;
    void mostrarInformes(std::ostream&) const;
    bool ubicarEnCampus(int id, int ubicacion, std::ostream&);
    bool ubicarEnPlano(int id, int referencia, std::ostream&);
    void exportarDatosMapa(std::ostream&) const;
    static void mostrarFicha(const Incidencia&, std::ostream&);
    GrafoCampus& grafo() { return grafo_; }
    const GrafoCampus& grafo() const { return grafo_; }
    int alturaBST() const { return indice_.altura(); }
    std::size_t cantidad() const { return lista_.cantidad(); }
    std::size_t correcciones() const { return pila_.cantidad(); }
    bool validarConsistencia() const;
    void cerrar(std::ostream&);
};
