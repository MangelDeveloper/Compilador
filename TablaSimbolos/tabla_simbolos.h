// TABLA DE SÍMBOLOS
// Este módulo gestiona la capa semántica del compilador.
// Se encarga de:
// - Control de ámbitos mediante pila de tablas de símbolos
// - Gestión de offsets de variables
// - Tabla global de símbolos
// - Gestión de literales string (asciiz)
// - Detección de errores semánticos
// - Validación de declaraciones y uso de identificadores

#ifndef TABLA_SIMBOLOS_H
#define TABLA_SIMBOLOS_H

#include "../Utils/stack_tabla_simbolos.h"
#include "../Utils/stack_int.h"
#include "../GeneracionCodigo/generacion_codigo.h"
#include <assert.h>

// VARIABLES GLOBALES DEL COMPILADOR
// Pila de tablas de símbolos (gestión de ámbitos)
extern StackTs stack_ts;
// Pila de offsets (gestión de variables locales)
extern StackInt stack_offset;
// Tabla hash global de símbolos
extern TablaHash ts_global;
// Tabla hash para literales de tipo string (asciiz)
extern TablaHash ts_str;
// Tipo actual en declaración
extern Tipo t;


// MENSAJES DE ERROR SEMÁNTICO
// Strings usados para reportar errores durante el análisis semántico.
extern char *not_read_const;
extern char *not_declared;
extern char *not_mod_const;
extern char *not_redeclared_variable;
extern char *not_redeclared_function;
extern char *not_declared_function;
extern char *err_num_args;
extern char *not_return_void;
extern char *not_return_int;
extern char *not_return;
extern char *not_function;
extern char *not_variable;

// FUNCIONES DEL ANÁLISIS SEMÁNTICO

/**
 * @brief Declara un identificador con tipo en el ámbito actual.
 */
void declarar_id(char *id, Tipo t);

/**
 * @brief Declara una variable global con valor inicial.
 */
void declarar_id_global(char *id, char *value);

/**
 * @brief Declara un literal string (asciiz).
 */
void declarar_asciiz(char *label, char *asciiz);

/**
 * @brief Declara una función con su tipo de retorno y parámetros.
 */
void declarar_funcion(char *function_name, TipoRetorno tipo_ret, Params params);

/**
 * @brief Escribe las variables globales en la sección .data
 */
void escribir_ls();

/**
 * @brief Comprueba que un identificador ha sido declarado.
 */
void check_id(char *id);

/**
 * @brief Comprueba una llamada a función (existencia y número de argumentos).
 */
void check_funcion(char *id, int num_args);

/**
 * @brief Comprueba modificación de constantes.
 */
void check_const(char *id, char *msg);

/**
 * @brief Verifica compatibilidad del tipo de retorno.
 */
void check_return(TipoRetorno tipo_return, TipoRetorno tipo_esperado);

/**
 * @brief Verifica que una función tenga return cuando es necesario.
 */
void check_has_return(char *ide, TipoRetorno tipo_return, int has_return);

/**
 * @brief Recupera el valor de un identificador.
 */
int recupera_valor(char *id);
#endif