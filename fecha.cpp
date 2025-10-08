#ifndef FECHA_CPP
#define FECHA_CPP

#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

struct Fecha {
    int anio{0};
    int mes{0};
    int dia{0};

    static bool esValida(const Fecha &f);
    static bool intentarParsear(const string &texto, Fecha &resultado);

    string aTexto() const;
    bool operator<(const Fecha &otra) const;
    bool operator==(const Fecha &otra) const;
};

inline bool Fecha::esValida(const Fecha &f) {
    if (f.anio < 1900 || f.anio > 2100) {
        return false;
    }
    if (f.mes < 1 || f.mes > 12) {
        return false;
    }
    static const int diasPorMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int limite = diasPorMes[f.mes];
    bool esBisiesto = (f.anio % 4 == 0 && f.anio % 100 != 0) || (f.anio % 400 == 0);
    if (f.mes == 2 && esBisiesto) {
        limite = 29;
    }
    return f.dia >= 1 && f.dia <= limite;
}

inline bool Fecha::intentarParsear(const string &texto, Fecha &resultado) {
    char separador1 = 0;
    char separador2 = 0;
    istringstream flujo(texto);
    if (!(flujo >> resultado.anio >> separador1 >> resultado.mes >> separador2 >> resultado.dia)) {
        return false;
    }
    if (separador1 != '-' || separador2 != '-') {
        return false;
    }
    return esValida(resultado);
}

inline string Fecha::aTexto() const {
    ostringstream salida;
    salida << setw(4) << setfill('0') << anio << '-'
           << setw(2) << setfill('0') << mes << '-'
           << setw(2) << setfill('0') << dia;
    return salida.str();
}

inline bool Fecha::operator<(const Fecha &otra) const {
    if (anio != otra.anio) {
        return anio < otra.anio;
    }
    if (mes != otra.mes) {
        return mes < otra.mes;
    }
    return dia < otra.dia;
}

inline bool Fecha::operator==(const Fecha &otra) const {
    return anio == otra.anio && mes == otra.mes && dia == otra.dia;
}

#endif
