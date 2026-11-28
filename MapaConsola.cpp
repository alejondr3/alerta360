#include "MapaConsola.h"
#include "UbicacionesCampus.h"
#include <array>
#include <ostream>

namespace {
bool activa(const Incidencia& i) {
    return i.estado!=Estado::RESUELTA && i.estado!=Estado::CANCELADA;
}
std::string bloqueDe(const Incidencia& i) {
    // La ubicacion explicita mas reciente tiene prioridad sobre el registro.
    if (i.referenciaPlano) return {};
    if (const auto* p=buscarUbicacionCampus(i.ubicacionCampus))
        return normalizarBloqueCampus(p->bloque);
    return normalizarBloqueCampus(i.bloque);
}
struct Resumen { int cantidad=0; int gravedad=0; };
std::string celda(const std::string& texto) {
    return "| " + texto + std::string(18-texto.size(),' ') + " |";
}
void fila(std::ostream& out, const std::array<std::string,3>& nombres,
          const std::array<Resumen,3>& datos) {
    const char* borde="+--------------------+";
    for (int linea=0;linea<5;++linea) {
        out << "  ";
        for (std::size_t j=0;j<3;++j) {
            if (nombres[j].empty()) out << std::string(22,' ');
            else if (linea==0 || linea==4) out << borde;
            else if (linea==1) out << celda(nombres[j]);
            else if (linea==2) out << celda(datos[j].cantidad
                ? "! " + std::to_string(datos[j].cantidad) + " activa(s)" : "Sin incidencias");
            else out << celda(datos[j].cantidad
                ? "Gravedad max: " + std::to_string(datos[j].gravedad) : "");
            out << "  ";
        }
        out << '\n';
    }
}
void listarIncidencia(const Incidencia& i, std::ostream& out) {
    out << "  ! #" << i.id;
    const auto* p=buscarUbicacionCampus(i.ubicacionCampus);
    if (i.referenciaPlano) out << " | " << nombreReferenciaPlano(i.referenciaPlano);
    else if (p) {
        const std::string b=normalizarBloqueCampus(p->bloque), nombre=p->nombre;
        if (!b.empty()) out << " | Bloque " << b;
        if (p->docente && nombre.size()>=5 && nombre[1]=='-') out << " | Aula " << nombre.substr(2,3);
        out << " | " << p->nombre << " | " << p->planta;
    } else if (!i.bloque.empty()) out << " | Bloque " << i.bloque << " | Aula " << i.aula;
    else out << " | Zona de atencion " << i.zona;
    out << " | Gravedad " << i.gravedad << " | " << nombreEstado(i.estado) << '\n';
}
}

void dibujarMapaConsola(const ListaIncidencias& lista, std::ostream& out,
                        const std::string& filtro) {
    const std::string bloque=normalizarBloqueCampus(filtro);
    std::array<Resumen,6> datos{}; // Central, A, B, C, D, E.
    int sinBloque=0,total=0;
    for (auto* n=lista.cabeza();n;n=n->siguiente) {
        const auto& i=n->dato;
        if (!activa(i)) continue;
        ++total;
        const auto b=bloqueDe(i);
        int indice=-1;
        if (b=="CENTRAL") indice=0;
        else if (b.size()==1 && b[0]>='A' && b[0]<='E') indice=b[0]-'A'+1;
        if (indice<0) {++sinBloque;continue;}
        auto& r=datos[static_cast<std::size_t>(indice)];
        ++r.cantidad;
        if (i.gravedad>r.gravedad) r.gravedad=i.gravedad;
    }
    out << "\n===================== MAPA UPSA =====================\n"
        "  Esquema por bloques, orientado como la imagen de referencia.\n"
        "  Ubicaciones aproximadas; no representa interiores ni rutas.\n\n";
    out << "                           CANCHA / AREAS\n";
    fila(out,{"BLOQUE B","","BLOQUE E"},{datos[2],{},datos[5]});
    fila(out,{"BLOQUE A","BLOQUE C","BLOQUE D"},{datos[1],datos[3],datos[4]});
    fila(out,{"BLOQUE CENTRAL","",""},{datos[0],{}, {}});
    out << "  ================= ACCESO / AVENIDA =================\n"
        "  ! = incidencia activa | Total: " << total << " | Sin bloque en el esquema: " << sinBloque
        << "\n  Resueltas y canceladas se consultan en el historial.\n";
    if (!bloque.empty()) out << "\nBLOQUE " << bloque << " - INCIDENCIAS ACTIVAS\n";
    else out << "\nINCIDENCIAS ACTIVAS (ID, aula y gravedad)\n";
    int visibles=0;
    for (auto* n=lista.cabeza();n;n=n->siguiente) {
        if (!activa(n->dato) || (!bloque.empty() && bloqueDe(n->dato)!=bloque)) continue;
        listarIncidencia(n->dato,out);++visibles;
    }
    if (!visibles) out << "  Sin incidencias activas" << (bloque.empty()?".":" en este bloque.") << '\n';
    if (!bloque.empty()) {
        out << "\nAULAS Y ESPACIOS DOCENTES CATALOGADOS - BLOQUE " << bloque << '\n';
        int lugares=0;
        for (int id=1;id<=205;++id) {
            const auto* p=buscarUbicacionCampus(id);
            if (!p || !p->docente || normalizarBloqueCampus(p->bloque)!=bloque) continue;
            out << "  " << p->nombre << " | " << p->planta << '\n';++lugares;
        }
        if (!lugares) out << "  Sin espacios docentes catalogados para este bloque.\n";
        out << "  Catalogo de referencia; no es un plano interior.\n";
    }
}
