#ifndef FECHA_CPP
#define FECHA_CPP

#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

// Estructura que representa una fecha y utilidades asociadas
struct Fecha {
    int anio{0}; // Año (ejemplo: 2025)
    int mes{0};  // Mes (1-12)
    int dia{0};  // Día (1-31 según el mes)

    // Verifica si una fecha es válida según el calendario gregoriano
    static bool esValida(const Fecha &f);
    // Intenta convertir un string con formato "AAAA-MM-DD" a una fecha
    static bool intentarParsear(const string &texto, Fecha &resultado);

    // Devuelve la fecha en formato texto "AAAA-MM-DD"
    string aTexto() const;
    // Operador menor para comparar fechas cronológicamente
    bool operator<(const Fecha &otra) const;
    // Operador de igualdad para comparar fechas
    bool operator==(const Fecha &otra) const;
};

// Implementación de las funciones de la estructura Fecha
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

// Intenta convertir un string con formato "AAAA-MM-DD" a una fecha
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

// Devuelve la fecha en formato texto "AAAA-MM-DD"
inline string Fecha::aTexto() const {
    ostringstream salida;
    salida << setw(4) << setfill('0') << anio << '-'
           << setw(2) << setfill('0') << mes << '-'
           << setw(2) << setfill('0') << dia;
    return salida.str();
}

// Operador menor para comparar fechas cronológicamente
inline bool Fecha::operator<(const Fecha &otra) const {
    if (anio != otra.anio) {
        return anio < otra.anio;
    }
    if (mes != otra.mes) {
        return mes < otra.mes;
    }
    return dia < otra.dia;
}

// Operador de igualdad para comparar fechas
inline bool Fecha::operator==(const Fecha &otra) const {
    return anio == otra.anio && mes == otra.mes && dia == otra.dia;
}

#endif // FECHA_CPP
