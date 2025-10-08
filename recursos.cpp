// Definición de funciones y utilidades para la gestión de recursos
#ifndef RECURSOS_CPP
#define RECURSOS_CPP

#include <iostream>
#include <string>

#include "relaciones.cpp"

using namespace std;

// Busca un recurso en la lista por su ID. Devuelve un puntero al recurso si lo encuentra, o nullptr si no existe.
inline NodoRecurso *buscarRecursoPorId(const string &id) {
    NodoRecurso *actual = cabezaRecursos;
    while (actual != nullptr) {
        if (actual->id == id) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

inline NodoRecurso *insertarRecurso(const string &id,
                                    const string &nombre,
                                    const string &descripcion) {
// Crea un nuevo recurso y lo inserta al final de la lista doblemente enlazada. Devuelve el puntero al recurso creado o nullptr si ya existe el ID.
    if (buscarRecursoPorId(id) != nullptr) {
        return nullptr;
    }
    auto *nodo = new NodoRecurso();
    nodo->id = id;
    nodo->nombre = nombre;
    nodo->descripcion = descripcion;
    if (cabezaRecursos == nullptr) {
        cabezaRecursos = nodo;
        colaRecursos = nodo;
    } else {
        colaRecursos->siguiente = nodo;
        nodo->anterior = colaRecursos;
        colaRecursos = nodo;
    }
    return nodo;
}

inline void actualizarRecurso(NodoRecurso *recurso,
                              const string &nuevoNombre,
                              const string &nuevaDescripcion) {
// Actualiza el nombre y/o la descripción de un recurso existente.
    if (recurso == nullptr) {
        return;
    }
    if (!nuevoNombre.empty()) {
        recurso->nombre = nuevoNombre;
    }
    if (!nuevaDescripcion.empty()) {
        recurso->descripcion = nuevaDescripcion;
    }
}

// Cuenta la cantidad de eventos en los que se utiliza un recurso.
inline size_t contarEventosRecurso(NodoRecurso *recurso) {
    size_t cantidad = 0;
    EnlaceRecursoEvento *actual = recurso->eventos;
    while (actual != nullptr) {
        ++cantidad;
        actual = actual->siguiente;
    }
    return cantidad;
}

// Elimina un recurso por su ID, desvinculando todos sus eventos y liberando memoria.
inline bool eliminarRecursoPorId(const string &id) {
    NodoRecurso *objetivo = buscarRecursoPorId(id);
    if (objetivo == nullptr) {
        return false;
    }
    while (objetivo->eventos != nullptr) {
        NodoEvento *evento = objetivo->eventos->evento;
        desvincularRecursoDeEvento(objetivo, evento);
    }
    if (objetivo->anterior != nullptr) {
        objetivo->anterior->siguiente = objetivo->siguiente;
    } else {
        cabezaRecursos = objetivo->siguiente;
    }
    if (objetivo->siguiente != nullptr) {
        objetivo->siguiente->anterior = objetivo->anterior;
    } else {
        colaRecursos = objetivo->anterior;
    }
    delete objetivo;
    return true;
}

// Muestra en consola todos los recursos registrados en la lista.
inline void mostrarRecursos() {
    cout << "\nRecursos registrados:\n";
    NodoRecurso *actual = cabezaRecursos;
    if (actual == nullptr) {
        cout << "No hay recursos registrados.\n";
        return;
    }
    while (actual != nullptr) {
        cout << "- [" << actual->id << "] " << actual->nombre
                  << " | " << actual->descripcion
                  << " | Eventos asignados: " << contarEventosRecurso(actual) << "\n";
        actual = actual->siguiente;
    }
}

#endif // RECURSOS_CPP
