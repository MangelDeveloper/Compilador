// PILA DE TABLAS DE SÍMBOLOS
// Esta estructura implementa una pila (stack) de tablas hash de símbolos.
// Se usa para gestionar ámbitos (scopes):
// - Cada nivel de la pila representa un ámbito (global, función, bloque, etc.)
// - Al entrar en un bloque se hace push de una nueva tabla
// - Al salir se hace pop
#ifndef STACK_TABLA_SIMBOLOS_H
#define STACK_TABLA_SIMBOLOS_H

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "tabla_hash.h"

// Estructura principal de la pila de tablas de símbolos
typedef struct StackRep *StackTs;
// Posición dentro de la pila (iterador interno)
// Permite recorrer la pila sin exponer su implementación
typedef struct PosicionStackRep *PosicionStackTs;


// OPERACIONES BÁSICAS DE LA PILA
/**
 * @brief Crea una nueva pila de tablas de símbolos vacía.
 * @return StackTs inicializada.
 */
StackTs creaStackTS();

/**
 * @brief Libera toda la memoria asociada a la pila y sus tablas.
 * @param stack_ts Pila a liberar.
 */
void liberaStackTS(StackTs stack_ts);

/**
 * @brief Inserta una nueva tabla de símbolos en la cima de la pila.
 * @param stack_ts Pila destino.
 * @param ts Tabla de símbolos a insertar.
 */
void pushStackTS(StackTs stack_ts, TablaHash ts);

/**
 * @brief Elimina la tabla de símbolos en la cima de la pila.
 * @param stack_ts Pila a modificar.
 */
void popStackTS(StackTs stack_ts);

/**
 * @brief Obtiene la tabla de símbolos en la cima de la pila.
 * @param stack_ts Pila.
 * @return TablaHash en la cima.
 */
TablaHash topStackTS(StackTs stack_ts);

/**
 * @brief Modifica la tabla de la cima de la pila por otra nueva.
 * @param stack_ts Pila.
 * @param ts Nueva tabla para la cima.
 */
void setTopStackTS(StackTs stack_ts, TablaHash ts);

/**
 * @brief Obtiene la tabla de símbolos en el fondo de la pila (ámbito global).
 * @param stack_ts Pila.
 * @return TablaHash del fondo.
 */
TablaHash bottomStackTS(StackTs stack_ts);

/**
 * @brief Sustituye la tabla de símbolos del fondo de la pila.
 * @param stack_ts Pila.
 * @param ts Nueva tabla para el fondo.
 */
void setBottomStackTS(StackTs stack_ts, TablaHash ts);

/**
 * @brief Obtiene la tabla de símbolos almacenado en una posición concreta de la pila.
 * @param stack_ts Pila.
 * @param p Posición dentro de la pila.
 * @return La tabla de símbolos buscada.
 */
TablaHash recuperaStackTS(StackTs stack_ts, PosicionStackTs p);

/**
 * @brief Devuelve la primera posición válida de la pila.
 * @param stack_ts Pila.
 * @return Posición inicial.
 */
PosicionStackTs inicioStackTS(StackTs stack_ts);

/**
 * @brief Avanza a la siguiente posición en la pila.
 * @param stack_ts Pila.
 * @param p Posición actual.
 * @return Siguiente posición.
 */
PosicionStackTs siguienteStackTS(StackTs stack_ts, PosicionStackTs p);

/**
 * @brief Busca un identificador en toda la pila de tablas de símbolos.
 *
 * La búsqueda se realiza desde la cima (ámbito más cercano) hacia el fondo
 * (ámbito global).
 *
 * @param stack_ts Pila de tablas.
 * @param id Identificador a buscar.
 * @return Símbolo encontrado (si existe).
 */
Simbolo getSimboloStackTS(StackTs stack_ts, char* id);

/**
 * @brief Devuelve el número de tablas de símbolos en la pila.
 * @param stack_ts Pila.
 * @return Número de niveles (ámbitos).
 */
int getNumTS(StackTs stack_ts);
#endif