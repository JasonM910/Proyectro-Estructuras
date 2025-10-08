// Definición de funciones y utilidades para la gestión de eventos
#ifndef EVENTOS_CPP
#define EVENTOS_CPP

#include <iostream>
#include <string>

#include "relaciones.cpp"

using namespace std;

// Busca un evento en la lista por su ID. Devuelve un puntero al evento si lo encuentra, o nullptr si no existe.
inline NodoEvento *buscarEventoPorId(const string &id) {
    NodoEvento *actual = cabezaEventos;
    while (actual != nullptr) {
        if (actual->id == id) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

// Inserta un evento en la lista enlazada de eventos, manteniendo el orden por fecha.
inline void insertarEventoEnListaOrdenada(NodoEvento *evento) {
    if (cabezaEventos == nullptr || evento->fecha < cabezaEventos->fecha) {
        evento->siguiente = cabezaEventos;
        cabezaEventos = evento;
        return;
    }
    NodoEvento *actual = cabezaEventos;
    while (actual->siguiente != nullptr && !(evento->fecha < actual->siguiente->fecha)) {
        actual = actual->siguiente;
    }
    evento->siguiente = actual->siguiente;
    actual->siguiente = evento;
}

inline NodoEvento *insertarEventoOrdenado(const string &id,
                                          const string &nombre,
                                          const Fecha &fecha,
                                          const string &tipo,
                                          const string &lugar,
                                          NodoCategoria *categoria) {
// Crea un nuevo evento y lo inserta ordenadamente en la lista. Devuelve el puntero al evento creado o nullptr si ya existe el ID o la categoría es nula.
    if (buscarEventoPorId(id) != nullptr || categoria == nullptr) {
        return nullptr;
    }
    auto *evento = new NodoEvento();
    evento->id = id;
    evento->nombre = nombre;
    evento->fecha = fecha;
    evento->tipo = tipo;
    evento->lugar = lugar;
    evento->categoria = categoria;
    insertarEventoEnListaOrdenada(evento);
    return evento;
}

// Elimina un evento de la lista enlazada de eventos, sin liberar memoria.
inline void removerEventoDeLista(NodoEvento *evento) {
    if (cabezaEventos == nullptr || evento == nullptr) {
        return;
    }
    if (cabezaEventos == evento) {
        cabezaEventos = cabezaEventos->siguiente;
        evento->siguiente = nullptr;
        return;
    }
    NodoEvento *actual = cabezaEventos;
    while (actual->siguiente != nullptr && actual->siguiente != evento) {
        actual = actual->siguiente;
    }
    if (actual->siguiente == evento) {
        actual->siguiente = evento->siguiente;
        evento->siguiente = nullptr;
    }
}

inline void actualizarEvento(NodoEvento *evento,
                             const string &nuevoNombre,
                             const Fecha *nuevaFecha,
                             const string &nuevoTipo,
                             const string &nuevoLugar,
                             NodoCategoria *nuevaCategoria) {
// Actualiza los datos de un evento existente. Si la fecha cambia, reubica el evento en la lista ordenada.
    if (evento == nullptr) {
        return;
    }
    if (!nuevoNombre.empty()) {
        evento->nombre = nuevoNombre;
    }
    if (nuevaFecha != nullptr && !(evento->fecha == *nuevaFecha)) {
        removerEventoDeLista(evento);
        evento->fecha = *nuevaFecha;
        insertarEventoEnListaOrdenada(evento);
    }
    if (!nuevoTipo.empty()) {
        evento->tipo = nuevoTipo;
    }
    if (!nuevoLugar.empty()) {
        evento->lugar = nuevoLugar;
    }
    if (nuevaCategoria != nullptr) {
        evento->categoria = nuevaCategoria;
    }
}

// Cuenta la cantidad de participantes asociados a un evento.
inline size_t contarParticipantesEvento(NodoEvento *evento) {
    size_t cantidad = 0;
    EnlaceEventoParticipante *actual = evento->participantes;
    while (actual != nullptr) {
        ++cantidad;
        actual = actual->siguiente;
    }
    return cantidad;
}

// Cuenta la cantidad de organizadores asociados a un evento.
inline size_t contarOrganizadoresEvento(NodoEvento *evento) {
    size_t cantidad = 0;
    EnlaceEventoOrganizador *actual = evento->organizadores;
    while (actual != nullptr) {
        ++cantidad;
        actual = actual->siguiente;
    }
    return cantidad;
}

// Cuenta la cantidad de recursos asociados a un evento.
inline size_t contarRecursosEvento(NodoEvento *evento) {
    size_t cantidad = 0;
    EnlaceEventoRecurso *actual = evento->recursos;
    while (actual != nullptr) {
        ++cantidad;
        actual = actual->siguiente;
    }
    return cantidad;
}

// Muestra en consola la información detallada de un evento, incluyendo participantes, organizadores y recursos.
inline void mostrarEventoDetallado(NodoEvento *evento) {
    cout << "- [" << evento->id << "] " << evento->nombre
              << " | Fecha: " << evento->fecha.aTexto()
              << " | Tipo: " << evento->tipo
              << " | Lugar: " << evento->lugar
              << " | Categoria: " << (evento->categoria != nullptr ? evento->categoria->nombre : "Sin categoria") << "\n";
    cout << "  Participantes: " << contarParticipantesEvento(evento)
              << " | Organizadores: " << contarOrganizadoresEvento(evento)
              << " | Recursos: " << contarRecursosEvento(evento) << "\n";
}

// Muestra en consola todos los eventos registrados en la lista.
inline void mostrarEventos() {
    cout << "\nEventos registrados:\n";
    NodoEvento *actual = cabezaEventos;
    if (actual == nullptr) {
        cout << "No hay eventos registrados.\n";
        return;
    }
    while (actual != nullptr) {
        mostrarEventoDetallado(actual);
        actual = actual->siguiente;
    }
}

// Elimina todos los enlaces de participantes, organizadores y recursos asociados a un evento.
inline void eliminarEnlacesEvento(NodoEvento *evento) {
    while (evento->participantes != nullptr) {
        NodoParticipante *participante = evento->participantes->participante;
        desvincularParticipanteDeEvento(participante, evento);
    }
    while (evento->organizadores != nullptr) {
        NodoOrganizador *organizador = evento->organizadores->organizador;
        desvincularOrganizadorDeEvento(organizador, evento);
    }
    while (evento->recursos != nullptr) {
        NodoRecurso *recurso = evento->recursos->recurso;
        desvincularRecursoDeEvento(recurso, evento);
    }
}

// Elimina un evento por su ID, desvinculando todos sus enlaces y liberando memoria.
inline bool eliminarEventoPorId(const string &id) {
    NodoEvento *objetivo = buscarEventoPorId(id);
    if (objetivo == nullptr) {
        return false;
    }
    eliminarEnlacesEvento(objetivo);
    eliminarHistorialPorEvento(objetivo);
    removerEventoDeLista(objetivo);
    delete objetivo;
    return true;
}

#endif // EVENTOS_CPP
