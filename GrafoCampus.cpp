#include "GrafoCampus.h"
#include <limits>
#include <ostream>

GrafoCampus::GrafoCampus() {
    for (int a = 0; a < ZONAS; ++a)
        for (int b = 0; b < ZONAS; ++b)
            costos_[a][b] = restaurables_[a][b] = a == b ? 0 : -1;
    const int conexiones[][3] = {
        {0,1,4}, {0,2,2}, {1,2,1}, {1,3,5}, {2,3,8}, {2,4,10},
        {3,4,2}, {3,5,6}, {4,5,3}, {4,6,1}, {5,7,4}, {6,7,2}
    };
    for (const auto& c : conexiones) {
        costos_[c[0]][c[1]] = costos_[c[1]][c[0]] = c[2];
        restaurables_[c[0]][c[1]] = restaurables_[c[1]][c[0]] = c[2];
    }
}
const char* GrafoCampus::nombreZona(int zona) {
    static const char* const nombres[] = {
        "Central de soporte", "Biblioteca", "Laboratorios", "Coliseo",
        "Residencias", "Cafeteria", "Centro de salud universitario", "Estadio"
    };
    return zona >= 0 && zona < ZONAS ? nombres[zona] : "Zona invalida";
}
int GrafoCampus::costo(int a, int b) const {
    return a >= 0 && a < ZONAS && b >= 0 && b < ZONAS ? costos_[a][b] : -1;
}
bool GrafoCampus::cambiarCosto(int a, int b, int minutos) {
    if (a < 0 || a >= ZONAS || b < 0 || b >= ZONAS || a == b || minutos <= 0)
        return false;
    // Gestiona vias del mapa inicial; no crea conexiones arbitrarias.
    if (restaurables_[a][b] == -1) return false;
    costos_[a][b] = costos_[b][a] = minutos;
    restaurables_[a][b] = restaurables_[b][a] = minutos;
    return true;
}
bool GrafoCampus::cerrar(int a, int b) {
    if (a == b || costo(a,b) <= 0) return false;
    costos_[a][b] = costos_[b][a] = -1;
    return true;
}
bool GrafoCampus::restaurar(int a, int b) {
    if (a < 0 || a >= ZONAS || b < 0 || b >= ZONAS || a == b
        || costos_[a][b] != -1 || restaurables_[a][b] <= 0) return false;
    costos_[a][b] = costos_[b][a] = restaurables_[a][b];
    return true;
}
Ruta GrafoCampus::dijkstra(int origen, int destino) const {
    Ruta ruta;
    if (origen < 0 || origen >= ZONAS || destino < 0 || destino >= ZONAS) return ruta;
    constexpr long long INF = std::numeric_limits<long long>::max() / 4;
    long long distancia[ZONAS];
    int anterior[ZONAS];
    bool visitado[ZONAS]{};
    for (int i = 0; i < ZONAS; ++i) { distancia[i] = INF; anterior[i] = -1; }
    distancia[origen] = 0;
    for (int paso = 0; paso < ZONAS; ++paso) {
        int u = -1;
        for (int i = 0; i < ZONAS; ++i)
            if (!visitado[i] && (u == -1 || distancia[i] < distancia[u])) u = i;
        if (u == -1 || distancia[u] == INF) break;
        visitado[u] = true;
        if (u == destino) break;
        for (int v = 0; v < ZONAS; ++v) {
            if (!visitado[v] && costos_[u][v] > 0) {
                const long long candidato = distancia[u] + costos_[u][v];
                if (candidato < distancia[v]) {
                    distancia[v] = candidato;
                    anterior[v] = u;
                }
            }
        }
    }
    if (distancia[destino] == INF) return ruta;
    int inverso[ZONAS], longitud = 0;
    for (int u = destino; u != -1; u = anterior[u]) inverso[longitud++] = u;
    ruta.existe = true;
    ruta.costo = distancia[destino];
    ruta.longitud = longitud;
    for (int i = 0; i < longitud; ++i) ruta.nodos[i] = inverso[longitud - 1 - i];
    return ruta;
}
void GrafoCampus::mostrar(std::ostream& out) const {
    for (int i = 0; i < ZONAS; ++i) out << i << ": " << nombreZona(i) << '\n';
    out << "Vias (minutos):\n";
    for (int a = 0; a < ZONAS; ++a)
        for (int b = a + 1; b < ZONAS; ++b) {
            if (restaurables_[a][b] <= 0) continue;
            out << a << " <-> " << b << ": ";
            if (costos_[a][b] == -1) out << "CERRADA (ultimo costo " << restaurables_[a][b] << ")\n";
            else out << costos_[a][b] << " min\n";
        }
}
bool GrafoCampus::validar() const {
    for (int a = 0; a < ZONAS; ++a)
        for (int b = 0; b < ZONAS; ++b) {
            if (costos_[a][b] != costos_[b][a] || restaurables_[a][b] != restaurables_[b][a])
                return false;
            if (a == b) { if (costos_[a][b] != 0 || restaurables_[a][b] != 0) return false; }
            else if (costos_[a][b] != -1 && costos_[a][b] <= 0) return false;
            else if (costos_[a][b] > 0 && costos_[a][b] != restaurables_[a][b]) return false;
        }
    return true;
}
