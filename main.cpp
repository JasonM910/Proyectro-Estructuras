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
void registrarInscripcion();
void asignarOrganizadorEvento();
void asignarRecursoEvento();
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
        cout << "6. Registrar inscripcion de participante en evento\n";
        cout << "7. Asignar organizador a evento\n";
        cout << "8. Asignar recurso a evento\n";
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
                registrarInscripcion();
                break;
            case 7:
                asignarOrganizadorEvento();
                break;
            case 8:
                asignarRecursoEvento();
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
