#include <iostream>
#include <string>

#include "utilidades.cpp"
#include "categorias.cpp"
#include "reportes.cpp"

using namespace std;

NodoCategoria *cabezaCategorias = nullptr;
NodoEvento *cabezaEventos = nullptr;
NodoParticipante *cabezaParticipantes = nullptr;
NodoParticipante *colaParticipantes = nullptr;
NodoOrganizador *cabezaOrganizadores = nullptr;
NodoOrganizador *colaOrganizadores = nullptr;
NodoRecurso *cabezaRecursos = nullptr;
NodoRecurso *colaRecursos = nullptr;
NodoHistorial *cabezaHistorial = nullptr;

void cargarDatosIniciales();
void liberarMemoria();

void menuCategorias();
void menuEventos();
void menuParticipantes();
void menuOrganizadores();
void menuRecursos();
void menuInscripciones();
void menuOrganizadoresEvento();
void menuRecursosEvento();
void registrarInscripcion();
void modificarInscripcion();
void cancelarInscripcion();
void mostrarParticipantesDeEvento();
void buscarInscripcion();
void asignarOrganizadorEvento();
void reasignarOrganizadorEvento();
void retirarOrganizadorEvento();
void mostrarOrganizadoresEvento();
void buscarOrganizadorEvento();
void asignarRecursoEvento();
void reasignarRecursoEvento();
void retirarRecursoEvento();
void mostrarRecursosEvento();
void buscarRecursoEvento();
void menuConsultas();
void menuReportes();

