%{
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <assert.h>
    
    //Utilidades
    #include "../Utils/stack.h"
    #include "../Utils/stack_int.h"
    #include "../Utils/tabla_hash.h"
    
    //Tabla de símbolos
    #include "../TablaSimbolos/tabla_simbolos.h"

    //Generación de código
    #include "../GeneracionCodigo/generacion_codigo.h"
    #include "../GeneracionCodigo/listaCodigo.h"
    #include "funciones.h"

    //Variables externas definidas en flex
    extern int yylineno;
    extern int yylex();
    extern int errores;

    //Mensajes de error sintáctico
    const char *SYNTACTIC_ERR = "Error sintáctico en línea %d: %s\n";
    const char *BREAK_ERR = "El break no está dentro de un bucle.";
    const char *MAIN_ERR = "El programa debe tener la función main.";

    Stack etiquetas_loop;
    int has_main = 0;
    //Booleano para saber si la función en la que estoy es main o no
    int is_func_main = 0;
    //Booleano para saber si estoy analizando dentro de una función
    int is_in_function = 0;
    //Es una variable global que almacena el tipo de retorno de la función en la que estoy
    TipoRetorno tipo_funcion_actual;
    //Booleanos para saber si tiene return una función o no
    int has_return;
    //Almacena la etiqueta fin de funcion
    char *fin_funcion;

    //Función auxiliar
    void yyerror(const char *msg);
    void print_error(const char *msg);
    void is_main(char * funcion);
%}

%define parse.error detailed

%code requires{
  #include "../GeneracionCodigo/listaCodigo.h"
  #include "funciones.h"
}

%union {
    char* cadena;
    //Lista de código 
    ListaC codigo;
    //Para saber el tipo de retorno de una función
    TipoRetorno tipo_retorno;
    //Número de parámetros para param_list
    Params params;
    //Número de argumentos y su código generado de arg_list
    Args args;
}

%token <cadena> IDE CAD NUM
%token VOI VAR CON INT IF ELS WHI PRI REA DO FOR BRK RET
%token MAS "+" MEN "-" POR "*" DIV "/" IGU "=" PYC ";" PAI "(" PAD ")" LLI "{" LLD "}" COM ","
%token EQ "==" NEQ "!=" GT ">" GTE ">=" LT "<" LTE "<="

%type <codigo> body expression statement asignation print_list print_item read_list block function function_list 
%type <codigo> call_function id_list id_decl declaration
%type <tipo_retorno> return_function
%type <params> param_list param_decl
%type <args> arg_list

%nonassoc EQ NEQ GT GTE LT LTE
%left "+" "-"
%left "*" "/"
%right UMINUS
%precedence NOELSE
%precedence ELS
//%define parse.trace usar {yydebug = 1}

%%

program:
  {
    stack_ts = creaStackTS();
    stack_offset = stack_create_int();
    ts_global = creaTS(GLOBAL_TS);
    ts_str = creaTS(GLOBAL_TS);
    pushStackTS(stack_ts, creaTS(GLOBAL_TS));

    etiquetas_loop = stack_crear();

    inicializar_reg();
    //Creamos el archivo ensamblador
    fasm = fopen("salida.s", "w");

    if (fasm == NULL) {
      perror("No se pudo crear el archivo");
      exit(1);
    }

    escribir_seccion_data();
  } global_declarations function_list {
    //Comprobamos si sigue existiendo el main
    if (has_main == 0) print_error(MAIN_ERR);
    
    ListaC listaCodigo = $3;

    if(errores == 0){
      escribir_ls();
      escribir_seccion_text();
      
      //Escribimos el código
      escribir_lc(listaCodigo);

      //Escribimos la sección de fin
      escribir_seccion_fin();
      escribir_lc(generar_exit());
    }

    //Liberación de memoria
    stack_liberar(etiquetas_loop);
    liberaLC(listaCodigo);
    liberaStackTS(stack_ts);
    fclose(fasm);
  }
;

global_declarations:
  %empty
  | global_declarations global_declaration
;

global_declaration:
  VAR tipo global_id_list PYC
;

global_id_list:
    global_id_decl
  | global_id_list COM global_id_decl
;

global_id_decl:
    IDE                 { declarar_id_global($1, "0"); }
  | IDE IGU NUM         { declarar_id_global($1, $3);  }
;

function_list:
  function { $$ = $1; }
  | function_list function { concatenaLC($1, $2); $$ = $1; liberaLC($2); }
;

