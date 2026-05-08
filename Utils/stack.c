#include <stdlib.h>
#include "stack.h"

struct NodoStr{
    TipoDato dato;
    struct NodoStr * siguiente;
};
typedef struct NodoStr Nodo;

struct StackStr {
    Nodo * nodo;
    int size;
};

Stack stack_crear(){
    Stack s = malloc(sizeof(struct StackStr));
    s->size = 0;
    s->nodo = NULL;
    return s;
}

void stack_liberar(Stack s){
    Nodo * antiguo;
    while(s->nodo != NULL){
        antiguo = s->nodo;
        s->nodo = antiguo->siguiente;
        free(antiguo);
    }
    free(s);
}

void stack_push(Stack s, TipoDato valor){
    Nodo * antiguo = s->nodo;

    Nodo * nuevo = malloc(sizeof(Nodo));
    nuevo->dato = valor;
    nuevo->siguiente = antiguo;

    s->nodo = nuevo;
    s->size += 1;
}

TipoDato stack_top(Stack s){
    return s->nodo->dato;
}

bool stack_pop(Stack s){
    if(!stack_empty(s)){
        Nodo * antiguo = s->nodo;
        s->nodo = antiguo->siguiente;
        free(antiguo);
        s->size -= 1;
        return true;
    }
    return false;
}

int stack_size(Stack s){
    return s->size;
}

bool stack_empty(Stack s){
    return s->size == 0;
}