// Definición de funciones y utilidades para la gestión de participantes
#ifndef PARTICIPANTES_CPP
#define PARTICIPANTES_CPP

#include <iostream>
#include <string>

#include "relaciones.cpp"

using namespace std;

// Busca un participante en la lista por su ID. Devuelve un puntero al participante si lo encuentra, o nullptr si no existe.
inline NodoParticipante *buscarParticipantePorId(const string &id) {
    NodoParticipante *actual = cabezaParticipantes;
    while (actual != nullptr) {
        if (actual->id == id) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

inline NodoParticipante *insertarParticipante(const string &id,
                                               const string &nombres,
                                               const string &apellidos,
                                               const string &carrera) {
// Crea un nuevo participante y lo inserta al final de la lista doblemente enlazada. Devuelve el puntero al participante creado o nullptr si ya existe el ID.
    if (buscarParticipantePorId(id) != nullptr) {
        return nullptr;
    }
    auto *nodo = new NodoParticipante();
    nodo->id = id;
    nodo->nombres = nombres;
    nodo->apellidos = apellidos;
    nodo->carrera = carrera;
    if (cabezaParticipantes == nullptr) {
        cabezaParticipantes = nodo;
        colaParticipantes = nodo;
    } else {
        colaParticipantes->siguiente = nodo;
        nodo->anterior = colaParticipantes;
        colaParticipantes = nodo;
    }
    return nodo;
}

inline void actualizarParticipante(NodoParticipante *participante,
                                   const string &nuevosNombres,
                                   const string &nuevosApellidos,
                                   const string &nuevaCarrera) {
// Actualiza los nombres, apellidos y/o carrera de un participante existente.
    if (participante == nullptr) {
        return;
    }
    if (!nuevosNombres.empty()) {
        participante->nombres = nuevosNombres;
    }
    if (!nuevosApellidos.empty()) {
        participante->apellidos = nuevosApellidos;
    }
    if (!nuevaCarrera.empty()) {
        participante->carrera = nuevaCarrera;
    }
}

// Cuenta la cantidad de eventos en los que participa un participante.
inline size_t contarEventosParticipante(NodoParticipante *participante) {
    size_t cantidad = 0;
    EnlaceParticipanteEvento *actual = participante->eventos;
    while (actual != nullptr) {
        ++cantidad;
        actual = actual->siguiente;
    }
    return cantidad;
}

// Elimina un participante por su ID, desvinculando todos sus eventos y eliminando su historial.
inline bool eliminarParticipantePorId(const string &id) {
    NodoParticipante *objetivo = buscarParticipantePorId(id);
    if (objetivo == nullptr) {
        return false;
    }
    while (objetivo->eventos != nullptr) {
        NodoEvento *evento = objetivo->eventos->evento;
        desvincularParticipanteDeEvento(objetivo, evento);
    }
    eliminarHistorialPorParticipante(objetivo);

    if (objetivo->anterior != nullptr) {
        objetivo->anterior->siguiente = objetivo->siguiente;
    } else {
        cabezaParticipantes = objetivo->siguiente;
    }
    if (objetivo->siguiente != nullptr) {
        objetivo->siguiente->anterior = objetivo->anterior;
    } else {
        colaParticipantes = objetivo->anterior;
    }
    delete objetivo;
    return true;
}

// Muestra en consola todos los participantes registrados en la lista.
inline void mostrarParticipantes() {
    cout << "\nParticipantes registrados:\n";
    NodoParticipante *actual = cabezaParticipantes;
    if (actual == nullptr) {
        cout << "No hay participantes registrados.\n";
        return;
    }
    while (actual != nullptr) {
        cout << "- [" << actual->id << "] " << actual->nombres << " " << actual->apellidos
                  << " | Carrera: " << actual->carrera
                  << " | Eventos inscritos: " << contarEventosParticipante(actual) << "\n";
        actual = actual->siguiente;
    }
}

#endif // PARTICIPANTES_CPP
