#include "Estructuras.h"
#include <limits>
#include <stdexcept>

ListaIncidencias::~ListaIncidencias() { limpiar(); }
Incidencia& ListaIncidencias::agregar(int id, const std::string& d, Tipo t, int z, long long s) {
    Nodo* nuevo = new Nodo(id, d, t, z, s);
    nuevo->anterior = cola_;
    if (cola_) cola_->siguiente = nuevo;
    else cabeza_ = nuevo;
    cola_ = nuevo;
    ++cantidad_;
    return nuevo->dato;
}
Incidencia* ListaIncidencias::buscar(int id) {
    for (Nodo* n = cabeza_; n; n = n->siguiente)
        if (n->dato.id == id) return &n->dato;
    return nullptr;
}
bool ListaIncidencias::validar() const {
    const Nodo* anterior = nullptr;
    std::size_t total = 0;
    for (const Nodo* n = cabeza_; n; n = n->siguiente) {
        if (n->anterior != anterior || ++total > cantidad_) return false;
        anterior = n;
    }
    if (anterior != cola_ || total != cantidad_) return false;
    const Nodo* siguiente = nullptr;
    total = 0;
    for (const Nodo* n = cola_; n; n = n->anterior) {
        if (n->siguiente != siguiente || ++total > cantidad_) return false;
        siguiente = n;
    }
    return siguiente == cabeza_ && total == cantidad_;
}
std::size_t ListaIncidencias::limpiar() {
    const auto total = cantidad_;
    while (cabeza_) {
        Nodo* viejo = cabeza_;
        cabeza_ = cabeza_->siguiente;
        delete viejo;
    }
    cola_ = nullptr;
    cantidad_ = 0;
    return total;
}

ColaIngreso::~ColaIngreso() { limpiar(); }
void ColaIngreso::encolar(int id) {
    Nodo* nuevo = new Nodo{id, nullptr};
    if (ultimo_) ultimo_->siguiente = nuevo;
    else primero_ = nuevo;
    ultimo_ = nuevo;
    ++cantidad_;
}
bool ColaIngreso::desencolar(int& id) {
    if (!primero_) return false;
    Nodo* viejo = primero_;
    id = viejo->id;
    primero_ = viejo->siguiente;
    if (!primero_) ultimo_ = nullptr;
    delete viejo;
    --cantidad_;
    return true;
}
bool ColaIngreso::frente(int& id) const {
    if (!primero_) return false;
    id = primero_->id;
    return true;
}
int ColaIngreso::ocurrencias(int id) const {
    int total = 0;
    for (const Nodo* n = primero_; n; n = n->siguiente)
        if (n->id == id) ++total;
    return total;
}
bool ColaIngreso::validar() const {
    std::size_t total = 0;
    const Nodo* ultimo = nullptr;
    for (const Nodo* n = primero_; n; n = n->siguiente) {
        if (++total > cantidad_) return false;
        ultimo = n;
    }
    return total == cantidad_ && ultimo == ultimo_;
}
std::size_t ColaIngreso::limpiar() {
    const auto total = cantidad_;
    int id = 0;
    while (desencolar(id)) {}
    return total;
}

