// Definición de funciones y utilidades para la gestión de categorías
#ifndef CATEGORIAS_CPP
#define CATEGORIAS_CPP

#include <iostream>
#include <string>

#include "estructuras.cpp"

using namespace std;

// Busca una categoría en la lista por su ID. Devuelve un puntero a la categoría si la encuentra, o nullptr si no existe.
inline NodoCategoria *buscarCategoriaPorId(const string &id) {
    NodoCategoria *actual = cabezaCategorias;
    while (actual != nullptr) {
        if (actual->id == id) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

inline NodoCategoria *insertarCategoria(const string &id,
                                        const string &nombre,
                                        const string &descripcion) {
// Crea una nueva categoría y la inserta al final de la lista. Devuelve el puntero a la categoría creada o nullptr si ya existe el ID.
    if (buscarCategoriaPorId(id) != nullptr) {
        return nullptr;
    }
    auto *nodo = new NodoCategoria();
    nodo->id = id;
    nodo->nombre = nombre;
    nodo->descripcion = descripcion;
    if (cabezaCategorias == nullptr) {
        cabezaCategorias = nodo;
    } else {
        NodoCategoria *actual = cabezaCategorias;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nodo;
    }
    return nodo;
}

inline void actualizarCategoria(NodoCategoria *categoria,
                                const string &nuevoNombre,
                                const string &nuevaDescripcion) {
// Actualiza el nombre y/o la descripción de una categoría existente.
    if (categoria == nullptr) {
        return;
    }
    if (!nuevoNombre.empty()) {
        categoria->nombre = nuevoNombre;
    }
    if (!nuevaDescripcion.empty()) {
        categoria->descripcion = nuevaDescripcion;
    }
}

// Verifica si una categoría tiene eventos asociados. Devuelve true si al menos un evento pertenece a la categoría.
inline bool categoriaTieneEventos(NodoCategoria *categoria) {
    NodoEvento *evento = cabezaEventos;
    while (evento != nullptr) {
        if (evento->categoria == categoria) {
            return true;
        }
        evento = evento->siguiente;
    }
    return false;
}

// Elimina una categoría por su ID, solo si no tiene eventos asociados. Libera la memoria del nodo eliminado.
inline bool eliminarCategoriaPorId(const string &id) {
    NodoCategoria *anterior = nullptr;
    NodoCategoria *actual = cabezaCategorias;
    while (actual != nullptr && actual->id != id) {
        anterior = actual;
        actual = actual->siguiente;
    }
    if (actual == nullptr) {
        return false;
    }
    if (categoriaTieneEventos(actual)) {
        return false;
    }
    if (anterior == nullptr) {
        cabezaCategorias = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }
    delete actual;
    return true;
}

// Muestra en consola todas las categorías registradas en la lista.
inline void mostrarCategorias() {
    cout << "\nCategorias registradas:\n";
    NodoCategoria *actual = cabezaCategorias;
    if (actual == nullptr) {
        cout << "No hay categorias ingresadas.\n";
        return;
    }
    while (actual != nullptr) {
        cout << "- [" << actual->id << "] " << actual->nombre
                  << " (" << actual->descripcion << ")\n";
        actual = actual->siguiente;
    }
}

#endif // CATEGORIAS_CPP