function:
  return_function IDE PAI {
    //Reinicimamos el booleano a false
    is_func_main = 0;

    is_main($2);

    TablaHash ts = creaTS(PARAMETRO_TS);
    pushStackTS(stack_ts, ts);
  } param_list PAD {
    //Obtengo el tipo que se espera devolver en la función
    tipo_funcion_actual = $1;
    //Nombre de la función
    char *function_name = $2;
    //Parámetros de la función
    Params params = $5;
    //Booleano para saber si tiene return
    has_return = 0;

    //Inserto la función en la tabla de símbolos global (la tabla de símbolos más profunda de la pila)
    declarar_funcion(function_name, tipo_funcion_actual, params);

    //Escribimos la etiqueta fin de función
    fin_funcion = nueva_etiqueta("fin_funcion");
  } block {
      //Tipo de retorno de la función
      TipoRetorno tipo_retorno = $1;
      //Nombre de la función
      char* function_name = $2;
      //Parámetros de la función
      Params params = $5;

      //Comprobamos si hay return
      check_has_return(function_name, tipo_retorno, has_return);

      //Lista de código
      ListaC codigo = creaLC();

      //Generar etiqueta de función
      ListaC etiqueta = generar_etiqueta(function_name);
      concatenaLC(codigo, etiqueta);

      ListaC inicio_marco_pila = generar_inicio_marco_pila(is_func_main);
      concatenaLC(codigo, inicio_marco_pila);

      //Obtenemos el código de block
      concatenaLC(codigo, $8);

      if(is_func_main == 0) 
        concatenaLC(codigo, generar_etiqueta(fin_funcion));

      ListaC fin_marco_pila = generar_fin_marco_pila(is_func_main, fin_funcion);
      concatenaLC(codigo, fin_marco_pila);

      $$ = codigo;
      popStackTS(stack_ts);
    }
;

param_list:
    %empty { 
    $$.num = 0;
    $$.nombres = NULL;
  }
  | param_decl
  | param_list COM param_decl { 
    $$.num = $1.num + $3.num;
    $$.nombres = realloc($1.nombres, $$.num * sizeof(char*));
    $$.nombres[$1.num] = $3.nombres[0];
  }
;

param_decl:
  INT IDE { 
    declarar_id($2, PARAMETRO);
    $$.num = 1;
    $$.nombres = malloc(sizeof(char*));
    $$.nombres[0] = $2;
  }
;

return_function:
  INT { $$ = TIPO_INT; }
  | VOI { $$ = TIPO_VOID; }

block:
    LLI { 
      TablaHash ts = creaTS(LOCAL_TS);
      pushStackTS(stack_ts, ts);
      stack_push_int(stack_offset, 0);
    } body LLD { 
      int num_simbolos = numSimbolos(topStackTS(stack_ts));

      ListaC codigo = creaLC();
      if(num_simbolos > 0) {
        ListaC inicio_llaves = generar_inicio_llaves(num_simbolos);
        concatenaLC(codigo, inicio_llaves);
      }

      concatenaLC(codigo, $3);

      if(num_simbolos > 0){
        ListaC fin_llaves = generar_fin_llaves(num_simbolos);
        concatenaLC(codigo, fin_llaves);
      }

      stack_pop_int(stack_offset);
      popStackTS(stack_ts);
      $$ = codigo;
    } 
;

body:
    body declaration { concatenaLC($1, $2); $$ = $1; liberaLC($2); }
  | body statement { concatenaLC($1, $2); $$ = $1; liberaLC($2); }
  | %empty { $$ = creaLC();}
;

declaration:
    VAR { t = VARIABLE_LOCAL; } tipo id_list PYC { $$ = $4; }
  | CON { t = CONSTANTE; } tipo id_list PYC { $$ = $4; }
;

tipo:
    INT
;

id_list:
    id_decl { $$ = $1; }
  | id_list COM id_decl { concatenaLC($1, $3); $$ = $1; liberaLC($3); }
;

id_decl:
    IDE                 { declarar_id($1, t); $$ = creaLC(); }
  | IDE IGU expression  { 
    declarar_id($1, t);
    Simbolo s = getSimboloStackTS(stack_ts, $1);
    $$ = generar_store($3, s);
  }
;

