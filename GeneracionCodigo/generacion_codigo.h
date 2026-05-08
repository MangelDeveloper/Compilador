// GENERACIÓN DE CÓDIGO (BACKEND DEL COMPILADOR)
// Este módulo se encarga de la generación de código ensamblador (MIPS).
// Funcionalidades principales:
// - Gestión de registros (temporales y argumentos)
// - Generación de etiquetas
// - Secciones .data, .text
// - Traducción de expresiones a código ensamblador
// - Gestión de llamadas a funciones y marcos de pila


#ifndef GENERACION_CODIGO_H
#define GENERACION_CODIGO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "listaCodigo.h"
#include "../Utils/stack.h"
#include "../miniC/funciones.h"
#include "../TablaSimbolos/tabla_simbolos.h"

// CONTADORES Y RECURSOS GLOBALES
// Contador de etiquetas del compilador
extern int label_count;
// Contador de strings asciiz generados
extern int asciiz_count;
// Registro de disponibilidad de registros temporales
extern char registros_temporales[10];
// Registro de disponibilidad de registros de argumentos
extern char registros_argumentos[4];
// Fichero de salida del código ensamblador
extern FILE *fasm;

// GESTIÓN DE REGISTROS
/**
 * @brief Inicializa la estructura de gestión de registros.
 */
void inicializar_reg();

/**
 * @brief Reserva un registro del tipo indicado.
 */
char *obtener_reg(char *tipo_registro);

/**
 * @brief Obtiene un registro temporal disponible.
 */
char *obtener_reg_temporal();

/**
 * @brief Obtiene un registro de argumento disponible.
 */
char *obtener_reg_argumento();

/**
 * @brief Libera el registro pasado por parámetro.
 */
void liberar_reg(char *reg);

/**
 * @brief Libera un registro temporal.
 */
void liberar_reg_temporal(char *reg);

/**
 * @brief Libera un registro de argumento.
 */
void liberar_reg_argumento(char *reg);

// SECCIONES DEL PROGRAMA
/**
 * @brief Escribe la sección .data del programa.
 */
void escribir_seccion_data();

/**
 * @brief Escribe la sección .text del programa.
 */
void escribir_seccion_text();

/**
 * @brief Escribe la sección final del programa.
 */
void escribir_seccion_fin();

/**
 * @brief Declara un string en la sección de datos.
 */
char* escribir_asciiz(char *msg);

/**
 * @brief Escribe una variable con valor inicial.
 */
void escribir_id(char *nombre, int valor);

/**
 * @brief Escribe una lista de código ensamblador.
 */
void escribir_lc(ListaC codigo);

/**
 * @brief Genera una nueva etiqueta única.
 */
char* nueva_etiqueta(char *nombre_etiqueta);


// GENERACIÓN DE CARGAS (LOAD)
ListaC generar_load_immediate(char *expr1);
ListaC generar_load_simbolo(Simbolo s);
ListaC generar_load_parametro(Simbolo s);
ListaC generar_load_offset(int offset);
ListaC generar_load_global(char *label);
ListaC generar_load_asciiz(char *label);


// GENERACIÓN DE STORE Y EXPRESIONES
ListaC generar_store(ListaC expr1, Simbolo s);
ListaC generar_expresion_unaria(ListaC expr);
ListaC generar_expresion_binaria(ListaC expr1, ListaC expr2, char *op);

// CONTROL DE FLUJO
ListaC generar_etiqueta(char *etq);
ListaC generar_salto_condicional(char *op, ListaC expr1, char* etq);
ListaC generar_b(char *etiqueta);

// ENTRADA / SALIDA
ListaC generar_print_asciiz(char *etiqueta);
ListaC generar_print_expresiones(ListaC codigo);
ListaC generar_read(char *ide);

// FINALIZACIÓN DEL PROGRAMA
ListaC generar_exit();

// RETURN Y FUNCIONES
ListaC generar_return(char *label);
ListaC generar_return_con_valor(ListaC expr, char *label);

// MARCOS DE PILA (CALL STACK)
//Llamada a una función
ListaC generar_inicio_marco_pila_llamada(Args args);
ListaC generar_llamada_funcion(char *function_name, Args args);
ListaC generar_fin_marco_pila_llamada(Args args);

//Dentro de una función
ListaC generar_inicio_marco_pila(int is_func_main);
ListaC generar_fin_marco_pila(int is_func_main, char *label);

// BLOQUES Y ÁMBITOS
ListaC generar_inicio_llaves(int num_vars);
ListaC generar_fin_llaves(int num_vars);
#endif