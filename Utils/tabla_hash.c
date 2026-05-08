#include "tabla_hash.h"

// Tabla hash de símbolos
// Implementación mediante dispersión abierta (encadenamiento)
// Cada posición de la tabla apunta a una lista de símbolos
typedef struct TablaHashRep{
    //Tipo de tabla de símbolo
    TipoTablaHash tipo_ts;
    // Array dinámico de listas de símbolos
    Lista *tabla;
    // Tamaños actual de la tabla hash - Cubetas
    int cubetas;
    // Número total de símbolos almacenados - Elementos en total de todas las cubetas       
    int num_simbolos;
    // Número de variables declaradas
    int num_vars;
    // Número de llamadas a funciones
    int num_func;
}TablaHashRep;

struct PosicionListaRep {
    Simbolo dato;
    struct PosicionListaRep *sig;
};

struct ListaRep {
    PosicionLista cabecera;
    PosicionLista ultimo;
};

typedef struct PosicionListaRep *NodoPtr;


TablaHash creaTS(TipoTablaHash tipo_ts){
    int num_cubetas = 113;
    //Nueva tabla hash
    TablaHash new_ts = malloc(sizeof(struct TablaHashRep));
    new_ts->tabla = malloc(sizeof(Lista*) * num_cubetas);
    new_ts->cubetas = num_cubetas;
    new_ts->num_simbolos = 0;
    new_ts->num_vars = 0;
    new_ts->num_func = 0;
    new_ts->tipo_ts = tipo_ts;

    for (int i = 0; i < num_cubetas; i++)
        new_ts->tabla[i] = creaLS();

    return new_ts;
}

void liberaTS(TablaHash ts){
    for (int i = 0; i < ts->cubetas; i++) liberaLS(ts->tabla[i]);
    free(ts->tabla);
    free(ts);
}

TablaHash insertaTS(TablaHash ts, Simbolo s){
    char *name = s.nombre;

    // Comprobar si ya existe
    Simbolo existente = buscaSimboloTS(ts, name);
    if (existente.nombre != NULL) return ts;

    // Factor de carga
    float factor = (float)ts->num_simbolos / ts->cubetas;

    // Rehash si es necesario
    if (factor > UMBRAL_REESTRUCTURACION) ts = rehash(ts);

    // Calculamos el hash del símbolo
    unsigned int idx = hash(name, ts->cubetas);

    // Inserción en cabeza
    Lista list = recuperaLista(idx, ts);
    insertaLS(list, list->ultimo, s);

    // Actualizamos contador
    ts->num_simbolos++;

    if(s.tipo == VARIABLE_LOCAL || s.tipo == CONSTANTE || s.tipo == VARIABLE_GLOBAL) ts->num_vars++;
    else if(s.tipo == FUNCION) ts->num_func++;

    return ts;
}

PosicionLista buscaTS(TablaHash ts, char *nombre){
    int idx = hash(nombre, ts->cubetas);
    Lista list = recuperaLista(idx, ts);
    
    return buscaLS(list, nombre);
}

Simbolo buscaSimboloTS(TablaHash ts, char *nombre){
    PosicionLista p = buscaTS(ts, nombre);
    Lista list = recuperaLista(hash(nombre, numCubetas(ts)), ts);

    if (p == finalLS(list)) {
        Simbolo s;
        s.tipo = NONE;
        s.nombre = NULL;
        return s;
    }

    return recuperaLS(list, p);
}

void asignaTS(TablaHash ts, char *nombre, Simbolo s){
    PosicionLista pos = buscaTS(ts, nombre);
    Lista list = recuperaLista(hash(nombre, numCubetas(ts)),ts);
    asignaLS(list, pos, s);
}

int is_primo(int n) {
    if (n < 2) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;

    for (int i = 3; i <= n / i; i += 2)
        if (n % i == 0) return 0;

    return 1;
}

int siguiente_primo(int n) {
    while (!is_primo(n)) n++;
    return n;
}

// Función hash (djb2)
// Convierte un string en un índice dentro de la tabla
unsigned int hash(const char *str, int size) {
    unsigned int hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash % size;
}