statement:
  asignation PYC { $$ = $1; }
  | call_function PYC { $$ = $1; }
  | RET expression PYC { 
    //Este será el return para funciones que devuelve un INT
    has_return = 1;
    check_return(tipo_funcion_actual, TIPO_INT);
    $$ = generar_return_con_valor($2,fin_funcion);
  } 
  | RET PYC { 
    //Este será el return vacío 
    has_return = 1;
    check_return(tipo_funcion_actual, TIPO_VOID);
    $$ = generar_return(fin_funcion);
  }     
  | block { $$ = $1; }
  | IF PAI expression PAD statement %prec NOELSE {
    char *etiqueta_end_if = nueva_etiqueta("end_if");

    ListaC if_simple = creaLC();
    ListaC salto_condicional = generar_salto_condicional("beqz", $3, etiqueta_end_if);
    ListaC etiqueta = generar_etiqueta(etiqueta_end_if);
    
    concatenaLC(if_simple, salto_condicional);
    concatenaLC(if_simple, $5);
    concatenaLC(if_simple, etiqueta);

    $$ = if_simple;
  }
  | IF PAI expression PAD statement ELS statement {
    char *etiqueta1 = nueva_etiqueta("else");
    char *etiqueta2 = nueva_etiqueta("end_if");

    ListaC if_else = creaLC();
    ListaC salto_condicional = generar_salto_condicional("beqz", $3, etiqueta1);
    ListaC b = generar_b(etiqueta2); 
    ListaC etiqueta_else = generar_etiqueta(etiqueta1);
    ListaC etiqueta_end_if = generar_etiqueta(etiqueta2);

    concatenaLC(if_else, salto_condicional);
    concatenaLC(if_else, $5);
    concatenaLC(if_else, b);
    concatenaLC(if_else, etiqueta_else);
    concatenaLC(if_else, $7);
    concatenaLC(if_else, etiqueta_end_if);

    $$ = if_else;
  }
  | WHI { stack_push(etiquetas_loop, nueva_etiqueta("while_end")); } PAI expression PAD statement{
    //Creamos la etiqueta del inicio while
    char *etiqueta1 = nueva_etiqueta("while_start");
    char *etiqueta2 = stack_top(etiquetas_loop);
    
    ListaC while_loop = creaLC();
    ListaC etiqueta_while_start = generar_etiqueta(etiqueta1);
    ListaC salto_condicional = generar_salto_condicional("beqz",$4, etiqueta2);
    ListaC b = generar_b(etiqueta1);
    ListaC etiqueta_while_end = generar_etiqueta(etiqueta2);

    concatenaLC(while_loop, etiqueta_while_start);
    concatenaLC(while_loop, salto_condicional);
    concatenaLC(while_loop, $6);
    concatenaLC(while_loop, b);
    concatenaLC(while_loop, etiqueta_while_end);
    
    $$ = while_loop;

    stack_pop(etiquetas_loop);
  }
  | DO { stack_push(etiquetas_loop, nueva_etiqueta("do_while_end")); } statement WHI PAI expression PAD PYC { 
    //Creamos la etiqueta del inicio while
    char *etiqueta1 = nueva_etiqueta("do_while_start");
    char *etiqueta2 = stack_top(etiquetas_loop);

    ListaC do_while_loop = creaLC();
    ListaC etiqueta_do_while_start = generar_etiqueta(etiqueta1);
    ListaC etiqueta_do_while_end = generar_etiqueta(etiqueta2);
    ListaC salto_condicional = generar_salto_condicional("bnez", $6, etiqueta1);

    concatenaLC(do_while_loop, etiqueta_do_while_start);
    concatenaLC(do_while_loop, $3);
    concatenaLC(do_while_loop, salto_condicional);
    concatenaLC(do_while_loop, etiqueta_do_while_end);

    $$ = do_while_loop;

    stack_pop(etiquetas_loop);
  }
  | FOR { stack_push(etiquetas_loop, nueva_etiqueta("for_end")); } PAI asignation PYC expression PYC asignation PAD statement { 
    char *etiqueta1 = nueva_etiqueta("for_start");
    char *etiqueta2 = stack_top(etiquetas_loop);

    ListaC for_loop = creaLC();
    ListaC etiqueta_for_start = generar_etiqueta(etiqueta1);
    ListaC salto_condicional = generar_salto_condicional("beqz", $6, etiqueta2);
    ListaC b = generar_b(etiqueta1);
    ListaC etiqueta_for_end = generar_etiqueta(etiqueta2);

    concatenaLC(for_loop, $4);
    concatenaLC(for_loop, etiqueta_for_start);
    concatenaLC(for_loop, salto_condicional);
    concatenaLC(for_loop, $10);
    concatenaLC(for_loop, $8);
    concatenaLC(for_loop, b);
    concatenaLC(for_loop, etiqueta_for_end);
    
    $$ = for_loop;
    stack_pop(etiquetas_loop);
  } 
  | BRK PYC {
    ListaC cod_break = creaLC();
    if(!stack_empty(etiquetas_loop)){
      ListaC salto_incondicional = generar_b(stack_top(etiquetas_loop));
      concatenaLC(cod_break,salto_incondicional);
    }else print_error(BREAK_ERR);     
    
    $$ = cod_break;
  }
  | PRI PAI print_list PAD PYC  { $$ = $3; }
  | REA PAI read_list PAD PYC   { $$ = $3; }
