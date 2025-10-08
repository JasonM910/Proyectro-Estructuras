// Definición de estructuras de datos principales para el sistema de gestión de eventos
#ifndef ESTRUCTURAS_CPP
#define ESTRUCTURAS_CPP

#include <string>

#include "fecha.cpp"

using namespace std;

// Declaraciones adelantadas de las estructuras principales
struct NodoCategoria;
struct NodoEvento;
struct NodoParticipante;
struct NodoOrganizador;
struct NodoRecurso;
struct NodoHistorial;

// Enlace de un participante a un evento (lista de eventos en los que participa un participante)
struct EnlaceParticipanteEvento {
    NodoEvento *evento{nullptr};
    EnlaceParticipanteEvento *siguiente{nullptr};
};

// Enlace de un evento a un participante (lista de participantes de un evento)
struct EnlaceEventoParticipante {
    NodoParticipante *participante{nullptr};
    EnlaceEventoParticipante *siguiente{nullptr};
};

// Enlace de un organizador a un evento (lista de eventos organizados por un organizador)
struct EnlaceOrganizadorEvento {
    NodoEvento *evento{nullptr};
    EnlaceOrganizadorEvento *siguiente{nullptr};
};

// Enlace de un evento a un organizador (lista de organizadores de un evento)
struct EnlaceEventoOrganizador {
    NodoOrganizador *organizador{nullptr};
    EnlaceEventoOrganizador *siguiente{nullptr};
};

// Enlace de un recurso a un evento (lista de eventos donde se usa un recurso)
struct EnlaceRecursoEvento {
    NodoEvento *evento{nullptr};
    EnlaceRecursoEvento *siguiente{nullptr};
};

// Enlace de un evento a un recurso (lista de recursos usados en un evento)
struct EnlaceEventoRecurso {
    NodoRecurso *recurso{nullptr};
    EnlaceEventoRecurso *siguiente{nullptr};
};

// Nodo de la lista de categorías
struct NodoCategoria {
    string id;                // Identificador único de la categoría
    string nombre;            // Nombre de la categoría
    string descripcion;       // Descripción de la categoría
    NodoCategoria *siguiente{nullptr}; // Siguiente categoría en la lista
};

// Nodo de la lista doblemente enlazada de participantes
struct NodoParticipante {
    string id;                        // Identificador único del participante
    string nombres;                   // Nombres del participante
    string apellidos;                 // Apellidos del participante
    string carrera;                   // Carrera o especialidad
    NodoParticipante *anterior{nullptr};
    NodoParticipante *siguiente{nullptr};
    EnlaceParticipanteEvento *eventos{nullptr}; // Lista de eventos en los que participa
};

// Nodo de la lista doblemente enlazada de organizadores
struct NodoOrganizador {
    string id;                        // Identificador único del organizador
    string nombre;                    // Nombre del organizador
    string departamento;              // Departamento al que pertenece
    NodoOrganizador *anterior{nullptr};
    NodoOrganizador *siguiente{nullptr};
    EnlaceOrganizadorEvento *eventos{nullptr}; // Lista de eventos organizados
};

// Nodo de la lista doblemente enlazada de recursos
struct NodoRecurso {
    string id;                        // Identificador único del recurso
    string nombre;                    // Nombre del recurso
    string descripcion;               // Descripción del recurso
    NodoRecurso *anterior{nullptr};
    NodoRecurso *siguiente{nullptr};
    EnlaceRecursoEvento *eventos{nullptr}; // Lista de eventos donde se usa el recurso
};

// Nodo de la lista enlazada de eventos
struct NodoEvento {
    string id;                        // Identificador único del evento
    string nombre;                    // Nombre del evento
    Fecha fecha;                      // Fecha del evento
    string tipo;                      // Tipo de evento
    string lugar;                     // Lugar donde se realiza
    NodoCategoria *categoria{nullptr}; // Categoría a la que pertenece
    NodoEvento *siguiente{nullptr};
    EnlaceEventoParticipante *participantes{nullptr}; // Lista de participantes
    EnlaceEventoOrganizador *organizadores{nullptr}; // Lista de organizadores
    EnlaceEventoRecurso *recursos{nullptr};          // Lista de recursos
};

// Nodo de la lista enlazada de historial de inscripciones o acciones
struct NodoHistorial {
    string id;                        // Identificador único del historial
    Fecha fecha;                      // Fecha de la acción
    NodoParticipante *participante{nullptr}; // Participante involucrado
    NodoEvento *evento{nullptr};      // Evento involucrado
    NodoHistorial *siguiente{nullptr};
};

// Declaración de punteros globales a las cabeceras y colas de las listas principales
extern NodoCategoria *cabezaCategorias;
extern NodoEvento *cabezaEventos;
extern NodoParticipante *cabezaParticipantes;
extern NodoParticipante *colaParticipantes;
extern NodoOrganizador *cabezaOrganizadores;
extern NodoOrganizador *colaOrganizadores;
extern NodoRecurso *cabezaRecursos;
extern NodoRecurso *colaRecursos;
extern NodoHistorial *cabezaHistorial;

#endif // ESTRUCTURAS_CPP
