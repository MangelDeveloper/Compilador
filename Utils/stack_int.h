// PILA DE ENTEROS (STACK DE INT)
// Esta estructura implementa una pila dinámica de enteros.
// Se usa para almacenar valores enteros con política LIFO
// (Last In, First Out).
// Internamente usa un array dinámico con capacidad variable.


#ifndef STACK_INT_H
#define STACK_INT_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct StackIntRep{
    int *value;
    int top;
    int capacity;
} StackIntRep;

//Pila de enteros
typedef struct StackIntRep *StackInt;


// OPERACIONES BÁSICAS

/**
 * @brief Crea una pila de enteros vacía.
 * @return StackInt inicializada.
 */
StackInt stack_create_int();

/**
 * @brief Inserta un entero en la cima de la pila.
 * @param s Pila destino.
 * @param value Valor a insertar.
 */
void stack_push_int(StackInt s, int value);

/**
 * @brief Elimina y devuelve el elemento en la cima de la pila.
 * @param s Pila.
 * @return Entero eliminado de la cima.
 */
int stack_pop_int(StackInt s);

/**
 * @brief Obtiene el valor de la cima sin eliminarlo.
 * @param s Pila.
 * @return Entero en la cima.
 */
int stack_top_int(StackInt s);

/**
 * @brief Comprueba si la pila está vacía.
 * @param s Pila.
 * @return 1 si está vacía, 0 en caso contrario.
 */
int stack_empty_int(StackInt s);

/**
 * @brief Libera toda la memoria asociada a la pila.
 * @param s Pila a liberar.
 */
void stack_free_int(StackInt s);

/**
 * @brief Modifica el valor del elemento en la cima sin desapilarlo.
 * @param s Pila.
 * @param value Nuevo valor para la cima.
 */
void stack_set_top(StackInt s, int value);

#endif