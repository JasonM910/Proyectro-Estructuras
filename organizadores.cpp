// Definición de funciones y utilidades para la gestión de organizadores
#ifndef ORGANIZADORES_CPP
#define ORGANIZADORES_CPP

#include <iostream>
#include <string>

#include "relaciones.cpp"

using namespace std;

// Busca un organizador en la lista por su ID. Devuelve un puntero al organizador si lo encuentra, o nullptr si no existe.
inline NodoOrganizador *buscarOrganizadorPorId(const string &id) {
    NodoOrganizador *actual = cabezaOrganizadores;
    while (actual != nullptr) {
        if (actual->id == id) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

inline NodoOrganizador *insertarOrganizador(const string &id,
                                            const string &nombre,
                                            const string &departamento) {
// Crea un nuevo organizador y lo inserta al final de la lista doblemente enlazada. Devuelve el puntero al organizador creado o nullptr si ya existe el ID.
    if (buscarOrganizadorPorId(id) != nullptr) {
        return nullptr;
    }
    auto *nodo = new NodoOrganizador();
    nodo->id = id;
    nodo->nombre = nombre;
    nodo->departamento = departamento;
    if (cabezaOrganizadores == nullptr) {
        cabezaOrganizadores = nodo;
        colaOrganizadores = nodo;
    } else {
        colaOrganizadores->siguiente = nodo;
        nodo->anterior = colaOrganizadores;
        colaOrganizadores = nodo;
    }
    return nodo;
}

inline void actualizarOrganizador(NodoOrganizador *organizador,
                                  const string &nuevoNombre,
                                  const string &nuevoDepartamento) {
// Actualiza el nombre y/o el departamento de un organizador existente.
    if (organizador == nullptr) {
        return;
    }
    if (!nuevoNombre.empty()) {
        organizador->nombre = nuevoNombre;
    }
    if (!nuevoDepartamento.empty()) {
        organizador->departamento = nuevoDepartamento;
    }
}

// Cuenta la cantidad de eventos asociados a un organizador.
inline size_t contarEventosOrganizador(NodoOrganizador *organizador) {
    size_t cantidad = 0;
    EnlaceOrganizadorEvento *actual = organizador->eventos;
    while (actual != nullptr) {
        ++cantidad;
        actual = actual->siguiente;
    }
    return cantidad;
}

// Elimina un organizador por su ID, desvinculando todos sus eventos y liberando memoria.
inline bool eliminarOrganizadorPorId(const string &id) {
    NodoOrganizador *objetivo = buscarOrganizadorPorId(id);
    if (objetivo == nullptr) {
        return false;
    }
    while (objetivo->eventos != nullptr) {
        NodoEvento *evento = objetivo->eventos->evento;
        desvincularOrganizadorDeEvento(objetivo, evento);
    }
    if (objetivo->anterior != nullptr) {
        objetivo->anterior->siguiente = objetivo->siguiente;
    } else {
        cabezaOrganizadores = objetivo->siguiente;
    }
    if (objetivo->siguiente != nullptr) {
        objetivo->siguiente->anterior = objetivo->anterior;
    } else {
        colaOrganizadores = objetivo->anterior;
    }
    delete objetivo;
    return true;
}

// Muestra en consola todos los organizadores registrados en la lista.
inline void mostrarOrganizadores() {
    cout << "\nOrganizadores registrados:\n";
    NodoOrganizador *actual = cabezaOrganizadores;
    if (actual == nullptr) {
        cout << "No hay organizadores registrados.\n";
        return;
    }
    while (actual != nullptr) {
        cout << "- [" << actual->id << "] " << actual->nombre
                  << " | Departamento: " << actual->departamento
                  << " | Eventos a cargo: " << contarEventosOrganizador(actual) << "\n";
        actual = actual->siguiente;
    }
}

#endif // ORGANIZADORES_CPP
