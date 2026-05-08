#include "stack_tabla_simbolos.h"

struct PosicionStackRep {
    TablaHash ts;
    struct PosicionStackRep *sig;
};

struct StackRep {
    PosicionStackTs cabecera;
    PosicionStackTs ultimo;
    int num_ts;
};

typedef struct PosicionStackRep *NodoStackPtr;

StackTs creaStackTS(){
    StackTs nueva = malloc(sizeof(struct StackRep));
    nueva->cabecera = malloc(sizeof(struct PosicionStackRep));
    nueva->cabecera->sig = NULL;
    nueva->ultimo = nueva->cabecera;
    nueva->num_ts = 0;
    return nueva;
}

void liberaStackTS(StackTs stack_ts){
    PosicionStackTs actual = stack_ts->cabecera;

    while (actual != NULL) {
        PosicionStackTs sig = actual->sig;

        if (actual != stack_ts->cabecera && actual->ts != NULL) liberaTS(actual->ts);

        free(actual);
        actual = sig;
    }

    free(stack_ts);
}

void pushStackTS(StackTs stack_ts, TablaHash ts){
    NodoStackPtr nuevo = malloc(sizeof(struct PosicionStackRep));
    nuevo->ts = ts;
    nuevo->sig = stack_ts->cabecera->sig;
    stack_ts->cabecera->sig = nuevo;
    stack_ts->num_ts++;

    if(stack_ts->cabecera == stack_ts->ultimo) stack_ts->ultimo = stack_ts->cabecera->sig;
}

void popStackTS(StackTs stack_ts){
    assert(stack_ts->cabecera->sig != NULL);

    PosicionStackTs pos_ts = stack_ts->cabecera->sig;
    liberaTS(pos_ts->ts);
    stack_ts->cabecera->sig = pos_ts->sig;
    free(pos_ts);
    stack_ts->num_ts--;
}

TablaHash topStackTS(StackTs stack_ts){
    assert(stack_ts->cabecera->sig != NULL);
    return stack_ts->cabecera->sig->ts;
}

TablaHash bottomStackTS(StackTs stack_ts){
    assert(stack_ts->ultimo != NULL);
    return stack_ts->ultimo->ts;
}

TablaHash recuperaStackTS(StackTs stack_ts, PosicionStackTs p){
    assert(p != NULL);
    return p->ts;
}

PosicionStackTs inicioStackTS(StackTs stack_ts){
    return stack_ts->cabecera;
}

PosicionStackTs siguienteStackTS(StackTs stack_ts, PosicionStackTs p){
    assert(p != NULL);
    return p->sig;
}

Simbolo getSimboloStackTS(StackTs stack_ts, char* id){
    PosicionStackTs pos = stack_ts->cabecera->sig;
    int offset = 0;

    while(pos != NULL){
        TablaHash ts = pos->ts;

        Simbolo s = buscaSimboloTS(ts, id);
        if(s.nombre != NULL) {
            s.var_const_local.offset += offset; 
            return s;
        }
        pos = pos->sig;

        TipoTablaHash tipo_ts = getTipoTS(ts);
        if(tipo_ts == LOCAL_TS && s.nombre == NULL) offset += numSimbolos(ts)*4;
    }

    Simbolo s;
    s.nombre = NULL;
    return s;
}

void setTopStackTS(StackTs stack_ts, TablaHash ts){
    assert(stack_ts->cabecera->sig != NULL);
    stack_ts->cabecera->sig->ts = ts;
}

void setBottomStackTS(StackTs stack_ts, TablaHash ts){
    assert(stack_ts->ultimo != NULL);
    stack_ts->ultimo->ts = ts;
}

int getNumTS(StackTs stack_ts){
    return stack_ts->num_ts;
}