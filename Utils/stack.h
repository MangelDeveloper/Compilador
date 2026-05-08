// PILA DE STRINGS (STACK DE CADENAS)
// Esta estructura implementa una pila genérica de cadenas (char *).
// Sigue el comportamiento LIFO (Last In, First Out).
#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <assert.h>

typedef char * TipoDato;

// Estructura opaca de la pila de strings
typedef struct StackStr * Stack;

// OPERACIONES BÁSICAS
/**
 * @brief Crea una nueva pila vacía.
 * @return Stack inicializada.
 */
Stack stack_crear();

/**
 * @brief Libera toda la memoria asociada a la pila.
 * @param s Pila a liberar.
 */
void stack_liberar(Stack s);

/**
 * @brief Inserta un elemento en la cima de la pila.
 * @param s Pila destino.
 * @param valor Cadena a insertar.
 */
void stack_push(Stack s, TipoDato valor);

/**
 * @brief Obtiene el elemento en la cima sin eliminarlo.
 * @param s Pila.
 * @return Cadena en la cima.
 */
TipoDato stack_top(Stack s);

/**
 * @brief Elimina el elemento en la cima de la pila.
 * @param s Pila.
 * @return true si se pudo eliminar, false si la pila estaba vacía.
 */
bool stack_pop(Stack s);

/**
 * @brief Devuelve el número de elementos en la pila.
 * @param s Pila.
 * @return Tamaño actual de la pila.
 */
int stack_size(Stack s);

/**
 * @brief Comprueba si la pila está vacía.
 * @param s Pila.
 * @return true si está vacía, false en caso contrario.
 */
bool stack_empty(Stack s);

#endif