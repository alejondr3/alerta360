#include "MapaVisual.h"
#include "SistemaAlerta360.h"
#include "UbicacionesCampus.h"
#include <filesystem>
#include <fstream>
#include <ostream>
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <windows.h>
#include <shellapi.h>
#elif defined(__unix__) || defined(__APPLE__)
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#endif

namespace {
struct LimpiezaTemporal {
    std::filesystem::path ruta;
    ~LimpiezaTemporal() {
        std::error_code ignorado;
        std::filesystem::remove(ruta,ignorado);
    }
};
}

void escribirCadenaJSON(std::ostream& out, const std::string& valor) {
    static const char hex[] = "0123456789abcdef";
    out << '"';
    for (unsigned char c : valor) {
        if (c == '"') out << "\\\"";
        else if (c == '\\') out << "\\\\";
        else if (c < 32 || c == '<' || c == '>' || c == '&')
            out << "\\u00" << hex[c >> 4] << hex[c & 15];
        else out << static_cast<char>(c);
    }
    out << '"';
}
bool guardarMapaVisual(const SistemaAlerta360& sistema, const std::string& archivo, std::string& error) {
    try {
        const std::filesystem::path destino{std::u8string(archivo.begin(),archivo.end())};
        auto temporal = destino;
        temporal += ".tmp";
        const LimpiezaTemporal limpieza{temporal};
        std::ofstream out(temporal, std::ios::binary | std::ios::trunc);
        if (!out) { error = "No se pudo crear el mapa en esta carpeta."; return false; }
        out << "<!doctype html><html lang=\"es\"><head><meta charset=\"utf-8\">"
            "<meta name=\"viewport\" content=\"width=device-width,initial-scale=1\">"
            "<title>Alerta360 | Mapa de incidencias</title></head><body>"
            "<script id=\"datos\" type=\"application/json\">{";
        out << "\"campus\":";
        escribirUbicacionesCampusJSON(out);
        out << ",\"sistema\":";
        sistema.exportarDatosMapa(out);
        out << "}</script>";
        out <<
#include "MapaPlantilla.inc"
        ;
        out << "</body></html>";
        out.close();
        if (!out) { error = "No se pudo completar la escritura del mapa."; return false; }
#ifdef _WIN32
        if (!MoveFileExW(temporal.c_str(), destino.c_str(), MOVEFILE_REPLACE_EXISTING)) {
            error = "No se pudo reemplazar el archivo del mapa.";
            std::error_code ignorado;
            std::filesystem::remove(temporal, ignorado);
            return false;
        }
#else
        std::filesystem::rename(temporal, destino);
#endif
        error.clear();
        return true;
    } catch (const std::exception& e) { error = e.what(); return false; }
}
bool abrirMapaVisual(const std::string& archivo) {
    const auto ruta = std::filesystem::absolute(std::filesystem::path{std::u8string(archivo.begin(),archivo.end())});
#ifdef _WIN32
    const auto resultado = ShellExecuteW(nullptr, L"open", ruta.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
    return reinterpret_cast<INT_PTR>(resultado) > 32;
#elif defined(__unix__) || defined(__APPLE__)
    // Sin shell: un nombre de archivo nunca se interpreta como un comando.
    pid_t pid = fork();
    if (pid < 0) return false;
    if (pid == 0) {
        pid_t nieto = fork();
        if (nieto < 0) _exit(1);
        if (nieto > 0) _exit(0);
#ifdef __APPLE__
        execlp("open", "open", ruta.c_str(), static_cast<char*>(nullptr));
#else
        execlp("xdg-open", "xdg-open", ruta.c_str(), static_cast<char*>(nullptr));
#endif
        _exit(127);
    }
    int estado = 0;
    return waitpid(pid, &estado, 0) == pid && WIFEXITED(estado) && WEXITSTATUS(estado) == 0;
#else
    return false;
#endif
}
