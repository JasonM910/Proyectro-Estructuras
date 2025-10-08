// Definición de funciones de consulta y reportes estadísticos sobre los datos del sistema
#ifndef CONSULTAS_CPP
#define CONSULTAS_CPP

#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <vector>

#include "eventos.cpp"
#include "participantes.cpp"
#include "organizadores.cpp"
#include "recursos.cpp"

using namespace std;

// Muestra el/los participante(s) que están inscritos en más eventos.
inline void consultaParticipanteConMasEventos() {
    NodoParticipante *actual = cabezaParticipantes;
    size_t maximo = 0;
    vector<NodoParticipante *> ganadores;
    while (actual != nullptr) {
        size_t cantidad = contarEventosParticipante(actual);
        if (cantidad > maximo) {
            ganadores.clear();
            ganadores.push_back(actual);
            maximo = cantidad;
        } else if (cantidad == maximo) {
            ganadores.push_back(actual);
        }
        actual = actual->siguiente;
    }
    if (maximo == 0) {
        cout << "Ningun participante se ha inscrito en eventos.\n";
        return;
    }
    cout << "Participante(s) con mas eventos (" << maximo << "):\n";
    for (NodoParticipante *p : ganadores) {
        cout << "- " << p->nombres << " " << p->apellidos << "\n";
    }
}

// Muestra el/los organizador(es) que están asignados a más eventos.
inline void consultaOrganizadorConMasEventos() {
    NodoOrganizador *actual = cabezaOrganizadores;
    size_t maximo = 0;
    vector<NodoOrganizador *> ganadores;
    while (actual != nullptr) {
        size_t cantidad = contarEventosOrganizador(actual);
        if (cantidad > maximo) {
            ganadores.clear();
            ganadores.push_back(actual);
            maximo = cantidad;
        } else if (cantidad == maximo) {
            ganadores.push_back(actual);
        }
        actual = actual->siguiente;
    }
    if (maximo == 0) {
        cout << "No hay organizadores con eventos asignados.\n";
        return;
    }
    cout << "Organizador(es) con mas eventos (" << maximo << "):\n";
    for (NodoOrganizador *o : ganadores) {
        cout << "- " << o->nombre << " | Departamento: " << o->departamento << "\n";
    }
}

// Muestra el/los tipo(s) de evento más frecuente(s) según la cantidad de ocurrencias.
inline void consultaTipoEventoMasFrecuente() {
    map<string, int> conteos;
    NodoEvento *actual = cabezaEventos;
    while (actual != nullptr) {
        conteos[actual->tipo]++;
        actual = actual->siguiente;
    }
    if (conteos.empty()) {
        cout << "No hay eventos registrados.\n";
        return;
    }
    int maximo = 0;
    for (const auto &par : conteos) {
        if (par.second > maximo) {
            maximo = par.second;
        }
    }
    cout << "Tipo(s) de evento mas frecuente(s) con " << maximo << " ocurrencias:\n";
    for (const auto &par : conteos) {
        if (par.second == maximo) {
            cout << "- " << par.first << "\n";
        }
    }
}

// Muestra la(s) categoría(s) con mayor cantidad de participantes sumando todos sus eventos.
inline void consultaCategoriaConMayorParticipacion() {
    if (cabezaCategorias == nullptr || cabezaEventos == nullptr) {
        cout << "No hay datos suficientes.\n";
        return;
    }
    map<NodoCategoria *, int> conteos;
    NodoEvento *evento = cabezaEventos;
    while (evento != nullptr) {
        conteos[evento->categoria] += static_cast<int>(contarParticipantesEvento(evento));
        evento = evento->siguiente;
    }
    int maximo = 0;
    vector<NodoCategoria *> ganadores;
    for (const auto &par : conteos) {
        if (par.second > maximo) {
            ganadores.clear();
            ganadores.push_back(par.first);
            maximo = par.second;
        } else if (par.second == maximo) {
            ganadores.push_back(par.first);
        }
    }
    if (maximo == 0) {
        cout << "No hay participantes registrados en eventos.\n";
        return;
    }
    cout << "Categoria(s) con mayor participacion (" << maximo << "):\n";
    for (NodoCategoria *categoria : ganadores) {
        if (categoria != nullptr) {
            cout << "- " << categoria->nombre << "\n";
        }
    }
}

// Muestra el/los recurso(s) que han sido utilizados en más eventos.
inline void consultaRecursoMasUtilizado() {
    NodoRecurso *actual = cabezaRecursos;
    size_t maximo = 0;
    vector<NodoRecurso *> ganadores;
    while (actual != nullptr) {
        size_t cantidad = contarEventosRecurso(actual);
        if (cantidad > maximo) {
            ganadores.clear();
            ganadores.push_back(actual);
            maximo = cantidad;
        } else if (cantidad == maximo) {
            ganadores.push_back(actual);
        }
        actual = actual->siguiente;
    }
    if (maximo == 0) {
        cout << "No hay recursos asignados a eventos.\n";
        return;
    }
    cout << "Recurso(s) mas utilizado(s) (" << maximo << " eventos):\n";
    for (NodoRecurso *recurso : ganadores) {
        cout << "- " << recurso->nombre << "\n";
    }
}

