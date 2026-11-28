#include "DatosJSON.h"
#include <ostream>

void escribirCadenaJSON(std::ostream& out, const std::string& valor) {
    static const char hex[]="0123456789abcdef";
    out << '"';
    for (unsigned char c:valor) {
        if (c=='"') out << "\\\"";
        else if (c=='\\') out << "\\\\";
        else if (c<32 || c=='<' || c=='>' || c=='&')
            out << "\\u00" << hex[c>>4] << hex[c&15];
        else out << static_cast<char>(c);
    }
    out << '"';
}
