#include "tabla_simbolos.h"

StackTs stack_ts;
StackInt stack_offset;
TablaHash ts_global;
TablaHash ts_str;
Tipo t;

static Simbolo *datos_ids = NULL;
static int num_ids = 0;
static int capacidad_ids = 0;

//Mensajes de error semántico
char *not_read_const = "Error semántico en la línea %d: no se puede leer la constante '%s'\n";
char *not_declared = "Error semántico en la línea %d: '%s' no está declarado\n";
char *not_mod_const = "Error semántico en la línea %d: no se puede modificar la constante '%s'\n";
char *not_redeclared_variable = "Error semántico en la línea %d: no se puede crear la variable '%s' porque ya ha sido declarada\n";
char *not_redeclared_function = "Error semántico en la línea %d: no se puede crear la función '%s' porque ya ha sido creada\n";
char *not_declared_function = "Error semántico en la línea %d: La función %s no ha sido declarada\n";
char *err_num_args = "Error semántico en la línea %d: Número incorrecto de argumentos para la función %s\n";
char *not_return_void = "Error semántico en la línea %d: La función de tipo VOID no debe devolver un valor\n";
char *not_return_int = "Error semántico en la línea %d: La función de tipo INT no se ha devuelto ningún valor\n";
char *not_return = "Error semántico en la línea %d: La función %s de tipo INT debe tener al menos un return\n";
char *not_function = "Error semántico en la línea %d: La función '%s' ya existe como variable\n";
char *not_variable = "Error semántico en la línea %d: La variable '%s' ya existe como función\n";

//Variables externas de miniC.y
extern int yylineno;
extern int errores;

static void asegurar_capacidad_ids(int nueva_capacidad) {
    if (capacidad_ids >= nueva_capacidad) return;
    capacidad_ids = nueva_capacidad > capacidad_ids * 2 ? nueva_capacidad : capacidad_ids * 2;
    if (capacidad_ids < 4) capacidad_ids = 4;
    datos_ids = realloc(datos_ids, sizeof(Simbolo) * capacidad_ids);
}

static void append_simbolo(Simbolo s) {
    asegurar_capacidad_ids(num_ids + 1);
    datos_ids[num_ids++] = s;
}

void declarar_id(char *id, Tipo t){
    TablaHash ts = topStackTS(stack_ts);
    Simbolo existente = buscaSimboloTS(ts, id);

    if (existente.nombre != NULL) {
        errores++;
        printf(not_redeclared_variable, yylineno, id);
        return;
    }

    Simbolo funcion = buscaSimboloTS(bottomStackTS(stack_ts), id);
    if (funcion.nombre != NULL && funcion.tipo == FUNCION) {
        errores++;
        printf(not_variable, yylineno, id);
        return;
    }

    Simbolo s;
    if(t == VARIABLE_LOCAL || t == CONSTANTE){
        s.nombre = strdup(id);
        s.var_const_local.value = 0;
        int offset = stack_top_int(stack_offset)+4;
        stack_set_top(stack_offset, offset);
        s.var_const_local.offset = offset;
    }else if(t == PARAMETRO){
        s.nombre = strdup(id);
        s.param.reg = obtener_reg("ARGUMENTO");
    }

    s.tipo = t;
    ts = insertaTS(ts, s);
    
    setTopStackTS(stack_ts, ts);
}

void declarar_id_global(char *id, char *value){
    TablaHash ts = topStackTS(stack_ts);
    Simbolo existente = buscaSimboloTS(ts, id);

    if (existente.nombre != NULL) {
        errores++;
        printf(not_redeclared_variable, yylineno, id);
        return;
    }

    Simbolo s;
    s.nombre = strdup(id);
    s.tipo = VARIABLE_GLOBAL;
    s.var_global.value = atoi(value);
    ts = insertaTS(ts, s);

    ts_global = insertaTS(ts_global, s);

    Simbolo copia = s;
    copia.nombre = strdup(s.nombre);
    append_simbolo(copia);
    
    setTopStackTS(stack_ts, ts);
}

void declarar_asciiz(char *label, char *msg){
    Simbolo string;
    string.nombre = strdup(msg);
    string.asciiz.label = strdup(label);

    insertaTS(ts_str, string);
}

void declarar_funcion(char* function_name, TipoRetorno tipo_ret, Params params){
    TablaHash bottom_stack_ts = bottomStackTS(stack_ts);
    Simbolo existente = buscaSimboloTS(bottom_stack_ts, function_name);

    if (existente.nombre != NULL && existente.tipo == FUNCION) {
        errores++;
        printf(not_redeclared_function, yylineno, function_name);
        return;
    }

    Simbolo variable = buscaSimboloTS(ts_global, function_name);
    if (variable.nombre != NULL && (variable.tipo == VARIABLE_LOCAL || variable.tipo == CONSTANTE || variable.tipo == VARIABLE_GLOBAL)) {
        errores++;
        printf(not_function, yylineno, function_name);
        return;
    }

    Simbolo function;
    function.tipo = FUNCION;
    function.nombre = strdup(function_name);
    function.func.num_params = params.num;
    function.func.ret = tipo_ret;

    bottom_stack_ts = insertaTS(bottom_stack_ts, function);
    setBottomStackTS(stack_ts, bottom_stack_ts);
}

void escribir_ls(){
    for (int i = 0; i < num_ids; i++) {
        escribir_id(datos_ids[i].nombre, datos_ids[i].var_global.value);
    }
}


void check_id(char *id){
    Simbolo s = getSimboloStackTS(stack_ts, id);

    if(s.nombre == NULL){
        errores++;
        printf(not_declared, yylineno, id);
    } else if (s.tipo == FUNCION){
        errores++;
        printf(not_function, yylineno, id);
    }
}

void check_const(char *id, char *msg){    
    Simbolo s = getSimboloStackTS(stack_ts, id);

    if(s.nombre != NULL && s.tipo == CONSTANTE){
        errores++;
        printf(msg, yylineno, s.nombre);
    }
}

void check_return(TipoRetorno tipo_return, TipoRetorno tipo_esperado){
    if(tipo_return == TIPO_VOID && tipo_esperado == TIPO_INT){
        errores++;
        printf(not_return_void,yylineno);
    }else if(tipo_return == TIPO_INT && tipo_esperado == TIPO_VOID){
        errores++;
        printf(not_return_int,yylineno);
    }
}

void check_has_return(char *ide, TipoRetorno tipo_return, int has_return){
    if(tipo_return == TIPO_INT && has_return == 0){
        errores++;
        printf(not_return,yylineno, ide);
    }
}

void check_funcion(char *id, int num_args){
    Simbolo s = getSimboloStackTS(stack_ts, id);

    if (s.nombre == NULL) {
        errores++;
        printf(not_declared_function, yylineno, id);
    } else if (s.tipo != FUNCION) {
        errores++;
        printf(not_function, yylineno, id);
    } else if (s.func.num_params != num_args) {
        errores++;
        printf(err_num_args, yylineno, id);
    }
}

int recupera_valor(char* id){
    Simbolo s = getSimboloStackTS(stack_ts, id);

    if(s.nombre == NULL){
        errores++;
        printf(not_declared, yylineno, id);
        return 0;
    }

    return s.var_const_local.value;
}