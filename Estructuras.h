#pragma once
#include "Incidencia.h"
#include <cstddef>

// Esta lista es la UNICA propietaria de los registros Incidencia.
class ListaIncidencias : private NoCopiable {
public:
    struct Nodo {
        Incidencia dato;
        Nodo* anterior = nullptr;
        Nodo* siguiente = nullptr;
        Nodo(int id, const std::string& d, Tipo t, int z, long long s)
            : dato(id, d, t, z, s) {}
    };
private:
    Nodo* cabeza_ = nullptr;
    Nodo* cola_ = nullptr;
    std::size_t cantidad_ = 0;
public:
    ListaIncidencias() = default;
    ~ListaIncidencias();
    Incidencia& agregar(int id, const std::string&, Tipo, int zona, long long secuencia);
    Incidencia* buscar(int id);
    const Nodo* cabeza() const { return cabeza_; }
    const Nodo* cola() const { return cola_; }
    std::size_t cantidad() const { return cantidad_; }
    bool validar() const;
    std::size_t limpiar();
};

class ColaIngreso : private NoCopiable {
    struct Nodo { int id; Nodo* siguiente; };
    Nodo* primero_ = nullptr;
    Nodo* ultimo_ = nullptr;
    std::size_t cantidad_ = 0;
public:
    ColaIngreso() = default;
    ~ColaIngreso();
    void encolar(int id);
    bool desencolar(int& id);
    bool frente(int& id) const;
    bool vacia() const { return primero_ == nullptr; }
    std::size_t cantidad() const { return cantidad_; }
    int ocurrencias(int id) const;
    bool validar() const;
    std::size_t limpiar();
};

class IndiceBST : private NoCopiable {
    struct Nodo {
        int id;
        Incidencia* referencia; // No propietaria: pertenece a ListaIncidencias.
        Nodo* izquierdo;
        Nodo* derecho;
    };
    Nodo* raiz_ = nullptr;
    std::size_t cantidad_ = 0;
    static int alturaNodo(const Nodo*);
    static void recorrer(const Nodo*, void (*visitar)(const Incidencia&, void*), void*);
    static bool validarNodo(const Nodo*, long long minimo, long long maximo,
                            std::size_t& cantidad);
public:
    IndiceBST() = default;
    ~IndiceBST();
    bool insertar(Incidencia&);
    Incidencia* buscar(int id);
    const Incidencia* buscar(int id) const;
    void inorden(void (*visitar)(const Incidencia&, void*), void* contexto) const;
    int altura() const { return alturaNodo(raiz_); }
    std::size_t cantidad() const { return cantidad_; }
    bool validar() const;
    std::size_t limpiar();
};

class HeapPrioridad : private NoCopiable {
    struct Entrada {
        int id;
        int gravedad;
        long long secuencia;
        int* posicion; // No propietaria; apunta a posicionHeap del registro original.
    };
    Entrada* datos_ = nullptr;
    int cantidad_ = 0;
    int capacidad_ = 0;
    static bool antes(const Entrada&, const Entrada&);
    void intercambiar(int a, int b);
    void subir(int posicion);
    void bajar(int posicion);
    void reparar(int posicion);
    void reservar();
    void quitarPosicion(int posicion);
public:
    HeapPrioridad() = default;
    ~HeapPrioridad();
    void insertar(Incidencia&);
    bool cima(int& id) const;
    bool extraer(int& id);
    bool retirar(Incidencia&);
    bool cambiarGravedad(Incidencia&, int nueva);
    int cantidad() const { return cantidad_; }
    bool vacio() const { return cantidad_ == 0; }
    int proximos(int* ids, int limite) const;
    bool validar(const IndiceBST&) const;
    int limpiar();
};

struct Correccion { int id; int gravedadAnterior; };
class PilaDeshacer : private NoCopiable {
    struct Nodo { Correccion dato; Nodo* siguiente; };
    Nodo* cima_ = nullptr;
    std::size_t cantidad_ = 0;
public:
    PilaDeshacer() = default;
    ~PilaDeshacer();
    void apilar(Correccion);
    bool desapilar(Correccion&);
    bool cima(Correccion&) const;
    bool vacia() const { return cima_ == nullptr; }
    std::size_t cantidad() const { return cantidad_; }
    bool validar() const;
    std::size_t limpiar();
};