// Redispersión (rehashing)
// Reasigna todos los símbolos a una nueva tabla de mayor tamaño
// para reducir colisiones cuando el factor de carga es alto
TablaHash rehash(TablaHash ts) {
    TablaHash new_ts = malloc(sizeof(struct TablaHashRep));
    int old_cubetas = ts->cubetas;
    int new_cubetas = siguiente_primo(ts->cubetas * 2);

    new_ts->tabla = malloc(sizeof(Lista*) * new_cubetas);
    new_ts->cubetas = new_cubetas;
    new_ts->num_simbolos = ts->num_simbolos;
    new_ts->num_vars = ts->num_vars;
    new_ts->num_func = ts->num_func;
    new_ts->tipo_ts = ts->tipo_ts;
    
    for (int i = 0; i < new_cubetas; i++)
        new_ts->tabla[i] = creaLS();

    for (int i = 0; i < old_cubetas; i++) {
        Lista list_old = recuperaLista(i, ts);
        PosicionLista pos = list_old->cabecera->sig;
        PosicionLista final = list_old->ultimo;

        while (pos != final) {
            Simbolo s = pos->dato;

            unsigned int idx = hash(s.nombre, new_ts->cubetas);

            Lista list_new = recuperaLista(idx, new_ts);
            insertaLS(list_new, list_new->ultimo, s);
            
            pos = pos->sig;
        }
    }

    free(ts->tabla);
    free(ts);

    return new_ts;
}

int numCubetas(TablaHash ts){
    return ts->cubetas;
}

int numSimbolos(TablaHash ts){
    return ts->num_simbolos;
}

int numVars(TablaHash ts){
    return ts->num_vars;
}

int numFunc(TablaHash ts){
    return ts->num_func;
}

TipoTablaHash getTipoTS(TablaHash ts){
    return ts->tipo_ts;
}

Lista *tablaHash(TablaHash ts){
    return ts->tabla;
}

Lista recuperaLista(int id, TablaHash ts){
    return ts->tabla[id];
}

Lista creaLS() {
    Lista nueva = malloc(sizeof(struct ListaRep));
    nueva->cabecera = malloc(sizeof(struct PosicionListaRep));
    nueva->cabecera->sig = NULL;
    nueva->ultimo = nueva->cabecera;
    return nueva;
}

void liberaLS(Lista lista) {
    while (lista->cabecera != NULL) {
        NodoPtr borrar = lista->cabecera;
        lista->cabecera = borrar->sig;
        free(borrar);
    }

    free(lista);
}

void insertaLS(Lista lista, PosicionLista p, Simbolo s) {
    NodoPtr nuevo = malloc(sizeof(struct PosicionListaRep));
    nuevo->dato = s;
    nuevo->sig = p->sig;
    p->sig = nuevo;
    if (lista->ultimo == p) lista->ultimo = nuevo;
}

void suprimeLS(Lista lista, PosicionLista p) {
    assert(p != lista->ultimo);
    NodoPtr borrar = p->sig;
    p->sig = borrar->sig;
    if (lista->ultimo == borrar) lista->ultimo = p;
    free(borrar);
}

Simbolo recuperaLS(Lista lista, PosicionLista p) {
    assert(p != lista->ultimo);
    return p->sig->dato;
}

PosicionLista buscaLS(Lista lista, char *nombre) {
    NodoPtr aux = lista->cabecera;
    while (aux->sig != NULL && strcmp(aux->sig->dato.nombre,nombre) != 0) {
        aux = aux->sig;
    }
    return aux;
}

void asignaLS(Lista lista, PosicionLista p, Simbolo s) {
    assert(p != lista->ultimo);

    if(p->sig != NULL){
        p->sig->dato.nombre = s.nombre;
        p->sig->dato.tipo = s.tipo;
        if(s.tipo == VARIABLE_LOCAL || s.tipo == CONSTANTE){
            p->sig->dato.var_const_local.value = s.var_const_local.value;
            p->sig->dato.var_const_local.offset = s.var_const_local.offset;
        }else if(s.tipo == VARIABLE_GLOBAL){
            //POR IMPLEMENTAR
        }else if(s.tipo == PARAMETRO) p->sig->dato.param.reg = strdup(s.param.reg);
        else if(s.tipo == FUNCION){
            p->sig->dato.func.num_params = s.func.num_params;
            p->sig->dato.func.ret = s.func.ret;
        }
    }
}

PosicionLista inicioLS(Lista lista) {
    return lista->cabecera;
}

PosicionLista finalLS(Lista lista) {
    return lista->ultimo;
}

PosicionLista siguienteLS(Lista lista, PosicionLista p) {
    assert(p != lista->ultimo);
    return p->sig;
}