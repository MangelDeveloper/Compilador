// TABLA HASH DE SÍMBOLOS
// Esta estructura implementa una tabla hash para la gestión de símbolos

#ifndef TABLA_HASH_H
#define TABLA_HASH_H

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "../miniC/funciones.h"

// Umbral para la reestructuración de la tabla hash
#define UMBRAL_REESTRUCTURACION 2

// TIPOS DE SÍMBOLO
// Indica qué tipo de entidad representa un símbolo.
typedef enum { 
    VARIABLE_LOCAL = 1, 
    VARIABLE_GLOBAL = 2,
    CONSTANTE = 3, 
    FUNCION = 4,
    PARAMETRO = 5,
    NONE = 6
} Tipo;


// TIPOS DE TABLA HASH (CONTEXTO)
// Indica el contexto donde se usa la tabla.
typedef enum{
    LOCAL_TS = 1,
    GLOBAL_TS = 2,
    PARAMETRO_TS = 3,
} TipoTablaHash;


// ESTRUCTURAS DE ATRIBUTOS DE SÍMBOLOS
// Información de una función
typedef struct Funcion{
    // Tipo de retorno (int, void, etc.)
    TipoRetorno ret;   
    // Número de parámetros
    int num_params;    
} Funcion;

// Variable o constante en ámbito local
typedef struct VariableConstanteLocal{
    // Valor asociado
    int value; 
    // Offset en memoria o stack  
    int offset;  
} VariableConstanteLocal;

// Variable global
typedef struct VariableGlobal{
    // Valor global
    int value;   
} VariableGlobal;

// Parámetro de función
typedef struct Parametro{
    // Registro asociado (ej: $t0, $a0)
    char *reg;   
} Parametro;

// Cadena tipo asciiz (literal de texto)
typedef struct Asciiz{
     // Etiqueta tipo $str0, $str1...
    char *label;
} Asciiz;

// SÍMBOLO (NODO PRINCIPAL)
// Representa cualquier entidad del lenguaje (variable, función, etc.)
// almacenada en la tabla hash.
//
typedef struct Nodo{
    // Identificador del símbolo
    char *nombre;  

    // Tipo de símbolo
    Tipo tipo;     

    // Atributos especializados según el tipo
    VariableConstanteLocal var_const_local;
    VariableGlobal var_global;
    Parametro param;
    Funcion func;
    Asciiz asciiz;

} Simbolo;


typedef struct ListaRep *Lista;
typedef struct PosicionListaRep *PosicionLista;
typedef struct TablaHashRep * TablaHash;


// OPERACIONES DE LA TABLA HASH

/**
 * @brief Devuelve el número de cubetas (buckets).
 */
int numCubetas(TablaHash ts);

/**
 * @brief Devuelve el número total de símbolos almacenados.
 */
int numSimbolos(TablaHash ts);

/**
 * @brief Devuelve el número de variables en la tabla.
 */
int numVars(TablaHash ts);

/**
 * @brief Devuelve el número de funciones en la tabla.
 */
int numFunc(TablaHash ts);

/**
 * @brief Devuelve el tipo de tabla hash (local, global, parámetros).
 */
TipoTablaHash getTipoTS(TablaHash ts);

/**
 * @brief Recupera la lista asociada a una cubeta concreta.
 */
Lista recuperaLista(int id, TablaHash ts);

/**
 * @brief Crea una nueva tabla hash del tipo indicado.
 */
TablaHash creaTS(TipoTablaHash tipo_ts);

/**
 * @brief Libera toda la memoria de la tabla hash.
 */
void liberaTS(TablaHash ts);

/**
 * @brief Inserta un símbolo en la tabla hash.
 */
TablaHash insertaTS(TablaHash ts, Simbolo s);

/**
 * @brief Busca una posición de un símbolo por nombre.
 */
PosicionLista buscaTS(TablaHash ts, char *nombre);

/**
 * @brief Busca un símbolo por nombre.
 */
Simbolo buscaSimboloTS(TablaHash ts, char *nombre);

/**
 * @brief Asigna o actualiza un símbolo en la tabla.
 */
void asignaTS(TablaHash ts, char *nombre, Simbolo s);


// FUNCIONES HASH Y REHASHING

/**
 * @brief Función hash para strings.
 */
unsigned int hash(const char *str, int size);

/**
 * @brief Reorganiza la tabla cuando crece demasiado.
 */
TablaHash rehash(TablaHash ts);

/**
 * @brief Comprueba si un número es primo.
 */
int is_primo(int n);

/**
 * @brief Devuelve el siguiente número primo.
 */
int siguiente_primo(int n);


// LISTA ENLAZADA

/**
 * @brief Crea una nueva lista de símbolos.
 */
Lista creaLS();

/**
 * @brief Libera una lista de símbolos.
 */
void liberaLS(Lista lista);

/**
 * @brief Inserta un símbolo en una posición de la lista.
 */
void insertaLS(Lista lista, PosicionLista p, Simbolo s);

/**
 * @brief Recupera un símbolo de una posición.
 */
Simbolo recuperaLS(Lista lista, PosicionLista p);

/**
 * @brief Busca un símbolo por nombre en la lista.
 */
PosicionLista buscaLS(Lista lista, char *nombre);

/**
 * @brief Asigna un símbolo en una posición.
 */
void asignaLS(Lista lista, PosicionLista p, Simbolo s);

/**
 * @brief Devuelve la primera posición de la lista.
 */
PosicionLista inicioLS(Lista lista);

/**
 * @brief Devuelve la última posición de la lista.
 */
PosicionLista finalLS(Lista lista);

/**
 * @brief Avanza a la siguiente posición.
 */
PosicionLista siguienteLS(Lista lista, PosicionLista p);

#endif