int main();
void cargarDatosIniciales() {
    NodoCategoria *catAcademico = insertarCategoria("CAT01", "Academico", "Charlas y conferencias");
    NodoCategoria *catCultural = insertarCategoria("CAT02", "Cultural", "Ferias y presentaciones");
    NodoCategoria *catDeportivo = insertarCategoria("CAT03", "Deportivo", "Actividades fisicas");

    NodoParticipante *p1 = insertarParticipante("P001", "Laura", "Gomez", "Ingenieria");
    NodoParticipante *p2 = insertarParticipante("P002", "Carlos", "Ramirez", "Medicina");
    NodoParticipante *p3 = insertarParticipante("P003", "Ana", "Martinez", "Derecho");
    NodoParticipante *p4 = insertarParticipante("P004", "Jose", "Pineda", "Arquitectura");
    NodoParticipante *p5 = insertarParticipante("P005", "Maria", "Sanchez", "Psicologia");

    NodoOrganizador *o1 = insertarOrganizador("O001", "Dra. Paula Herrera", "Decanato Academico");
    NodoOrganizador *o2 = insertarOrganizador("O002", "Ing. Mario Lopez", "Departamento de Sistemas");
    NodoOrganizador *o3 = insertarOrganizador("O003", "Lic. Sofia Torres", "Bienestar Universitario");

    NodoRecurso *r1 = insertarRecurso("R001", "Proyector Epson", "HDMI y VGA");
    NodoRecurso *r2 = insertarRecurso("R002", "Sala Magna", "Capacidad 200 personas");
    NodoRecurso *r3 = insertarRecurso("R003", "Kit de Robotica", "Componentes electronicos");

    Fecha f1{2025, 5, 10};
    Fecha f2{2025, 5, 15};
    Fecha f3{2025, 6, 1};
    Fecha f4{2025, 6, 5};
    Fecha f5{2025, 6, 20};

    NodoEvento *e1 = insertarEventoOrdenado("E001", "Charla de Innovacion", f1, "charla", "Auditorio Central", catAcademico);
    NodoEvento *e2 = insertarEventoOrdenado("E002", "Feria Cultural", f2, "feria", "Plaza Central", catCultural);
    NodoEvento *e3 = insertarEventoOrdenado("E003", "Taller de Programacion", f3, "taller", "Laboratorio 3", catAcademico);
    NodoEvento *e4 = insertarEventoOrdenado("E004", "Encuentro Deportivo", f4, "competencia", "Gimnasio", catDeportivo);
    NodoEvento *e5 = insertarEventoOrdenado("E005", "Taller de Expresion Artistica", f5, "taller", "Sala de Arte", catCultural);

    vincularOrganizadorConEvento(o1, e1);
    vincularOrganizadorConEvento(o2, e3);
    vincularOrganizadorConEvento(o3, e2);
    vincularOrganizadorConEvento(o3, e5);
    vincularOrganizadorConEvento(o2, e5);
    vincularOrganizadorConEvento(o1, e4);

    vincularRecursoConEvento(r1, e1);
    vincularRecursoConEvento(r2, e1);
    vincularRecursoConEvento(r3, e3);
    vincularRecursoConEvento(r2, e2);
    vincularRecursoConEvento(r2, e4);
    vincularRecursoConEvento(r1, e3);

    vincularParticipanteConEvento(p1, e1);
    vincularParticipanteConEvento(p1, e3);
    vincularParticipanteConEvento(p2, e1);
    vincularParticipanteConEvento(p2, e4);
    vincularParticipanteConEvento(p3, e2);
    vincularParticipanteConEvento(p3, e5);
    vincularParticipanteConEvento(p4, e4);
    vincularParticipanteConEvento(p5, e5);

    registrarHistorial("H001", f1, p1, e1);
    registrarHistorial("H002", f1, p2, e1);
    registrarHistorial("H003", f2, p3, e2);
    registrarHistorial("H004", f3, p1, e3);
    registrarHistorial("H005", f5, p5, e5);
}
void liberarMemoria() {
    while (cabezaEventos != nullptr) {
        NodoEvento *siguiente = cabezaEventos->siguiente;
        eliminarEnlacesEvento(cabezaEventos);
        eliminarHistorialPorEvento(cabezaEventos);
        delete cabezaEventos;
        cabezaEventos = siguiente;
    }

    while (cabezaCategorias != nullptr) {
        NodoCategoria *siguiente = cabezaCategorias->siguiente;
        delete cabezaCategorias;
        cabezaCategorias = siguiente;
    }

    while (cabezaParticipantes != nullptr) {
        while (cabezaParticipantes->eventos != nullptr) {
            NodoEvento *evento = cabezaParticipantes->eventos->evento;
            desvincularParticipanteDeEvento(cabezaParticipantes, evento);
        }
        NodoParticipante *siguiente = cabezaParticipantes->siguiente;
        delete cabezaParticipantes;
        cabezaParticipantes = siguiente;
    }
    colaParticipantes = nullptr;

    while (cabezaOrganizadores != nullptr) {
        while (cabezaOrganizadores->eventos != nullptr) {
            NodoEvento *evento = cabezaOrganizadores->eventos->evento;
            desvincularOrganizadorDeEvento(cabezaOrganizadores, evento);
        }
        NodoOrganizador *siguiente = cabezaOrganizadores->siguiente;
        delete cabezaOrganizadores;
        cabezaOrganizadores = siguiente;
    }
    colaOrganizadores = nullptr;

    while (cabezaRecursos != nullptr) {
        while (cabezaRecursos->eventos != nullptr) {
            NodoEvento *evento = cabezaRecursos->eventos->evento;
            desvincularRecursoDeEvento(cabezaRecursos, evento);
        }
        NodoRecurso *siguiente = cabezaRecursos->siguiente;
        delete cabezaRecursos;
        cabezaRecursos = siguiente;
    }
    colaRecursos = nullptr;

    if (cabezaHistorial != nullptr) {
        NodoHistorial *actual = cabezaHistorial->siguiente;
        while (actual != nullptr && actual != cabezaHistorial) {
            NodoHistorial *siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
        delete cabezaHistorial;
        cabezaHistorial = nullptr;
    }
}
void menuCategorias() {
    bool volver = false;
    while (!volver) {
        cout << "\n--- Gestion de categorias ---\n";
        cout << "1. Insertar categoria\n";
        cout << "2. Modificar categoria\n";
        cout << "3. Eliminar categoria\n";
        cout << "4. Buscar categoria\n";
        cout << "5. Mostrar categorias\n";
        cout << "0. Volver\n";
        cout << "Seleccione una opcion: ";
        int opcion = leerEntero();

        switch (opcion) {
            case 1: {
                string id = leerCadena("ID: ");
                if (buscarCategoriaPorId(id) != nullptr) {
                    cout << "Ya existe una categoria con ese ID.\n";
                    break;
                }
                string nombre = leerCadena("Nombre: ");
                string descripcion = leerCadena("Descripcion: ");
                if (insertarCategoria(id, nombre, descripcion) != nullptr) {
                    cout << "Categoria creada.\n";
                } else {
                    cout << "No se pudo crear la categoria.\n";
                }
                break;
            }
            case 2: {
                string id = leerCadena("Ingrese el ID de la categoria a modificar: ");
                NodoCategoria *categoria = buscarCategoriaPorId(id);
                if (categoria == nullptr) {
                    cout << "Categoria no encontrada.\n";
                    break;
                }
                string nuevoNombre = leerCadena("Nuevo nombre (" + categoria->nombre + "): ");
                string nuevaDescripcion = leerCadena("Nueva descripcion (" + categoria->descripcion + "): ");
                actualizarCategoria(categoria, nuevoNombre, nuevaDescripcion);
                cout << "Categoria actualizada.\n";
                break;
            }
            case 3: {
                string id = leerCadena("Ingrese el ID de la categoria a eliminar: ");
                NodoCategoria *categoria = buscarCategoriaPorId(id);
                if (categoria == nullptr) {
                    cout << "Categoria no encontrada.\n";
                    break;
                }
                if (categoriaTieneEventos(categoria)) {
                    cout << "No se puede eliminar la categoria porque tiene eventos asociados.\n";
                    break;
                }
                eliminarCategoriaPorId(id);
                cout << "Categoria eliminada.\n";
                break;
            }
            case 4: {
                string id = leerCadena("Ingrese el ID de la categoria a buscar: ");
                NodoCategoria *categoria = buscarCategoriaPorId(id);
                if (categoria == nullptr) {
                    cout << "Categoria no encontrada.\n";
                } else {
                    cout << "ID: " << categoria->id
                              << " | Nombre: " << categoria->nombre
                              << " | Descripcion: " << categoria->descripcion << "\n";
                }
                break;
            }
            case 5:
                mostrarCategorias();
                break;
            case 0:
                volver = true;
                break;
            default:
                cout << "Opcion no valida.\n";
                break;
        }
    }
}
void menuEventos() {
    bool volver = false;
    while (!volver) {
        cout << "\n--- Gestion de eventos ---\n";
        cout << "1. Insertar evento\n";
        cout << "2. Modificar evento\n";
        cout << "3. Eliminar evento\n";
        cout << "4. Buscar evento\n";
        cout << "5. Mostrar eventos\n";
        cout << "0. Volver\n";
        cout << "Seleccione una opcion: ";
        int opcion = leerEntero();

        switch (opcion) {
            case 1: {
                if (cabezaCategorias == nullptr) {
                    cout << "Debe registrar categorias antes de crear eventos.\n";
                    break;
                }
                string id = leerCadena("ID: ");
                if (buscarEventoPorId(id) != nullptr) {
                    cout << "Ya existe un evento con ese ID.\n";
                    break;
                }
                string nombre = leerCadena("Nombre: ");
                Fecha fecha = leerFecha("Fecha (AAAA-MM-DD): ");
                string tipo = leerCadena("Tipo: ");
                string lugar = leerCadena("Lugar: ");
                mostrarCategorias();
                string idCategoria = leerCadena("ID de categoria: ");
                NodoCategoria *categoria = buscarCategoriaPorId(idCategoria);
                if (categoria == nullptr) {
                    cout << "Categoria no encontrada.\n";
                    break;
                }
                if (insertarEventoOrdenado(id, nombre, fecha, tipo, lugar, categoria) != nullptr) {
                    cout << "Evento creado.\n";
                } else {
                    cout << "No se pudo crear el evento.\n";
                }
                break;
            }
            case 2: {
                string id = leerCadena("Ingrese el ID del evento a modificar: ");
                NodoEvento *evento = buscarEventoPorId(id);
                if (evento == nullptr) {
                    cout << "Evento no encontrado.\n";
                    break;
                }
                string nuevoNombre = leerCadena("Nuevo nombre (" + evento->nombre + "): ");
                string textoFecha = leerCadena("Nueva fecha (" + evento->fecha.aTexto() + "): ");
                Fecha nuevaFecha;
                Fecha *punteroFecha = nullptr;
                if (!textoFecha.empty()) {
                    if (Fecha::intentarParsear(textoFecha, nuevaFecha)) {
                        punteroFecha = &nuevaFecha;
                    } else {
                        cout << "Fecha invalida. Se mantiene la fecha anterior.\n";
                    }
                }
                string nuevoTipo = leerCadena("Nuevo tipo (" + evento->tipo + "): ");
                string nuevoLugar = leerCadena("Nuevo lugar (" + evento->lugar + "): ");
                string idCategoriaActual = evento->categoria != nullptr ? evento->categoria->id : "N/A";
                mostrarCategorias();
                string idCategoria = leerCadena("Nueva categoria (" + idCategoriaActual + "): ");
                NodoCategoria *nuevaCategoria = nullptr;
                if (!idCategoria.empty()) {
                    NodoCategoria *encontrada = buscarCategoriaPorId(idCategoria);
                    if (encontrada != nullptr) {
                        nuevaCategoria = encontrada;
                    } else {
                        cout << "Categoria invalida. Se mantiene la actual.\n";
                    }
                }
                actualizarEvento(evento, nuevoNombre, punteroFecha, nuevoTipo, nuevoLugar, nuevaCategoria);
                cout << "Evento actualizado.\n";
                break;
            }
            case 3: {
                string id = leerCadena("Ingrese el ID del evento a eliminar: ");
                NodoEvento *evento = buscarEventoPorId(id);
                if (evento == nullptr) {
                    cout << "Evento no encontrado.\n";
                    break;
                }
                eliminarEventoPorId(id);
                cout << "Evento eliminado.\n";
                break;
            }
            case 4: {
                string id = leerCadena("Ingrese el ID del evento a buscar: ");
                NodoEvento *evento = buscarEventoPorId(id);
                if (evento == nullptr) {
                    cout << "Evento no encontrado.\n";
                } else {
                    mostrarEventoDetallado(evento);
                }
                break;
            }
            case 5:
                mostrarEventos();
                break;
            case 0:
                volver = true;
                break;
            default:
                cout << "Opcion no valida.\n";
                break;
        }
    }
}
void menuParticipantes() {
    bool volver = false;
    while (!volver) {
        cout << "\n--- Gestion de participantes ---\n";
        cout << "1. Insertar participante\n";
        cout << "2. Modificar participante\n";
        cout << "3. Eliminar participante\n";
        cout << "4. Buscar participante\n";
        cout << "5. Mostrar participantes\n";
        cout << "0. Volver\n";
        cout << "Seleccione una opcion: ";
        int opcion = leerEntero();

        switch (opcion) {
            case 1: {
                string id = leerCadena("ID cedula/carne: ");
                if (buscarParticipantePorId(id) != nullptr) {
                    cout << "Ya existe un participante con ese ID.\n";
                    break;
                }
                string nombres = leerCadena("Nombres: ");
                string apellidos = leerCadena("Apellidos: ");
                string carrera = leerCadena("Carrera: ");
                if (insertarParticipante(id, nombres, apellidos, carrera) != nullptr) {
                    cout << "Participante registrado.\n";
                } else {
                    cout << "No se pudo registrar el participante.\n";
                }
                break;
            }
            case 2: {
                string id = leerCadena("Ingrese el ID del participante a modificar: ");
                NodoParticipante *participante = buscarParticipantePorId(id);
                if (participante == nullptr) {
                    cout << "Participante no encontrado.\n";
                    break;
                }
                string nuevosNombres = leerCadena("Nuevo nombre (" + participante->nombres + "): ");
                string nuevosApellidos = leerCadena("Nuevo apellido (" + participante->apellidos + "): ");
                string nuevaCarrera = leerCadena("Nueva carrera (" + participante->carrera + "): ");
                actualizarParticipante(participante, nuevosNombres, nuevosApellidos, nuevaCarrera);
                cout << "Participante actualizado.\n";
                break;
            }
            case 3: {
                string id = leerCadena("Ingrese el ID del participante a eliminar: ");
                if (eliminarParticipantePorId(id)) {
                    cout << "Participante eliminado.\n";
                } else {
                    cout << "Participante no encontrado.\n";
                }
                break;
            }
            case 4: {
                string id = leerCadena("Ingrese el ID del participante a buscar: ");
                NodoParticipante *participante = buscarParticipantePorId(id);
                if (participante == nullptr) {
                    cout << "Participante no encontrado.\n";
                } else {
                    cout << "- [" << participante->id << "] "
                              << participante->nombres << " " << participante->apellidos
                              << " | Carrera: " << participante->carrera
                              << " | Eventos inscritos: " << contarEventosParticipante(participante) << "\n";
                }
                break;
            }
            case 5:
                mostrarParticipantes();
                break;
            case 0:
                volver = true;
                break;
            default:
                cout << "Opcion no valida.\n";
                break;
        }
    }
}
void menuOrganizadores() {
    bool volver = false;
    while (!volver) {
        cout << "\n--- Gestion de organizadores ---\n";
        cout << "1. Insertar organizador\n";
        cout << "2. Modificar organizador\n";
        cout << "3. Eliminar organizador\n";
        cout << "4. Buscar organizador\n";
        cout << "5. Mostrar organizadores\n";
        cout << "0. Volver\n";
        cout << "Seleccione una opcion: ";
        int opcion = leerEntero();

        switch (opcion) {
            case 1: {
                string id = leerCadena("ID: ");
                if (buscarOrganizadorPorId(id) != nullptr) {
                    cout << "Ya existe un organizador con ese ID.\n";
                    break;
                }
                string nombre = leerCadena("Nombre: ");
                string departamento = leerCadena("Departamento: ");
                if (insertarOrganizador(id, nombre, departamento) != nullptr) {
                    cout << "Organizador registrado.\n";
                } else {
                    cout << "No se pudo registrar el organizador.\n";
                }
                break;
            }
            case 2: {
                string id = leerCadena("Ingrese el ID del organizador a modificar: ");
                NodoOrganizador *organizador = buscarOrganizadorPorId(id);
                if (organizador == nullptr) {
                    cout << "Organizador no encontrado.\n";
                    break;
                }
                string nuevoNombre = leerCadena("Nuevo nombre (" + organizador->nombre + "): ");
                string nuevoDepartamento = leerCadena("Nuevo departamento (" + organizador->departamento + "): ");
                actualizarOrganizador(organizador, nuevoNombre, nuevoDepartamento);
                cout << "Organizador actualizado.\n";
                break;
            }
            case 3: {
                string id = leerCadena("Ingrese el ID del organizador a eliminar: ");
                if (eliminarOrganizadorPorId(id)) {
                    cout << "Organizador eliminado.\n";
                } else {
                    cout << "Organizador no encontrado.\n";
                }
                break;
            }
            case 4: {
                string id = leerCadena("Ingrese el ID del organizador a buscar: ");
                NodoOrganizador *organizador = buscarOrganizadorPorId(id);
                if (organizador == nullptr) {
                    cout << "Organizador no encontrado.\n";
                } else {
                    cout << "- [" << organizador->id << "] " << organizador->nombre
                              << " | Departamento: " << organizador->departamento
                              << " | Eventos a cargo: " << contarEventosOrganizador(organizador) << "\n";
                }
                break;
            }
            case 5:
                mostrarOrganizadores();
                break;
            case 0:
                volver = true;
                break;
            default:
                cout << "Opcion no valida.\n";
                break;
        }
    }
}
void menuRecursos() {
    bool volver = false;
    while (!volver) {
        cout << "\n--- Gestion de recursos ---\n";
        cout << "1. Insertar recurso\n";
        cout << "2. Modificar recurso\n";
        cout << "3. Eliminar recurso\n";
        cout << "4. Buscar recurso\n";
        cout << "5. Mostrar recursos\n";
        cout << "0. Volver\n";
        cout << "Seleccione una opcion: ";
        int opcion = leerEntero();

        switch (opcion) {
            case 1: {
                string id = leerCadena("ID: ");
                if (buscarRecursoPorId(id) != nullptr) {
                    cout << "Ya existe un recurso con ese ID.\n";
                    break;
                }
                string nombre = leerCadena("Nombre: ");
                string descripcion = leerCadena("Descripcion: ");
                if (insertarRecurso(id, nombre, descripcion) != nullptr) {
                    cout << "Recurso registrado.\n";
                } else {
                    cout << "No se pudo registrar el recurso.\n";
                }
                break;
            }
            case 2: {
                string id = leerCadena("Ingrese el ID del recurso a modificar: ");
                NodoRecurso *recurso = buscarRecursoPorId(id);
                if (recurso == nullptr) {
                    cout << "Recurso no encontrado.\n";
                    break;
                }
                string nuevoNombre = leerCadena("Nuevo nombre (" + recurso->nombre + "): ");
                string nuevaDescripcion = leerCadena("Nueva descripcion (" + recurso->descripcion + "): ");
                actualizarRecurso(recurso, nuevoNombre, nuevaDescripcion);
                cout << "Recurso actualizado.\n";
                break;
            }
            case 3: {
                string id = leerCadena("Ingrese el ID del recurso a eliminar: ");
                if (eliminarRecursoPorId(id)) {
                    cout << "Recurso eliminado.\n";
                } else {
                    cout << "Recurso no encontrado.\n";
                }
                break;
            }
            case 4: {
                string id = leerCadena("Ingrese el ID del recurso a buscar: ");
                NodoRecurso *recurso = buscarRecursoPorId(id);
                if (recurso == nullptr) {
                    cout << "Recurso no encontrado.\n";
                } else {
                    cout << "- [" << recurso->id << "] " << recurso->nombre
                              << " | " << recurso->descripcion
                              << " | Eventos asignados: " << contarEventosRecurso(recurso) << "\n";
                }
                break;
            }
            case 5:
                mostrarRecursos();
                break;
            case 0:
                volver = true;
                break;
            default:
                cout << "Opcion no valida.\n";
                break;
        }
    }
}
void registrarInscripcion() {
    if (cabezaEventos == nullptr || cabezaParticipantes == nullptr) {
        cout << "Debe contar con eventos y participantes registrados.\n";
        return;
    }
    mostrarEventos();
    string idEvento = leerCadena("ID del evento: ");
    NodoEvento *evento = buscarEventoPorId(idEvento);
    if (evento == nullptr) {
        cout << "Evento no encontrado.\n";
        return;
    }
    mostrarParticipantes();
    string idParticipante = leerCadena("ID del participante: ");
    NodoParticipante *participante = buscarParticipantePorId(idParticipante);
    if (participante == nullptr) {
        cout << "Participante no encontrado.\n";
        return;
    }
    if (participanteInscritoEnEvento(participante, evento)) {
        cout << "El participante ya esta inscrito en este evento.\n";
        return;
    }
    string idInscripcion = leerCadena("ID de inscripcion: ");
    Fecha fechaInscripcion = leerFecha("Fecha de inscripcion (AAAA-MM-DD): ");
    vincularParticipanteConEvento(participante, evento);
    registrarHistorial(idInscripcion, fechaInscripcion, participante, evento);
    cout << "Inscripcion registrada.\n";
}

void asignarOrganizadorEvento() {
    if (cabezaEventos == nullptr || cabezaOrganizadores == nullptr) {
        cout << "Debe contar con eventos y organizadores registrados.\n";
        return;
    }
    mostrarEventos();
    string idEvento = leerCadena("ID del evento: ");
    NodoEvento *evento = buscarEventoPorId(idEvento);
    if (evento == nullptr) {
        cout << "Evento no encontrado.\n";
        return;
    }
    mostrarOrganizadores();
    string idOrganizador = leerCadena("ID del organizador: ");
    NodoOrganizador *organizador = buscarOrganizadorPorId(idOrganizador);
    if (organizador == nullptr) {
        cout << "Organizador no encontrado.\n";
        return;
    }
    if (organizadorAsignadoEnEvento(organizador, evento)) {
        cout << "El organizador ya esta asignado a este evento.\n";
        return;
    }
    vincularOrganizadorConEvento(organizador, evento);
    cout << "Organizador asignado.\n";
}

void asignarRecursoEvento() {
    if (cabezaEventos == nullptr || cabezaRecursos == nullptr) {
        cout << "Debe contar con eventos y recursos registrados.\n";
        return;
    }
    mostrarEventos();
    string idEvento = leerCadena("ID del evento: ");
    NodoEvento *evento = buscarEventoPorId(idEvento);
    if (evento == nullptr) {
        cout << "Evento no encontrado.\n";
        return;
    }
    mostrarRecursos();
    string idRecurso = leerCadena("ID del recurso: ");
    NodoRecurso *recurso = buscarRecursoPorId(idRecurso);
    if (recurso == nullptr) {
        cout << "Recurso no encontrado.\n";
        return;
    }
    if (recursoAsignadoEnEvento(recurso, evento)) {
        cout << "El recurso ya esta asignado a este evento.\n";
        return;
    }
    vincularRecursoConEvento(recurso, evento);
    cout << "Recurso asignado.\n";
}

void modificarInscripcion() {
    if (cabezaHistorial == nullptr) {
        cout << "No hay inscripciones registradas.\n";
        return;
    }
    string id = leerCadena("ID de la inscripcion: ");
    NodoHistorial *registro = buscarHistorialPorId(id);
    if (registro == nullptr) {
        cout << "Inscripcion no encontrada.\n";
        return;
    }
    NodoParticipante *participante = registro->participante;
    NodoEvento *eventoActual = registro->evento;
    Fecha fechaActual = registro->fecha;

    cout << "Inscripcion actual:\n";
    cout << "- Participante: " << (participante != nullptr ? participante->nombres + " " + participante->apellidos : "Sin participante")
         << " | Evento: " << (eventoActual != nullptr ? eventoActual->nombre : "Sin evento")
         << " | Fecha: " << fechaActual.aTexto() << "\n";
    cout << "1. Cambiar fecha\n";
    cout << "2. Cambiar evento\n";
    cout << "3. Cambiar fecha y evento\n";
    cout << "0. Cancelar\n";
    cout << "Seleccione una opcion: ";
    int opcionCambio = leerEntero();
    if (opcionCambio == 0) {
        cout << "No se realizaron cambios.\n";
        return;
    }

    bool cambiarFecha = opcionCambio == 1 || opcionCambio == 3;
    bool cambiarEvento = opcionCambio == 2 || opcionCambio == 3;
    if (!cambiarFecha && !cambiarEvento) {
        cout << "Opcion no valida.\n";
        return;
    }

    Fecha fechaFinal = fechaActual;
    if (cambiarFecha) {
        fechaFinal = leerFecha("Nueva fecha de inscripcion (AAAA-MM-DD): ");
    }

    NodoEvento *eventoFinal = eventoActual;
    if (cambiarEvento) {
        mostrarEventos();
        string idEventoNuevo = leerCadena("Nuevo ID de evento: ");
        NodoEvento *eventoNuevo = buscarEventoPorId(idEventoNuevo);
        if (eventoNuevo == nullptr) {
            cout << "Evento no encontrado.\n";
            return;
        }
        if (eventoNuevo == eventoActual) {
            cout << "Debe elegir un evento diferente.\n";
            return;
        }
        if (participante != nullptr && participanteInscritoEnEvento(participante, eventoNuevo)) {
            cout << "El participante ya esta inscrito en el evento destino.\n";
            return;
        }
        eventoFinal = eventoNuevo;
    }

    string idRegistro = registro->id;
    if (cambiarEvento && participante != nullptr && eventoActual != nullptr) {
        desvincularParticipanteDeEvento(participante, eventoActual);
        vincularParticipanteConEvento(participante, eventoFinal);
    }

    eliminarNodoHistorial(registro);
    registrarHistorial(idRegistro, fechaFinal, participante, eventoFinal);
    cout << "Inscripcion actualizada.\n";
}

void cancelarInscripcion() {
    if (cabezaHistorial == nullptr) {
        cout << "No hay inscripciones registradas.\n";
        return;
    }
    string id = leerCadena("ID de la inscripcion a cancelar: ");
    NodoHistorial *registro = buscarHistorialPorId(id);
    if (registro == nullptr) {
        cout << "Inscripcion no encontrada.\n";
        return;
    }
    if (registro->participante != nullptr && registro->evento != nullptr) {
        desvincularParticipanteDeEvento(registro->participante, registro->evento);
    }
    eliminarNodoHistorial(registro);
    cout << "Inscripcion cancelada.\n";
}

void mostrarParticipantesDeEvento() {
    if (cabezaEventos == nullptr) {
        cout << "No hay eventos registrados.\n";
        return;
    }
    string idEvento = leerCadena("ID del evento: ");
    NodoEvento *evento = buscarEventoPorId(idEvento);
    if (evento == nullptr) {
        cout << "Evento no encontrado.\n";
        return;
    }
    cout << "Participantes inscritos en " << evento->nombre << ":\n";
    EnlaceEventoParticipante *enlace = evento->participantes;
    if (enlace == nullptr) {
        cout << "No hay participantes inscritos en este evento.\n";
        return;
    }
    while (enlace != nullptr) {
        if (enlace->participante != nullptr) {
            cout << "- " << enlace->participante->nombres << " " << enlace->participante->apellidos
                 << " (" << enlace->participante->id << ")\n";
        }
        enlace = enlace->siguiente;
    }
}

void buscarInscripcion() {
    if (cabezaHistorial == nullptr) {
        cout << "No hay inscripciones registradas.\n";
        return;
    }
    string id = leerCadena("ID de la inscripcion a buscar: ");
    NodoHistorial *registro = buscarHistorialPorId(id);
    if (registro == nullptr) {
        cout << "Inscripcion no encontrada.\n";
        return;
    }
    cout << "- ID: " << registro->id
         << " | Fecha: " << registro->fecha.aTexto()
         << " | Participante: " << (registro->participante != nullptr ? registro->participante->nombres + " " + registro->participante->apellidos : "Sin participante")
         << " | Evento: " << (registro->evento != nullptr ? registro->evento->nombre : "Sin evento") << "\n";
}

void menuInscripciones() {
    bool volver = false;
    while (!volver) {
        cout << "\n--- Gestion de inscripciones ---\n";
        cout << "1. Registrar inscripcion\n";
        cout << "2. Modificar inscripcion\n";
        cout << "3. Cancelar inscripcion\n";
        cout << "4. Mostrar participantes de un evento\n";
        cout << "5. Buscar inscripcion por ID\n";
        cout << "0. Volver\n";
        cout << "Seleccione una opcion: ";
        int opcion = leerEntero();

        switch (opcion) {
            case 1:
                registrarInscripcion();
                break;
            case 2:
                modificarInscripcion();
                break;
            case 3:
                cancelarInscripcion();
                break;
            case 4:
                mostrarParticipantesDeEvento();
                break;
            case 5:
                buscarInscripcion();
                break;
            case 0:
                volver = true;
                break;
            default:
                cout << "Opcion no valida.\n";
                break;
        }
    }
}

void reasignarOrganizadorEvento() {
    if (cabezaEventos == nullptr || cabezaOrganizadores == nullptr) {
        cout << "Debe contar con eventos y organizadores registrados.\n";
        return;
    }
    string idOrganizador = leerCadena("ID del organizador: ");
    NodoOrganizador *organizador = buscarOrganizadorPorId(idOrganizador);
    if (organizador == nullptr) {
        cout << "Organizador no encontrado.\n";
        return;
    }
    if (organizador->eventos == nullptr) {
        cout << "El organizador no tiene eventos asignados.\n";
        return;
    }
    string idEventoActual = leerCadena("ID del evento actual: ");
    NodoEvento *eventoActual = buscarEventoPorId(idEventoActual);
    if (eventoActual == nullptr) {
        cout << "Evento actual no encontrado.\n";
        return;
    }
    if (!organizadorAsignadoEnEvento(organizador, eventoActual)) {
        cout << "El organizador no esta asignado a ese evento.\n";
        return;
    }
    mostrarEventos();
    string idEventoNuevo = leerCadena("ID del nuevo evento: ");
    NodoEvento *eventoNuevo = buscarEventoPorId(idEventoNuevo);
    if (eventoNuevo == nullptr) {
        cout << "Evento nuevo no encontrado.\n";
        return;
    }
    if (eventoNuevo == eventoActual) {
        cout << "Debe elegir un evento diferente.\n";
        return;
    }
    if (organizadorAsignadoEnEvento(organizador, eventoNuevo)) {
        cout << "El organizador ya esta asignado al evento destino.\n";
        return;
    }
    desvincularOrganizadorDeEvento(organizador, eventoActual);
    vincularOrganizadorConEvento(organizador, eventoNuevo);
    cout << "Organizador reasignado.\n";
}

void retirarOrganizadorEvento() {
    if (cabezaEventos == nullptr || cabezaOrganizadores == nullptr) {
        cout << "Debe contar con eventos y organizadores registrados.\n";
        return;
    }
    string idEvento = leerCadena("ID del evento: ");
    NodoEvento *evento = buscarEventoPorId(idEvento);
    if (evento == nullptr) {
        cout << "Evento no encontrado.\n";
        return;
    }
    string idOrganizador = leerCadena("ID del organizador: ");
    NodoOrganizador *organizador = buscarOrganizadorPorId(idOrganizador);
    if (organizador == nullptr) {
        cout << "Organizador no encontrado.\n";
        return;
    }
    if (!organizadorAsignadoEnEvento(organizador, evento)) {
        cout << "El organizador no esta asignado a este evento.\n";
        return;
    }
    desvincularOrganizadorDeEvento(organizador, evento);
    cout << "Organizador retirado del evento.\n";
}

void mostrarOrganizadoresEvento() {
    if (cabezaEventos == nullptr) {
        cout << "No hay eventos registrados.\n";
        return;
    }
    string idEvento = leerCadena("ID del evento: ");
    NodoEvento *evento = buscarEventoPorId(idEvento);
    if (evento == nullptr) {
        cout << "Evento no encontrado.\n";
        return;
    }
    cout << "Organizadores del evento " << evento->nombre << ":\n";
    EnlaceEventoOrganizador *enlace = evento->organizadores;
    if (enlace == nullptr) {
        cout << "No hay organizadores asignados a este evento.\n";
        return;
    }
    while (enlace != nullptr) {
        if (enlace->organizador != nullptr) {
            cout << "- " << enlace->organizador->nombre << " (" << enlace->organizador->id << ")\n";
        }
        enlace = enlace->siguiente;
    }
}

void buscarOrganizadorEvento() {
    if (cabezaEventos == nullptr || cabezaOrganizadores == nullptr) {
        cout << "Debe contar con eventos y organizadores registrados.\n";
        return;
    }
    string idOrganizador = leerCadena("ID del organizador: ");
    NodoOrganizador *organizador = buscarOrganizadorPorId(idOrganizador);
    if (organizador == nullptr) {
        cout << "Organizador no encontrado.\n";
        return;
    }
    string idEvento = leerCadena("ID del evento: ");
    NodoEvento *evento = buscarEventoPorId(idEvento);
    if (evento == nullptr) {
        cout << "Evento no encontrado.\n";
        return;
    }
    if (organizadorAsignadoEnEvento(organizador, evento)) {
        cout << "El organizador " << organizador->nombre << " esta asignado al evento " << evento->nombre << ".\n";
    } else {
        cout << "El organizador " << organizador->nombre << " no esta asignado al evento indicado.\n";
    }
}

void menuOrganizadoresEvento() {
    bool volver = false;
    while (!volver) {
        cout << "\n--- Gestion de organizadores por evento ---\n";
        cout << "1. Asignar organizador a evento\n";
        cout << "2. Reasignar organizador a otro evento\n";
        cout << "3. Retirar organizador de evento\n";
        cout << "4. Mostrar organizadores de un evento\n";
        cout << "5. Buscar organizador en un evento\n";
        cout << "0. Volver\n";
        cout << "Seleccione una opcion: ";
        int opcion = leerEntero();

        switch (opcion) {
            case 1:
                asignarOrganizadorEvento();
                break;
            case 2:
                reasignarOrganizadorEvento();
                break;
            case 3:
                retirarOrganizadorEvento();
                break;
            case 4:
                mostrarOrganizadoresEvento();
                break;
            case 5:
                buscarOrganizadorEvento();
                break;
            case 0:
                volver = true;
                break;
            default:
                cout << "Opcion no valida.\n";
                break;
        }
    }
}

void reasignarRecursoEvento() {
    if (cabezaEventos == nullptr || cabezaRecursos == nullptr) {
        cout << "Debe contar con eventos y recursos registrados.\n";
        return;
    }
    string idRecurso = leerCadena("ID del recurso: ");
    NodoRecurso *recurso = buscarRecursoPorId(idRecurso);
    if (recurso == nullptr) {
        cout << "Recurso no encontrado.\n";
        return;
    }
    if (recurso->eventos == nullptr) {
        cout << "El recurso no esta asignado a ningun evento.\n";
        return;
    }
    string idEventoActual = leerCadena("ID del evento actual: ");
    NodoEvento *eventoActual = buscarEventoPorId(idEventoActual);
    if (eventoActual == nullptr) {
        cout << "Evento actual no encontrado.\n";
        return;
    }
    if (!recursoAsignadoEnEvento(recurso, eventoActual)) {
        cout << "El recurso no esta asignado a ese evento.\n";
        return;
    }
    mostrarEventos();
    string idEventoNuevo = leerCadena("ID del nuevo evento: ");
    NodoEvento *eventoNuevo = buscarEventoPorId(idEventoNuevo);
    if (eventoNuevo == nullptr) {
        cout << "Evento nuevo no encontrado.\n";
        return;
    }
    if (eventoNuevo == eventoActual) {
        cout << "Debe elegir un evento diferente.\n";
        return;
    }
    if (recursoAsignadoEnEvento(recurso, eventoNuevo)) {
        cout << "El recurso ya esta asignado al evento destino.\n";
        return;
    }
    desvincularRecursoDeEvento(recurso, eventoActual);
    vincularRecursoConEvento(recurso, eventoNuevo);
    cout << "Recurso reasignado.\n";
}

void retirarRecursoEvento() {
    if (cabezaEventos == nullptr || cabezaRecursos == nullptr) {
        cout << "Debe contar con eventos y recursos registrados.\n";
        return;
    }
    string idEvento = leerCadena("ID del evento: ");
    NodoEvento *evento = buscarEventoPorId(idEvento);
    if (evento == nullptr) {
        cout << "Evento no encontrado.\n";
        return;
    }
    string idRecurso = leerCadena("ID del recurso: ");
    NodoRecurso *recurso = buscarRecursoPorId(idRecurso);
    if (recurso == nullptr) {
        cout << "Recurso no encontrado.\n";
        return;
    }
    if (!recursoAsignadoEnEvento(recurso, evento)) {
        cout << "El recurso no esta asignado a este evento.\n";
        return;
    }
    desvincularRecursoDeEvento(recurso, evento);
    cout << "Recurso retirado del evento.\n";
}

void mostrarRecursosEvento() {
    if (cabezaEventos == nullptr) {
        cout << "No hay eventos registrados.\n";
        return;
    }
    string idEvento = leerCadena("ID del evento: ");
    NodoEvento *evento = buscarEventoPorId(idEvento);
    if (evento == nullptr) {
        cout << "Evento no encontrado.\n";
        return;
    }
    cout << "Recursos asignados al evento " << evento->nombre << ":\n";
    EnlaceEventoRecurso *enlace = evento->recursos;
    if (enlace == nullptr) {
        cout << "No se han asignado recursos a este evento.\n";
        return;
    }
    while (enlace != nullptr) {
        if (enlace->recurso != nullptr) {
            cout << "- " << enlace->recurso->nombre << " (" << enlace->recurso->id << ") - " << enlace->recurso->descripcion << "\n";
        }
        enlace = enlace->siguiente;
    }
}

void buscarRecursoEvento() {
    if (cabezaEventos == nullptr || cabezaRecursos == nullptr) {
        cout << "Debe contar con eventos y recursos registrados.\n";
        return;
    }
    string idRecurso = leerCadena("ID del recurso: ");
    NodoRecurso *recurso = buscarRecursoPorId(idRecurso);
    if (recurso == nullptr) {
        cout << "Recurso no encontrado.\n";
        return;
    }
    string idEvento = leerCadena("ID del evento: ");
    NodoEvento *evento = buscarEventoPorId(idEvento);
    if (evento == nullptr) {
        cout << "Evento no encontrado.\n";
        return;
    }
    if (recursoAsignadoEnEvento(recurso, evento)) {
        cout << "El recurso " << recurso->nombre << " esta asignado al evento " << evento->nombre << ".\n";
    } else {
        cout << "El recurso " << recurso->nombre << " no esta asignado al evento indicado.\n";
    }
}

void menuRecursosEvento() {
    bool volver = false;
    while (!volver) {
        cout << "\n--- Gestion de recursos por evento ---\n";
        cout << "1. Asignar recurso a evento\n";
        cout << "2. Reasignar recurso a otro evento\n";
        cout << "3. Retirar recurso de evento\n";
        cout << "4. Mostrar recursos de un evento\n";
        cout << "5. Buscar recurso en un evento\n";
        cout << "0. Volver\n";
        cout << "Seleccione una opcion: ";
        int opcion = leerEntero();

        switch (opcion) {
            case 1:
                asignarRecursoEvento();
                break;
            case 2:
                reasignarRecursoEvento();
                break;
            case 3:
                retirarRecursoEvento();
                break;
            case 4:
                mostrarRecursosEvento();
                break;
            case 5:
                buscarRecursoEvento();
                break;
            case 0:
                volver = true;
                break;
            default:
                cout << "Opcion no valida.\n";
                break;
        }
    }
}

void menuConsultas() {
    bool volver = false;
    while (!volver) {
        cout << "\n--- Consultas ---\n";
        cout << "1. Participante con mas eventos\n";
        cout << "2. Organizador con mas eventos a cargo\n";
        cout << "3. Tipo de evento mas frecuente\n";
        cout << "4. Categoria con mayor participacion\n";
        cout << "5. Recurso mas utilizado\n";
        cout << "6. Lugar con mas eventos\n";
        cout << "7. Evento con mas participantes inscritos\n";
        cout << "8. Organizador con eventos en mas categorias\n";
        cout << "9. Porcentaje de participacion estudiantil\n";
        cout << "0. Volver\n";
        cout << "Seleccione una opcion: ";
        int opcion = leerEntero();

        switch (opcion) {
            case 1:
                consultaParticipanteConMasEventos();
                break;
            case 2:
                consultaOrganizadorConMasEventos();
                break;
            case 3:
                consultaTipoEventoMasFrecuente();
                break;
            case 4:
                consultaCategoriaConMayorParticipacion();
                break;
            case 5:
                consultaRecursoMasUtilizado();
                break;
            case 6:
                consultaLugarMasFrecuente();
                break;
            case 7:
                consultaEventoConMasParticipantes();
                break;
            case 8:
                consultaOrganizadorConMasCategorias();
                break;
            case 9:
                consultaPorcentajeParticipacion();
                break;
            case 0:
                volver = true;
                break;
            default:
                cout << "Opcion no valida.\n";
                break;
        }
    }
}
void menuReportes() {
    bool volver = false;
    while (!volver) {
        cout << "\n--- Reportes ---\n";
        cout << "1. Participantes ordenados por apellido (asc/desc)\n";
        cout << "2. Eventos organizados por una persona\n";
        cout << "3. Eventos de una categoria\n";
        cout << "4. Recursos asignados a un evento\n";
        cout << "5. Eventos realizados en un lugar\n";
        cout << "6. Talleres organizados por un departamento\n";
        cout << "7. Historial de inscripciones ordenado\n";
        cout << "8. Organizadores sin eventos\n";
        cout << "0. Volver\n";
        cout << "Seleccione una opcion: ";
        int opcion = leerEntero();

        switch (opcion) {
            case 1:
                reporteParticipantesPorApellido();
                break;
            case 2: {
                string idOrganizador = leerCadena("ID del organizador: ");
                NodoOrganizador *organizador = buscarOrganizadorPorId(idOrganizador);
                reporteEventosPorOrganizador(organizador);
                break;
            }
            case 3: {
                string idCategoria = leerCadena("ID de la categoria: ");
                NodoCategoria *categoria = buscarCategoriaPorId(idCategoria);
                reporteEventosPorCategoria(categoria);
                break;
            }
            case 4: {
                string idEvento = leerCadena("ID del evento: ");
                NodoEvento *evento = buscarEventoPorId(idEvento);
                reporteRecursosPorEvento(evento);
                break;
            }
            case 5: {
                string lugar = leerCadena("Lugar: ");
                reporteEventosPorLugar(lugar);
                break;
            }
            case 6: {
                string departamento = leerCadena("Departamento: ");
                reporteTalleresPorDepartamento(departamento);
                break;
            }
            case 7:
                reporteHistorialInscripciones();
                break;
            case 8:
                reporteOrganizadoresSinEventos();
                break;
            case 0:
                volver = true;
                break;
            default:
                cout << "Opcion no valida.\n";
                break;
        }
    }
}
int main() {
    cargarDatosIniciales();
    bool salir = false;
    while (!salir) {
        cout << "\n====== Sistema de Gestion de Eventos Universitarios ======\n";
        cout << "1. Gestionar categorias\n";
        cout << "2. Gestionar eventos\n";
        cout << "3. Gestionar participantes\n";
        cout << "4. Gestionar organizadores\n";
        cout << "5. Gestionar recursos\n";
        cout << "6. Gestionar inscripciones\n";
        cout << "7. Gestionar organizadores por evento\n";
        cout << "8. Gestionar recursos por evento\n";
        cout << "9. Consultas\n";
        cout << "10. Reportes\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        int opcion = leerEntero();

        switch (opcion) {
            case 1:
                menuCategorias();
                break;
            case 2:
                menuEventos();
                break;
            case 3:
                menuParticipantes();
                break;
            case 4:
                menuOrganizadores();
                break;
            case 5:
                menuRecursos();
                break;
            case 6:
                menuInscripciones();
                break;
            case 7:
                menuOrganizadoresEvento();
                break;
            case 8:
                menuRecursosEvento();
                break;
            case 9:
                menuConsultas();
                break;
            case 10:
                menuReportes();
                break;
            case 0:
                salir = true;
                break;
            default:
                cout << "Opcion no valida.\n";
                break;
        }
    }
    liberarMemoria();
    cout << "Saliendo del sistema...\n";
    return 0;
}
