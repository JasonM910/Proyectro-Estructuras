#ifndef RELACIONES_CPP
#define RELACIONES_CPP

#include <vector>

#include "estructuras.cpp"

using namespace std;

inline void vincularParticipanteConEvento(NodoParticipante *participante, NodoEvento *evento) {
    if (participante == nullptr || evento == nullptr) {
        return;
    }
    auto *enlaceParticipante = new EnlaceParticipanteEvento();
    enlaceParticipante->evento = evento;
    enlaceParticipante->siguiente = participante->eventos;
    participante->eventos = enlaceParticipante;

    auto *enlaceEvento = new EnlaceEventoParticipante();
    enlaceEvento->participante = participante;
    enlaceEvento->siguiente = evento->participantes;
    evento->participantes = enlaceEvento;
}

inline void desvincularParticipanteDeEvento(NodoParticipante *participante, NodoEvento *evento) {
    if (participante == nullptr || evento == nullptr) {
        return;
    }
    EnlaceParticipanteEvento *prevPE = nullptr;
    EnlaceParticipanteEvento *currPE = participante->eventos;
    while (currPE != nullptr) {
        if (currPE->evento == evento) {
            if (prevPE == nullptr) {
                participante->eventos = currPE->siguiente;
            } else {
                prevPE->siguiente = currPE->siguiente;
            }
            delete currPE;
            break;
        }
        prevPE = currPE;
        currPE = currPE->siguiente;
    }

    EnlaceEventoParticipante *prevEP = nullptr;
    EnlaceEventoParticipante *currEP = evento->participantes;
    while (currEP != nullptr) {
        if (currEP->participante == participante) {
            if (prevEP == nullptr) {
                evento->participantes = currEP->siguiente;
            } else {
                prevEP->siguiente = currEP->siguiente;
            }
            delete currEP;
            break;
        }
        prevEP = currEP;
        currEP = currEP->siguiente;
    }
}

