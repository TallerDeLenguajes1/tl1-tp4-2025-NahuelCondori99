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
Nodo *buscarNodo(Nodo *Lista, int id);
void eliminarNodo(Nodo **lista, int id);
void tareaPorIDoClave(Nodo **lista, int id, int clave);

int main()
{
    Nodo *tareaPendiente;
    tareaPendiente = crearListaVacia();

    Nodo *tareaRealizada;
    tareaRealizada = crearListaVacia();

    char opcion;
    fflush(stdin);

    int contador = 0;

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
    
    printf("***Tareas pendientes***\n");

    mostrarTareas(tareaPendiente);

    char valido;

    do
    {
        int idTarea;
        printf("Ingresar ID de la tarea que ya realizo:");
        scanf("%d",&idTarea);

        Nodo *nodoBuscado = buscarNodo(tareaPendiente, idTarea);

        if (nodoBuscado != NULL)
        {   

            Nodo *nodoCopia = crearNuevoNodo(nodoBuscado->T.TareaID - 1000, nodoBuscado->T.Duracion, nodoBuscado->T.Descripcion);
            
            eliminarNodo(&tareaPendiente, idTarea); 
            agregarTarea(&tareaRealizada, nodoCopia);
            printf("Realizo alguna otra tarea?(s/n)");
            scanf(" %c",&valido);
            getchar();
        }
        

    } while (tolower(valido) != 'n');   

    printf("***Tareas realizadas***\n");
    mostrarTareas(tareaRealizada);

    printf("***Tareas pendientes***\n");
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
        printf("Tarea ID: %d --> Descripcion: %s --> Duracion de la tarea: %d minutos\n", tarea->T.TareaID, tarea->T.Descripcion, tarea->T.Duracion);

        tarea = tarea->Siguiente;
    }
}

Nodo *buscarNodo(Nodo *Lista, int id)
{

    while (Lista != NULL)
    {
        if (Lista->T.TareaID == id)
        {
            return(Lista);
        }
        
        Lista = Lista->Siguiente;

    }
    return(0);
}

void eliminarNodo(Nodo **lista, int id) {
    Nodo *actual = *lista;
    Nodo *anterior = NULL;

    while (actual != NULL && actual->T.TareaID != id) {
        anterior = actual;
        actual = actual->Siguiente;
    }

    if (actual == NULL) return;

    if (anterior == NULL) {
        *lista = actual->Siguiente;
    } else {
        anterior->Siguiente = actual->Siguiente;
    }

    free(actual->T.Descripcion);
    free(actual);
}
