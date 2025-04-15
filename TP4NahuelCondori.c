#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define tama 50

struct Tarea
{
    int TareaID;       // Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion;      // entre 10 – 100

} typedef Tarea;

struct Nodo
{
    Tarea T;
    struct Nodo *Siguiente;

} typedef Nodo;

Nodo *crearListaVacia();
Nodo *crearNuevoNodo(int id, int duracion, char *descripcion);
void agregarTarea(Nodo **lista, Nodo *nuevoNodo);
void mostrarTareas(Nodo *tarea);

int main()
{
    Nodo *tareaPendiente;
    tareaPendiente = crearListaVacia();

    Nodo *tareaRealizada;
    tareaRealizada = crearListaVacia();

    char opcion;
    printf("¿Desea ingresar una tarea?(s/n).");
    scanf("%c", &opcion);
    fflush(stdin);

    int contador = 1;

    do
    {

        char descripcion[tama];
        printf("Ingresar la descripcion de la tarea:");
        fgets(descripcion, tama, stdin);
        if (descripcion[strlen(descripcion) - 1] == '\n')
        {
            descripcion[strlen(descripcion) - 1] = '\0';
        }

        int duracion;
        printf("Ingresar la duracion de la tarea:");
        scanf("%d", &duracion);
        getchar();
        Nodo *aux = crearNuevoNodo(contador, duracion, descripcion);
        agregarTarea(&tareaPendiente, aux);

        contador += 1;

        printf("Desea ingresar otra tarea? (s/n)");
        scanf(" %c", &opcion);
        getchar();
    } while (tolower(opcion) != 'n');

    printf("Tareas pendientes\n");
    mostrarTareas(tareaPendiente);

    return 0;
}

Nodo *crearListaVacia()
{
    return NULL;
}

Nodo *crearNuevoNodo(int id, int duracion, char *descripcion)
{
    Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));

    nuevoNodo->T.Descripcion = (char *)malloc(strlen(descripcion) + 1);
    strcpy(nuevoNodo->T.Descripcion, descripcion);

    nuevoNodo->T.TareaID = 1000 + id;

    nuevoNodo->T.Duracion = duracion;

    nuevoNodo->Siguiente = NULL;

    return nuevoNodo;
}

void agregarTarea(Nodo **lista, Nodo *nuevoNodo)
{
    if (*lista == NULL)
    {
        *lista = nuevoNodo;
    }
    else
    {
        Nodo *aux = *lista;
        while (aux->Siguiente != NULL)
        {
            aux = aux->Siguiente;
        }
        aux->Siguiente = nuevoNodo;
    }
}

void mostrarTareas(Nodo *tarea)
{
    while (tarea)
    {
        printf("Tarea ID: %d\n", tarea->T.TareaID);
        printf("Descripcion: %s\n", tarea->T.Descripcion);
        printf("Duracion de la tarea: %d\n", tarea->T.Duracion);
        tarea = tarea->Siguiente;
    }
}