#ifndef REPORTES_CPP
#define REPORTES_CPP

#include <algorithm>
#include <iostream>
#include <vector>

#include "consultas.cpp"

using namespace std;

inline void reporteParticipantesPorApellido() {
    vector<NodoParticipante *> participantes;
    NodoParticipante *actual = cabezaParticipantes;
    while (actual != nullptr) {
        participantes.push_back(actual);
        actual = actual->siguiente;
    }
    if (participantes.empty()) {
        cout << "No hay participantes registrados.\n";
        return;
    }
    auto comparador = [](NodoParticipante *a, NodoParticipante *b) {
        if (a->apellidos == b->apellidos) {
            return a->nombres < b->nombres;
        }
        return a->apellidos < b->apellidos;
    };
    sort(participantes.begin(), participantes.end(), comparador);
    cout << "Orden ascendente por apellido:\n";
    for (NodoParticipante *p : participantes) {
        cout << "- " << p->apellidos << ", " << p->nombres
                  << " | Carrera: " << p->carrera
                  << " | Eventos: " << contarEventosParticipante(p) << "\n";
    }
    reverse(participantes.begin(), participantes.end());
    cout << "\nOrden descendente por apellido:\n";
    for (NodoParticipante *p : participantes) {
        cout << "- " << p->apellidos << ", " << p->nombres
                  << " | Carrera: " << p->carrera
                  << " | Eventos: " << contarEventosParticipante(p) << "\n";
    }
}

inline void reporteEventosPorOrganizador(NodoOrganizador *organizador) {
    if (organizador == nullptr) {
        cout << "Organizador no encontrado.\n";
        return;
    }
    cout << "Eventos organizados por " << organizador->nombre << ":\n";
    EnlaceOrganizadorEvento *enlace = organizador->eventos;
    if (enlace == nullptr) {
        cout << "No tiene eventos asignados.\n";
        return;
    }
    while (enlace != nullptr) {
        if (enlace->evento != nullptr) {
            mostrarEventoDetallado(enlace->evento);
        }
        enlace = enlace->siguiente;
    }
}

inline void reporteEventosPorCategoria(NodoCategoria *categoria) {
    if (categoria == nullptr) {
        cout << "Categoria no encontrada.\n";
        return;
    }
    cout << "Eventos de la categoria " << categoria->nombre << ":\n";
    NodoEvento *actual = cabezaEventos;
    bool alguno = false;
    while (actual != nullptr) {
        if (actual->categoria == categoria) {
            cout << "- [" << actual->id << "] " << actual->nombre
                 << " | Fecha: " << actual->fecha.aTexto()
                 << " | Tipo: " << actual->tipo
                 << " | Lugar: " << actual->lugar << "\n";

            cout << "  Organizadores: ";
            EnlaceEventoOrganizador *org = actual->organizadores;
            if (org == nullptr) {
                cout << "No hay organizadores asignados.\n";
            } else {
                bool primero = true;
                while (org != nullptr) {
                    if (org->organizador != nullptr) {
                        if (!primero) {
                            cout << ", ";
                        }
                        cout << org->organizador->nombre;
                        primero = false;
                    }
                    org = org->siguiente;
                }
                cout << "\n";
            }
            alguno = true;
        }
        actual = actual->siguiente;
    }
    if (!alguno) {
        cout << "No hay eventos para esta categoria.\n";
    }
}

inline void reporteRecursosPorEvento(NodoEvento *evento) {
    if (evento == nullptr) {
        cout << "Evento no encontrado.\n";
        return;
    }
    cout << "Recursos asignados al evento " << evento->nombre << ":\n";
    EnlaceEventoRecurso *enlace = evento->recursos;
    if (enlace == nullptr) {
        cout << "No se han asignado recursos.\n";
        return;
    }
    while (enlace != nullptr) {
        if (enlace->recurso != nullptr) {
            cout << "- " << enlace->recurso->nombre << " (" << enlace->recurso->descripcion << ")\n";
        }
        enlace = enlace->siguiente;
    }
}

inline void reporteEventosPorLugar(const string &lugar) {
    NodoEvento *actual = cabezaEventos;
    bool alguno = false;
    while (actual != nullptr) {
        if (actual->lugar == lugar) {
            mostrarEventoDetallado(actual);
            alguno = true;
        }
        actual = actual->siguiente;
    }
    if (!alguno) {
        cout << "No hay eventos registrados para ese lugar.\n";
    }
}

inline void reporteTalleresPorDepartamento(const string &departamento) {
    NodoOrganizador *actual = cabezaOrganizadores;
    bool alguno = false;
    while (actual != nullptr) {
        if (actual->departamento == departamento) {
            EnlaceOrganizadorEvento *enlace = actual->eventos;
            while (enlace != nullptr) {
                NodoEvento *evento = enlace->evento;
                if (evento != nullptr && evento->tipo == "taller") {
                    cout << "- Evento: " << evento->nombre
                              << " | Fecha: " << evento->fecha.aTexto()
                              << " | Organizador: " << actual->nombre
                              << " | Lugar: " << evento->lugar << "\n";
                    alguno = true;
                }
                enlace = enlace->siguiente;
            }
        }
        actual = actual->siguiente;
    }
    if (!alguno) {
        cout << "No se encontraron talleres para el departamento indicado.\n";
    }
}

inline void reporteHistorialInscripciones() {
    if (cabezaHistorial == nullptr) {
        cout << "No hay inscripciones registradas.\n";
        return;
    }
    cout << "Historial de inscripciones (ordenado por fecha):\n";
    NodoHistorial *actual = cabezaHistorial;
    do {
        cout << "- [" << actual->id << "] " << actual->fecha.aTexto()
                  << " | Estudiante: " << (actual->participante != nullptr ? actual->participante->nombres + " " + actual->participante->apellidos : "Desconocido")
                  << " | Evento: " << (actual->evento != nullptr ? actual->evento->nombre : "Desconocido") << "\n";
        actual = actual->siguiente;
    } while (actual != cabezaHistorial);
}

inline void reporteOrganizadoresSinEventos() {
    NodoOrganizador *actual = cabezaOrganizadores;
    bool alguno = false;
    while (actual != nullptr) {
        if (actual->eventos == nullptr) {
            cout << "- " << actual->nombre << " | Departamento: " << actual->departamento << "\n";
            alguno = true;
        }
        actual = actual->siguiente;
    }
    if (!alguno) {
        cout << "Todos los organizadores tienen eventos asignados.\n";
    }
}

#endif
