#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "../GeneracionCodigo/listaCodigo.h"

typedef enum {
    TIPO_INT,
    TIPO_VOID,
    TIPO_NONE
} TipoRetorno;

typedef struct Args{
    //Número de argumentos
    int num;
    //Array dinámico de registros que son pasado por los argumentos
    char **registros;
    //Lista de código de cada argumento
    ListaC codigo_argumentos;
} Args;

typedef struct Params{
    //Array dinámico con el identificador de cada parámetro
    char **nombres;
    //Número de parámetros de dicha función
    int num;
} Params;

#endif