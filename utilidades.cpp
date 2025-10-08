#ifndef UTILIDADES_CPP
#define UTILIDADES_CPP

#include <iostream>
#include <limits>
#include <string>

#include "fecha.cpp"

using namespace std;

inline int leerEntero() {
    int valor;
    while (!(cin >> valor)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada invalida. Intente nuevamente: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return valor;
}

inline string leerCadena(const string &mensaje) {
    cout << mensaje;
    string texto;
    getline(cin, texto);
    return texto;
}

inline Fecha leerFecha(const string &mensaje) {
    while (true) {
        string texto = leerCadena(mensaje);
        Fecha resultado;
        if (Fecha::intentarParsear(texto, resultado)) {
            return resultado;
        }
        cout << "Fecha invalida. Utilice el formato AAAA-MM-DD.\n";
    }
}

inline void pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

#endif