IndiceBST::~IndiceBST() { limpiar(); }
bool IndiceBST::insertar(Incidencia& dato) {
    Nodo** enlace = &raiz_;
    while (*enlace) {
        if (dato.id == (*enlace)->id) return false;
        enlace = dato.id < (*enlace)->id ? &(*enlace)->izquierdo : &(*enlace)->derecho;
    }
    *enlace = new Nodo{dato.id, &dato, nullptr, nullptr};
    ++cantidad_;
    return true;
}
const Incidencia* IndiceBST::buscar(int id) const {
    const Nodo* actual = raiz_;
    while (actual) {
        if (id == actual->id) return actual->referencia;
        actual = id < actual->id ? actual->izquierdo : actual->derecho;
    }
    return nullptr;
}
Incidencia* IndiceBST::buscar(int id) {
    return const_cast<Incidencia*>(static_cast<const IndiceBST&>(*this).buscar(id));
}
int IndiceBST::alturaNodo(const Nodo* n) {
    if (!n) return 0;
    int a = alturaNodo(n->izquierdo), b = alturaNodo(n->derecho);
    return 1 + (a > b ? a : b);
}
void IndiceBST::recorrer(const Nodo* n, void (*visitar)(const Incidencia&, void*), void* c) {
    if (!n) return;
    recorrer(n->izquierdo, visitar, c);
    visitar(*n->referencia, c);
    recorrer(n->derecho, visitar, c);
}
void IndiceBST::inorden(void (*visitar)(const Incidencia&, void*), void* contexto) const {
    if (visitar) recorrer(raiz_, visitar, contexto);
}
bool IndiceBST::validarNodo(const Nodo* n, long long minimo, long long maximo,
                          std::size_t& total) {
    if (!n) return true;
    if (n->id <= minimo || n->id >= maximo || !n->referencia || n->id != n->referencia->id)
        return false;
    ++total;
    return validarNodo(n->izquierdo, minimo, n->id, total)
        && validarNodo(n->derecho, n->id, maximo, total);
}
bool IndiceBST::validar() const {
    std::size_t total = 0;
    return validarNodo(raiz_, std::numeric_limits<long long>::min(),
                       std::numeric_limits<long long>::max(), total) && total == cantidad_;
}
std::size_t IndiceBST::limpiar() {
    const auto total = cantidad_;
    // Rotaciones: destruccion iterativa, incluso si el arbol esta degenerado.
    while (raiz_) {
        if (raiz_->izquierdo) {
            Nodo* izquierda = raiz_->izquierdo;
            raiz_->izquierdo = izquierda->derecho;
            izquierda->derecho = raiz_;
            raiz_ = izquierda;
        } else {
            Nodo* viejo = raiz_;
            raiz_ = raiz_->derecho;
            delete viejo; // Nunca libera referencia.
        }
    }
    cantidad_ = 0;
    return total;
}