// Muestra el/los lugar(es) donde se han realizado más eventos.
inline void consultaLugarMasFrecuente() {
    map<string, int> conteos;
    NodoEvento *actual = cabezaEventos;
    while (actual != nullptr) {
        conteos[actual->lugar]++;
        actual = actual->siguiente;
    }
    if (conteos.empty()) {
        cout << "No hay eventos registrados.\n";
        return;
    }
    int maximo = 0;
    for (const auto &par : conteos) {
        if (par.second > maximo) {
            maximo = par.second;
        }
    }
    vector<string> ganadores;
    for (const auto &par : conteos) {
        if (par.second == maximo) {
            ganadores.push_back(par.first);
        }
    }
    if (ganadores.size() == 1) {
        cout << "El lugar con mas eventos es: " << ganadores.front()
                  << " con " << maximo << " eventos.\n";
    } else {
        cout << "Empate entre lugares (" << maximo << " eventos cada uno):\n";
        for (const auto &lugar : ganadores) {
            cout << "- " << lugar << "\n";
        }
    }
}

// Muestra el/los evento(s) con mayor cantidad de participantes.
inline void consultaEventoConMasParticipantes() {
    NodoEvento *actual = cabezaEventos;
    size_t maximo = 0;
    vector<NodoEvento *> ganadores;
    while (actual != nullptr) {
        size_t cantidad = contarParticipantesEvento(actual);
        if (cantidad > maximo) {
            ganadores.clear();
            ganadores.push_back(actual);
            maximo = cantidad;
        } else if (cantidad == maximo) {
            ganadores.push_back(actual);
        }
        actual = actual->siguiente;
    }
    if (maximo == 0) {
        cout << "No hay participantes registrados.\n";
        return;
    }
    cout << "Evento(s) con mas participantes (" << maximo << "):\n";
    for (NodoEvento *evento : ganadores) {
        cout << "- " << evento->nombre << " | Fecha: " << evento->fecha.aTexto() << "\n";
    }
}

// Muestra el/los organizador(es) que han gestionado eventos de más categorías distintas.
inline void consultaOrganizadorConMasCategorias() {
    NodoOrganizador *actual = cabezaOrganizadores;
    size_t maximo = 0;
    vector<NodoOrganizador *> ganadores;
    map<NodoOrganizador *, set<string>> categoriasPorOrganizador;

    while (actual != nullptr) {
        set<string> categorias;
        EnlaceOrganizadorEvento *enlace = actual->eventos;
        while (enlace != nullptr) {
            if (enlace->evento != nullptr && enlace->evento->categoria != nullptr) {
                categorias.insert(enlace->evento->categoria->nombre);
            }
            enlace = enlace->siguiente;
        }
        categoriasPorOrganizador[actual] = categorias;
        if (categorias.size() > maximo) {
            ganadores.clear();
            ganadores.push_back(actual);
            maximo = categorias.size();
        } else if (categorias.size() == maximo) {
            ganadores.push_back(actual);
        }
        actual = actual->siguiente;
    }

    if (maximo == 0) {
        cout << "No hay organizadores con categorias multiples asignadas.\n";
        return;
    }

    cout << "Organizador(es) con mas categorias distintas (" << maximo << "):\n";
    for (NodoOrganizador *organizador : ganadores) {
        cout << "- " << organizador->nombre << " | Categorias: ";
        const auto &categorias = categoriasPorOrganizador[organizador];
        bool primero = true;
        for (const auto &nombreCategoria : categorias) {
            if (!primero) {
                cout << ", ";
            }
            cout << nombreCategoria;
            primero = false;
        }
        cout << "\n";
    }
}

// Muestra el porcentaje de participantes activos (con al menos un evento) e inactivos.
inline void consultaPorcentajeParticipacion() {
    size_t total = 0;
    size_t conEventos = 0;
    NodoParticipante *actual = cabezaParticipantes;
    while (actual != nullptr) {
        ++total;
        if (contarEventosParticipante(actual) > 0) {
            ++conEventos;
        }
        actual = actual->siguiente;
    }
    if (total == 0) {
        cout << "No hay participantes registrados.\n";
        return;
    }
    double porcentajeActivos = (static_cast<double>(conEventos) / static_cast<double>(total)) * 100.0;
    double porcentajeInactivos = 100.0 - porcentajeActivos;
    cout << fixed << setprecision(2);
    cout << "Participantes con al menos un evento: " << porcentajeActivos << "%\n";
    cout << "Participantes sin eventos: " << porcentajeInactivos << "%\n";
}

#endif // CONSULTAS_CPP
