#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Alumno {
    char nombreCompleto[100];
    int creditosAprobados;
    int semestreEquivalente;
};

struct Nodo {
    struct Alumno alumno;
    struct Nodo* siguiente;
};

// Función para crear un alumno
struct Alumno crearAlumno(const char* nombre, int creditos, int semestre) {
    struct Alumno alumno;
    strcpy(alumno.nombreCompleto, nombre);
    alumno.creditosAprobados = creditos;
    alumno.semestreEquivalente = semestre;
    return alumno;
}

// Función para imprimir los datos de un alumno
void imprimirAlumno(struct Alumno alumno) {
    printf("Nombre: %s\n", alumno.nombreCompleto);
    printf("Creditos Aprobados: %d\n", alumno.creditosAprobados);
    printf("Semestre Equivalente: %d\n", alumno.semestreEquivalente);
    printf("----------------------\n");
}

// Función para crear un nuevo nodo
struct Nodo* crearNodo(struct Alumno alumno) {
    struct Nodo* nodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    nodo->alumno = alumno;
    nodo->siguiente = NULL;
    return nodo;
}

// Función para insertar un nodo en orden descendente por créditos
int insertarNodoOrdenadoCreditos(struct Nodo** inicio, struct Nodo* nuevoNodo) {
    if (!(*inicio) || nuevoNodo->alumno.creditosAprobados >= (*inicio)->alumno.creditosAprobados) {
        nuevoNodo->siguiente = *inicio;
        *inicio = nuevoNodo;
        return 0;
    }
    
    struct Nodo* actual = *inicio;
    while (actual->siguiente && actual->siguiente->alumno.creditosAprobados > nuevoNodo->alumno.creditosAprobados) {
        actual = actual->siguiente;
    }
    
    nuevoNodo->siguiente = actual->siguiente;
    actual->siguiente = nuevoNodo;
    
    return 0;
}

// Función para imprimir la lista de alumnos
void imprimirLista(struct Nodo* inicio) {
    struct Nodo* actual = inicio;
    while (actual) {
        imprimirAlumno(actual->alumno);
        actual = actual->siguiente;
    }
}

int main() {
    struct Nodo* lista = NULL;

    // Crear alumnos y nodos
    struct Alumno alumno1 = crearAlumno("Carlos", 120, 5);
    struct Alumno alumno2 = crearAlumno("Xavier", 90, 4);
    struct Alumno alumno3 = crearAlumno("Mario", 150, 6);
    struct Alumno alumno4 = crearAlumno("Victor", 110, 5);
    struct Alumno alumno5 = crearAlumno("Emiliano", 80, 3);

    struct Nodo* nodo1 = crearNodo(alumno1);
    struct Nodo* nodo2 = crearNodo(alumno2);
    struct Nodo* nodo3 = crearNodo(alumno3);
    struct Nodo* nodo4 = crearNodo(alumno4);
    struct Nodo* nodo5 = crearNodo(alumno5);

    // Insertar nodos en orden descendente por créditos
    insertarNodoOrdenadoCreditos(&lista, nodo1);
    insertarNodoOrdenadoCreditos(&lista, nodo2);
    insertarNodoOrdenadoCreditos(&lista, nodo3);
    insertarNodoOrdenadoCreditos(&lista, nodo4);
    insertarNodoOrdenadoCreditos(&lista, nodo5);

    // Imprimir la lista
    imprimirLista(lista);

    // Liberar memoria
    struct Nodo* actual = lista;
    while (actual) {
        struct Nodo* siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }

    return 0;
}