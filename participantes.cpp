#ifndef PARTICIPANTES_CPP
#define PARTICIPANTES_CPP

#include <iostream>
#include <string>

#include "relaciones.cpp"

using namespace std;

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

inline size_t contarEventosParticipante(NodoParticipante *participante) {
    size_t cantidad = 0;
    EnlaceParticipanteEvento *actual = participante->eventos;
    while (actual != nullptr) {
        ++cantidad;
        actual = actual->siguiente;
    }
    return cantidad;
}

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

#endif