HeapPrioridad::~HeapPrioridad() { limpiar(); }
bool HeapPrioridad::antes(const Entrada& a, const Entrada& b) {
    if (a.gravedad != b.gravedad) return a.gravedad > b.gravedad;
    if (a.secuencia != b.secuencia) return a.secuencia < b.secuencia;
    return a.id < b.id; // Desempate defensivo; las secuencias reales son unicas.
}
void HeapPrioridad::reservar() {
    if (cantidad_ < capacidad_) return;
    if (capacidad_ > std::numeric_limits<int>::max() / 2)
        throw std::length_error("Capacidad maxima del heap alcanzada.");
    const int nueva = capacidad_ == 0 ? 8 : capacidad_ * 2;
    Entrada* arreglo = new Entrada[nueva];
    for (int i = 0; i < cantidad_; ++i) arreglo[i] = datos_[i];
    delete[] datos_;
    datos_ = arreglo;
    capacidad_ = nueva;
}
void HeapPrioridad::intercambiar(int a, int b) {
    Entrada temporal = datos_[a];
    datos_[a] = datos_[b];
    datos_[b] = temporal;
    *datos_[a].posicion = a;
    *datos_[b].posicion = b;
}
void HeapPrioridad::subir(int p) {
    while (p > 0) {
        const int padre = (p - 1) / 2;
        if (!antes(datos_[p], datos_[padre])) break;
        intercambiar(p, padre);
        p = padre;
    }
}
void HeapPrioridad::bajar(int p) {
    // p < cantidad_/2 garantiza que existe hijo izquierdo y evita overflow.
    while (p < cantidad_ / 2) {
        int mejor = 2 * p + 1;
        if (mejor + 1 < cantidad_ && antes(datos_[mejor + 1], datos_[mejor])) ++mejor;
        if (!antes(datos_[mejor], datos_[p])) break;
        intercambiar(p, mejor);
        p = mejor;
    }
}
void HeapPrioridad::reparar(int p) {
    if (p > 0 && antes(datos_[p], datos_[(p - 1) / 2])) subir(p);
    else bajar(p);
}
void HeapPrioridad::insertar(Incidencia& dato) {
    if (dato.estado != Estado::PENDIENTE || dato.gravedad < 1 || dato.gravedad > 5
        || dato.posicionHeap != -1) throw std::logic_error("Insercion invalida en heap.");
    reservar();
    const int p = cantidad_++;
    datos_[p] = {dato.id, dato.gravedad, dato.secuenciaIngreso, &dato.posicionHeap};
    dato.posicionHeap = p;
    subir(p);
}
bool HeapPrioridad::cima(int& id) const {
    if (vacio()) return false;
    id = datos_[0].id;
    return true;
}
void HeapPrioridad::quitarPosicion(int p) {
    *datos_[p].posicion = -1;
    --cantidad_;
    if (p == cantidad_) return;
    datos_[p] = datos_[cantidad_];
    *datos_[p].posicion = p;
    reparar(p);
}
bool HeapPrioridad::extraer(int& id) {
    if (!cima(id)) return false;
    quitarPosicion(0);
    return true;
}
bool HeapPrioridad::retirar(Incidencia& dato) {
    const int p = dato.posicionHeap;
    if (p < 0 || p >= cantidad_ || datos_[p].id != dato.id) return false;
    quitarPosicion(p);
    return true;
}
bool HeapPrioridad::cambiarGravedad(Incidencia& dato, int nueva) {
    const int p = dato.posicionHeap;
    if (nueva < 1 || nueva > 5 || dato.estado != Estado::PENDIENTE
        || p < 0 || p >= cantidad_ || datos_[p].id != dato.id) return false;
    dato.gravedad = nueva;
    datos_[p].gravedad = nueva;
    reparar(p);
    return true;
}
int HeapPrioridad::proximos(int* ids, int limite) const {
    if (!ids || limite <= 0) return 0;
    const int total = limite < cantidad_ ? limite : cantidad_;
    // Copia de metadatos: sus swaps NO actualizan posiciones del heap original.
    Entrada* copia = new Entrada[cantidad_];
    for (int i = 0; i < cantidad_; ++i) copia[i] = datos_[i];
    int restantes = cantidad_;
    for (int i = 0; i < total; ++i) {
        ids[i] = copia[0].id;
        copia[0] = copia[--restantes];
        int p = 0;
        while (p < restantes / 2) {
            int mejor = 2 * p + 1;
            if (mejor + 1 < restantes && antes(copia[mejor + 1], copia[mejor])) ++mejor;
            if (!antes(copia[mejor], copia[p])) break;
            Entrada temporal = copia[p]; copia[p] = copia[mejor]; copia[mejor] = temporal;
            p = mejor;
        }
    }
    delete[] copia;
    return total;
}
bool HeapPrioridad::validar(const IndiceBST& indice) const {
    if (cantidad_ < 0 || cantidad_ > capacidad_) return false;
    for (int i = 0; i < cantidad_; ++i) {
        const auto* dato = indice.buscar(datos_[i].id);
        if (!dato || dato->estado != Estado::PENDIENTE || dato->posicionHeap != i
            || datos_[i].posicion != &dato->posicionHeap || datos_[i].gravedad != dato->gravedad
            || datos_[i].secuencia != dato->secuenciaIngreso) return false;
        if (i > 0 && antes(datos_[i], datos_[(i - 1) / 2])) return false;
    }
    return true;
}
int HeapPrioridad::limpiar() {
    const int total = cantidad_;
    for (int i = 0; i < cantidad_; ++i) *datos_[i].posicion = -1;
    delete[] datos_;
    datos_ = nullptr;
    cantidad_ = capacidad_ = 0;
    return total;
}

PilaDeshacer::~PilaDeshacer() { limpiar(); }
void PilaDeshacer::apilar(Correccion dato) {
    cima_ = new Nodo{dato, cima_};
    ++cantidad_;
}
bool PilaDeshacer::desapilar(Correccion& dato) {
    if (!cima_) return false;
    Nodo* viejo = cima_;
    dato = viejo->dato;
    cima_ = viejo->siguiente;
    delete viejo;
    --cantidad_;
    return true;
}
bool PilaDeshacer::cima(Correccion& dato) const {
    if (!cima_) return false;
    dato = cima_->dato;
    return true;
}
bool PilaDeshacer::validar() const {
    std::size_t total = 0;
    for (const Nodo* n = cima_; n; n = n->siguiente) {
        if (++total > cantidad_ || n->dato.id <= 0
            || n->dato.gravedadAnterior < 1 || n->dato.gravedadAnterior > 5) return false;
    }
    return total == cantidad_;
}
std::size_t PilaDeshacer::limpiar() {
    const auto total = cantidad_;
    Correccion dato{};
    while (desapilar(dato)) {}
    return total;
}