inline bool participanteInscritoEnEvento(NodoParticipante *participante, NodoEvento *evento) {
    EnlaceParticipanteEvento *actual = participante->eventos;
    while (actual != nullptr) {
        if (actual->evento == evento) {
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

inline void vincularOrganizadorConEvento(NodoOrganizador *organizador, NodoEvento *evento) {
    if (organizador == nullptr || evento == nullptr) {
        return;
    }
    auto *enlaceOrganizador = new EnlaceOrganizadorEvento();
    enlaceOrganizador->evento = evento;
    enlaceOrganizador->siguiente = organizador->eventos;
    organizador->eventos = enlaceOrganizador;

    auto *enlaceEvento = new EnlaceEventoOrganizador();
    enlaceEvento->organizador = organizador;
    enlaceEvento->siguiente = evento->organizadores;
    evento->organizadores = enlaceEvento;
}

inline void desvincularOrganizadorDeEvento(NodoOrganizador *organizador, NodoEvento *evento) {
    if (organizador == nullptr || evento == nullptr) {
        return;
    }
    EnlaceOrganizadorEvento *prevOE = nullptr;
    EnlaceOrganizadorEvento *currOE = organizador->eventos;
    while (currOE != nullptr) {
        if (currOE->evento == evento) {
            if (prevOE == nullptr) {
                organizador->eventos = currOE->siguiente;
            } else {
                prevOE->siguiente = currOE->siguiente;
            }
            delete currOE;
            break;
        }
        prevOE = currOE;
        currOE = currOE->siguiente;
    }

    EnlaceEventoOrganizador *prevEO = nullptr;
    EnlaceEventoOrganizador *currEO = evento->organizadores;
    while (currEO != nullptr) {
        if (currEO->organizador == organizador) {
            if (prevEO == nullptr) {
                evento->organizadores = currEO->siguiente;
            } else {
                prevEO->siguiente = currEO->siguiente;
            }
            delete currEO;
            break;
        }
        prevEO = currEO;
        currEO = currEO->siguiente;
    }
}

inline bool organizadorAsignadoEnEvento(NodoOrganizador *organizador, NodoEvento *evento) {
    EnlaceOrganizadorEvento *actual = organizador->eventos;
    while (actual != nullptr) {
        if (actual->evento == evento) {
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

inline void vincularRecursoConEvento(NodoRecurso *recurso, NodoEvento *evento) {
    if (recurso == nullptr || evento == nullptr) {
        return;
    }
    auto *enlaceRecurso = new EnlaceRecursoEvento();
    enlaceRecurso->evento = evento;
    enlaceRecurso->siguiente = recurso->eventos;
    recurso->eventos = enlaceRecurso;

    auto *enlaceEvento = new EnlaceEventoRecurso();
    enlaceEvento->recurso = recurso;
    enlaceEvento->siguiente = evento->recursos;
    evento->recursos = enlaceEvento;
}

inline void desvincularRecursoDeEvento(NodoRecurso *recurso, NodoEvento *evento) {
    if (recurso == nullptr || evento == nullptr) {
        return;
    }
    EnlaceRecursoEvento *prevRE = nullptr;
    EnlaceRecursoEvento *currRE = recurso->eventos;
    while (currRE != nullptr) {
        if (currRE->evento == evento) {
            if (prevRE == nullptr) {
                recurso->eventos = currRE->siguiente;
            } else {
                prevRE->siguiente = currRE->siguiente;
            }
            delete currRE;
            break;
        }
        prevRE = currRE;
        currRE = currRE->siguiente;
    }

    EnlaceEventoRecurso *prevER = nullptr;
    EnlaceEventoRecurso *currER = evento->recursos;
    while (currER != nullptr) {
        if (currER->recurso == recurso) {
            if (prevER == nullptr) {
                evento->recursos = currER->siguiente;
            } else {
                prevER->siguiente = currER->siguiente;
            }
            delete currER;
            break;
        }
        prevER = currER;
        currER = currER->siguiente;
    }
}

inline bool recursoAsignadoEnEvento(NodoRecurso *recurso, NodoEvento *evento) {
    EnlaceRecursoEvento *actual = recurso->eventos;
    while (actual != nullptr) {
        if (actual->evento == evento) {
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

inline void registrarHistorial(const string &id,
                               const Fecha &fecha,
                               NodoParticipante *participante,
                               NodoEvento *evento) {
    auto *nuevo = new NodoHistorial();
    nuevo->id = id;
    nuevo->fecha = fecha;
    nuevo->participante = participante;
    nuevo->evento = evento;

    if (cabezaHistorial == nullptr) {
        cabezaHistorial = nuevo;
        nuevo->siguiente = nuevo;
        return;
    }

    NodoHistorial *actual = cabezaHistorial;
    NodoHistorial *anterior = nullptr;
    do {
        if (fecha < actual->fecha) {
            break;
        }
        anterior = actual;
        actual = actual->siguiente;
    } while (actual != cabezaHistorial);

    if (anterior == nullptr && fecha < cabezaHistorial->fecha) {
        NodoHistorial *cola = cabezaHistorial;
        while (cola->siguiente != cabezaHistorial) {
            cola = cola->siguiente;
        }
        nuevo->siguiente = cabezaHistorial;
        cabezaHistorial = nuevo;
        cola->siguiente = cabezaHistorial;
    } else {
        nuevo->siguiente = anterior->siguiente;
        anterior->siguiente = nuevo;
    }
}

inline void eliminarNodoHistorial(NodoHistorial *objetivo) {
    if (cabezaHistorial == nullptr || objetivo == nullptr) {
        return;
    }
    if (cabezaHistorial == objetivo && cabezaHistorial->siguiente == cabezaHistorial) {
        delete cabezaHistorial;
        cabezaHistorial = nullptr;
        return;
    }
    NodoHistorial *actual = cabezaHistorial;
    NodoHistorial *anterior = nullptr;
    do {
        if (actual == objetivo) {
            if (anterior == nullptr) {
                NodoHistorial *cola = cabezaHistorial;
                while (cola->siguiente != cabezaHistorial) {
                    cola = cola->siguiente;
                }
                cabezaHistorial = cabezaHistorial->siguiente;
                cola->siguiente = cabezaHistorial;
            } else {
                anterior->siguiente = actual->siguiente;
            }
            delete actual;
            return;
        }
        anterior = actual;
        actual = actual->siguiente;
    } while (actual != cabezaHistorial);
}

inline void eliminarHistorialPorEvento(NodoEvento *evento) {
    if (cabezaHistorial == nullptr || evento == nullptr) {
        return;
    }
    vector<NodoHistorial *> aEliminar;
    NodoHistorial *actual = cabezaHistorial;
    do {
        if (actual->evento == evento) {
            aEliminar.push_back(actual);
        }
        actual = actual->siguiente;
    } while (actual != cabezaHistorial);
    for (NodoHistorial *nodo : aEliminar) {
        eliminarNodoHistorial(nodo);
    }
}

inline void eliminarHistorialPorParticipante(NodoParticipante *participante) {
    if (cabezaHistorial == nullptr || participante == nullptr) {
        return;
    }
    vector<NodoHistorial *> aEliminar;
    NodoHistorial *actual = cabezaHistorial;
    do {
        if (actual->participante == participante) {
            aEliminar.push_back(actual);
        }
        actual = actual->siguiente;
    } while (actual != cabezaHistorial);
    for (NodoHistorial *nodo : aEliminar) {
        eliminarNodoHistorial(nodo);
    }
}

#endif