;

asignation:
  IDE { 
    check_id($1); 
    check_const($1, not_mod_const); 
  } IGU expression { 
    Simbolo s = getSimboloStackTS(stack_ts, $1);
    $$ = generar_store($4, s); 
  }

print_list:
    print_item                  { $$ = $1; }
  | print_list COM print_item   { concatenaLC($1, $3); $$ = $1; }
;

print_item:
    expression  { $$ = generar_print_expresiones($1); }
  | CAD     { 
    char *etiqueta_asciiz = escribir_asciiz($1); 
    $$ = generar_print_asciiz(etiqueta_asciiz); 
  }
;

read_list:
    IDE                                       { 
      check_id($1);
      check_const($1, not_read_const); 
      $$ = generar_read($1); 
    }
  | read_list COM IDE                         { 
      check_id($3);
      check_const($3, not_read_const); 
      ListaC read = generar_read($3);  
      concatenaLC($1, read); 
      $$ = $1;
    }
;

arg_list:
    %empty { 
      $$.codigo_argumentos = NULL;
      $$.registros = NULL;
      $$.num = 0;
    }
  | expression {
    $$.num = 1;
    $$.codigo_argumentos = $1;

    $$.registros = (char**)malloc(sizeof(char*));
    $$.registros[0] = recuperaResLC($1);
  }
  | arg_list COM expression {
    $$.num = $1.num + 1;

    concatenaLC($1.codigo_argumentos, $3);
    $$.codigo_argumentos = $1.codigo_argumentos;

    $$.registros = (char**)realloc($1.registros, $$.num * sizeof(char*));
    $$.registros[$1.num] = recuperaResLC($3);
  }
;

expression:
  call_function                   { $$ = $1; }
  | expression NEQ expression     { $$ = generar_expresion_binaria($1, $3, "sne"); }
  | expression EQ expression      { $$ = generar_expresion_binaria($1, $3, "seq"); }
  | expression GT expression      { $$ = generar_expresion_binaria($1, $3, "sgt"); }
  | expression GTE expression     { $$ = generar_expresion_binaria($1, $3, "sge"); }
  | expression LT expression      { $$ = generar_expresion_binaria($1, $3, "slt"); }
  | expression LTE expression     { $$ = generar_expresion_binaria($1, $3, "sle"); }
  | expression MAS expression     { $$ = generar_expresion_binaria($1, $3, "add"); }
  | expression MEN expression     { $$ = generar_expresion_binaria($1, $3, "sub"); }       
  | expression POR expression     { $$ = generar_expresion_binaria($1, $3, "mul"); }    
  | expression DIV expression     { $$ = generar_expresion_binaria($1, $3, "div"); } 
  | MEN expression %prec UMINUS   { $$ = generar_expresion_unaria($2); }
  | PAI expression PAD            { $$ = $2; } 
  | NUM                           { $$ = generar_load_immediate($1); }        
  | IDE                           {
    check_id($1);
    Simbolo s = getSimboloStackTS(stack_ts, $1);
    $$ = generar_load_simbolo(s);
  }
;

call_function:
  IDE PAI arg_list PAD {
    Args args = $3;
    int num_args = args.num;
    
    check_funcion($1, num_args);

    ListaC codigo = creaLC();

    //Generamos el incio del marco de pila de la llamada
    if(num_args > 0) concatenaLC(codigo, generar_inicio_marco_pila_llamada(args));

    //Genera los argumentos del código
    ListaC args_codigo = generar_llamada_funcion($1, args);
    char *res = recuperaResLC(args_codigo);
    concatenaLC(codigo, args_codigo);
    guardaResLC(codigo, res);

    //Generamos el fin del marco de pila de la llamada
    if(num_args > 0) concatenaLC(codigo, generar_fin_marco_pila_llamada(args));

    $$ = codigo;
  }

%%

//INFORME DE ERROR SINTÁCTICO
void is_main(char * funcion){
  if(strcmp(funcion,"main") == 0) {
    is_func_main = 1;
    has_main = 1;
  }
}

void print_error(const char *msg){
  errores++;
  printf(SYNTACTIC_ERR, yylineno, msg);
}

void yyerror(const char *msg){
  errores++;
  printf(SYNTACTIC_ERR, yylineno, msg);
}