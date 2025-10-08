#ifndef ESTRUCTURAS_CPP
#define ESTRUCTURAS_CPP

#include <string>

#include "fecha.cpp"

using namespace std;

struct NodoCategoria;
struct NodoEvento;
struct NodoParticipante;
struct NodoOrganizador;
struct NodoRecurso;
struct NodoHistorial;

struct EnlaceParticipanteEvento {
    NodoEvento *evento{nullptr};
    EnlaceParticipanteEvento *siguiente{nullptr};
};

struct EnlaceEventoParticipante {
    NodoParticipante *participante{nullptr};
    EnlaceEventoParticipante *siguiente{nullptr};
};

struct EnlaceOrganizadorEvento {
    NodoEvento *evento{nullptr};
    EnlaceOrganizadorEvento *siguiente{nullptr};
};

struct EnlaceEventoOrganizador {
    NodoOrganizador *organizador{nullptr};
    EnlaceEventoOrganizador *siguiente{nullptr};
};

struct EnlaceRecursoEvento {
    NodoEvento *evento{nullptr};
    EnlaceRecursoEvento *siguiente{nullptr};
};

struct EnlaceEventoRecurso {
    NodoRecurso *recurso{nullptr};
    EnlaceEventoRecurso *siguiente{nullptr};
};

struct NodoCategoria {
    string id;
    string nombre;
    string descripcion;
    NodoCategoria *siguiente{nullptr};
};

struct NodoParticipante {
    string id;
    string nombres;
    string apellidos;
    string carrera;
    NodoParticipante *anterior{nullptr};
    NodoParticipante *siguiente{nullptr};
    EnlaceParticipanteEvento *eventos{nullptr};
};

struct NodoOrganizador {
    string id;
    string nombre;
    string departamento;
    NodoOrganizador *anterior{nullptr};
    NodoOrganizador *siguiente{nullptr};
    EnlaceOrganizadorEvento *eventos{nullptr};
};

struct NodoRecurso {
    string id;
    string nombre;
    string descripcion;
    NodoRecurso *anterior{nullptr};
    NodoRecurso *siguiente{nullptr};
    EnlaceRecursoEvento *eventos{nullptr};
};

struct NodoEvento {
    string id;
    string nombre;
    Fecha fecha;
    string tipo;
    string lugar;
    NodoCategoria *categoria{nullptr};
    NodoEvento *siguiente{nullptr};
    EnlaceEventoParticipante *participantes{nullptr};
    EnlaceEventoOrganizador *organizadores{nullptr};
    EnlaceEventoRecurso *recursos{nullptr};
};

struct NodoHistorial {
    string id;
    Fecha fecha;
    NodoParticipante *participante{nullptr};
    NodoEvento *evento{nullptr};
    NodoHistorial *siguiente{nullptr};
};

extern NodoCategoria *cabezaCategorias;
extern NodoEvento *cabezaEventos;
extern NodoParticipante *cabezaParticipantes;
extern NodoParticipante *colaParticipantes;
extern NodoOrganizador *cabezaOrganizadores;
extern NodoOrganizador *colaOrganizadores;
extern NodoRecurso *cabezaRecursos;
extern NodoRecurso *colaRecursos;
extern NodoHistorial *cabezaHistorial;

#endif
