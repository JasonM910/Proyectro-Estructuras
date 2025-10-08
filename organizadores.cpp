#ifndef ORGANIZADORES_CPP
#define ORGANIZADORES_CPP

#include <iostream>
#include <string>

#include "relaciones.cpp"

using namespace std;

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

inline size_t contarEventosOrganizador(NodoOrganizador *organizador) {
    size_t cantidad = 0;
    EnlaceOrganizadorEvento *actual = organizador->eventos;
    while (actual != nullptr) {
        ++cantidad;
        actual = actual->siguiente;
    }
    return cantidad;
}

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

#endif
