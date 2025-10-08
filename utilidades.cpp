// Funciones utilitarias para entrada y validación de datos en consola
#ifndef UTILIDADES_CPP
#define UTILIDADES_CPP

#include <iostream>
#include <limits>
#include <string>

#include "fecha.cpp"

using namespace std;

// Lee un número entero desde la entrada estándar, validando la entrada.
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

// Lee una línea de texto desde la entrada estándar, mostrando un mensaje previo.
inline string leerCadena(const string &mensaje) {
    cout << mensaje;
    string texto;
    getline(cin, texto);
    return texto;
}

// Lee una fecha desde la entrada estándar, validando el formato AAAA-MM-DD.
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

// Lee una opción numérica dentro de un rango específico.
inline int leerOpcion(int minimo, int maximo) {
    while (true) {
        cout << "Seleccione una opcion: ";
        int opcion = leerEntero();
        if (opcion >= minimo && opcion <= maximo) {
            return opcion;
        }
        cout << "Opcion fuera de rango. Ingrese un numero entre "
             << minimo << " y " << maximo << ".\n";
    }
}

// Pausa la ejecución hasta que el usuario presione ENTER.
inline void pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

#endif // UTILIDADES_CPP
