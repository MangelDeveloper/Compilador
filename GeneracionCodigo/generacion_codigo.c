#define _GNU_SOURCE
#define TEMPORAL "TEMPORAL"
#define ARGUMENTO "ARGUMENTO"
#define SYSCALL "SYSCALL"
#define NUM_REGISTROS_TEMPORALES 10
#define NUM_REGISTROS_ARGUMENTOS 4

#include "generacion_codigo.h"

int label_count = 0;
int asciiz_count = 0;
char registros_temporales[NUM_REGISTROS_TEMPORALES];
char registros_argumentos[NUM_REGISTROS_ARGUMENTOS];
FILE *fasm;

void inicializar_reg(){
  memset(registros_temporales, 0, sizeof(char)*NUM_REGISTROS_TEMPORALES);
  memset(registros_argumentos, 0, sizeof(char)*NUM_REGISTROS_ARGUMENTOS);
}

char *obtener_reg(char *tipo_registro){
  char *registro;
  if(strcmp(tipo_registro, TEMPORAL) == 0) registro = obtener_reg_temporal();
  else if (strcmp(tipo_registro, ARGUMENTO) == 0) registro = obtener_reg_argumento();

  if(registro == NULL){
      printf("Error: tipo de registro desconocido\n");
      exit(1);
  }

  return registro;
}

char *obtener_reg_temporal(){
  for(int i = 0; i < NUM_REGISTROS_TEMPORALES; i++){
    if(registros_temporales[i] == 0){
      
      char *reg;
      asprintf(&reg,"$t%d",i);
      registros_temporales[i] = 1;
      return reg;
    }
  }

  printf("Error fatal: registros temporales agotados!\n");
  exit(1);
}

char *obtener_reg_argumento(){
  for(int i = 0; i < NUM_REGISTROS_ARGUMENTOS; i++){
    if(registros_argumentos[i] == 0){
      
      char *reg;
      asprintf(&reg,"$a%d",i);
      registros_argumentos[i] = 1;
      return reg;
    }
  }

  printf("Error fatal: registros de argumentos agotados!\n");
  exit(1);
}

void liberar_reg(char* reg){
  assert(reg[0]=='$');
  if(reg[1] == 't') liberar_reg_temporal(reg);
  else if(reg[1] == 'a') liberar_reg_argumento(reg);
}

void liberar_reg_temporal(char *reg){
  int i = reg[2] - '0';
  assert(i <= NUM_REGISTROS_TEMPORALES-1);
  assert(i >= 0);
  registros_temporales[i] = 0;
}

void liberar_reg_argumento(char *reg){
  int i = reg[2] - '0';
  assert(i <= NUM_REGISTROS_ARGUMENTOS-1);
  assert(i >= 0);
  registros_argumentos[i] = 0;
}

void escribir_seccion_data(){
  fprintf(fasm, "###################\n");
  fprintf(fasm, "# Seccion de datos\n");
  fprintf(fasm,"\t.data\n");
  fprintf(fasm, "\n");
}

void escribir_seccion_text(){
  fprintf(fasm, "\n");
  fprintf(fasm, "###################\n");
  fprintf(fasm, "# Seccion de codigo\n");
  fprintf(fasm,"\t.text\n");
  fprintf(fasm,"\t.globl main\n");
}

void escribir_seccion_fin(){
  fprintf(fasm, "\n");
  fprintf(fasm, "###################\n");
  fprintf(fasm, "# Fin\n");
}

char* escribir_asciiz(char *msg){
  Simbolo s = buscaSimboloTS(ts_str, msg);
  if(s.nombre == NULL){
    char *label;
    asprintf(&label, "str%d", ++asciiz_count);
    declarar_asciiz(label, msg);
    fprintf(fasm, "%s:\n\t.asciiz %s\n", label, msg);
    return label;
  }else return s.asciiz.label;
}

void escribir_id(char *nombre, int valor){
  fprintf(fasm,"_%s:\n\t.word %d\n", nombre, valor);
}


void escribir_lc(ListaC codigo1){
  
  printf("El código contiene %d operaciones\n",longitudLC(codigo1));
  PosicionListaC p = inicioLC(codigo1);
  PosicionListaC final = finalLC(codigo1);

  while (p != final) {
    Operacion oper = recuperaLC(codigo1,p);
    fprintf(fasm, "%s", oper.op);
    if (oper.res) fprintf(fasm," %s",oper.res);
    if (oper.arg1) fprintf(fasm,",%s",oper.arg1);
    if (oper.arg2) fprintf(fasm,",%s",oper.arg2);
    fprintf(fasm,"\n");
    p = siguienteLC(codigo1, p);
  }
}


ListaC generar_load_immediate(char *expr1) {
  ListaC codigo = creaLC();

  
  Operacion operacion;
  operacion.res = obtener_reg(TEMPORAL);
  operacion.arg2 = NULL;

  
  operacion.op = "\tli";
  operacion.arg1 = expr1;

  insertaLC(codigo, finalLC(codigo), operacion);

  
  guardaResLC(codigo, operacion.res);

  return codigo;
}

ListaC generar_load_simbolo(Simbolo s) {
  if (s.tipo == VARIABLE_LOCAL || s.tipo == CONSTANTE) return generar_load_offset(s.var_const_local.offset);
  else if(s.tipo == PARAMETRO) return generar_load_parametro(s);
  else return generar_load_global(s.nombre);
}

ListaC generar_load_offset(int offset){
  ListaC codigo = creaLC();

  
  Operacion operacion;
  
  operacion.op = "\tlw";
  operacion.res = obtener_reg(TEMPORAL);
  asprintf(&operacion.arg1, "%d($sp)", offset);
  operacion.arg2 = NULL;

  insertaLC(codigo, finalLC(codigo), operacion);

  
  guardaResLC(codigo, operacion.res);

  return codigo;
}

ListaC generar_load_parametro(Simbolo s){
    ListaC codigo = creaLC();

    Operacion op;
    op.op = "\tmove";
    op.res = obtener_reg(TEMPORAL);
    op.arg1 = s.param.reg;
    op.arg2 = NULL;

    insertaLC(codigo, finalLC(codigo), op);
    guardaResLC(codigo, op.res);

    return codigo;
}

ListaC generar_load_global(char *id) {
  ListaC codigo = creaLC();

  Operacion operacion;
  operacion.op = "\tlw";
  operacion.res = obtener_reg(TEMPORAL);
  asprintf(&operacion.arg1, "_%s", id);
  operacion.arg2 = NULL;

  insertaLC(codigo, finalLC(codigo), operacion);
  guardaResLC(codigo, operacion.res);

  return codigo;
}


ListaC generar_load_asciiz(char *label){
  ListaC lista_codigo = creaLC();

  
  Operacion operacion;
  operacion.res = obtener_reg(ARGUMENTO);
  operacion.arg2 = NULL;

   
  operacion.op = "\tla";
  asprintf(&operacion.arg1, "%s", label);

  insertaLC(lista_codigo, finalLC(lista_codigo), operacion);
  liberar_reg(operacion.res);

  return lista_codigo;
}


ListaC generar_store(ListaC expr1, Simbolo s){
  
  ListaC codigo = expr1;

  
  Operacion operacion;
  operacion.op = "\tsw";
  operacion.res = recuperaResLC(codigo);

  if (s.tipo == VARIABLE_LOCAL || s.tipo == CONSTANTE) asprintf(&operacion.arg1, "%d($sp)", s.var_const_local.offset);
  else if(s.tipo == VARIABLE_GLOBAL) asprintf(&operacion.arg1, "_%s", s.nombre);

  operacion.arg2 = NULL;

  
  insertaLC(codigo, finalLC(codigo), operacion);
  
  liberar_reg(operacion.res);
  
  return codigo;
}


ListaC generar_expresion_unaria(ListaC expr) {
  ListaC codigo = expr;

  Operacion operacion;
  operacion.op = "\tsub";
  operacion.res = obtener_reg(TEMPORAL);
  operacion.arg1 = "$zero";
  operacion.arg2 = recuperaResLC(expr);

  insertaLC(codigo, finalLC(codigo), operacion);
  liberar_reg(operacion.arg2);
  guardaResLC(codigo, operacion.res);

  return codigo;
}


ListaC generar_expresion_binaria(ListaC expr1, ListaC expr2, char *op){
  ListaC codigo = expr1;
  concatenaLC(codigo, expr2);
  
  Operacion operacion;
  asprintf(&operacion.op, "\t%s", op);
  
  operacion.res = operacion.arg1 = recuperaResLC(expr1);
  operacion.arg2 = recuperaResLC(expr2);
  insertaLC(codigo,finalLC(codigo),operacion);

  
  liberar_reg(operacion.arg2);
  liberaLC(expr2);

  return codigo;
}


char* nueva_etiqueta(char *nombre_etiqueta){
  char* etiqueta;
  asprintf(&etiqueta, "%s_%d", nombre_etiqueta, label_count++);
  return etiqueta;
}


ListaC generar_salto_condicional(char *op, ListaC expr1, char* etq){
  ListaC codigo = expr1;

  
  Operacion operacion;
  asprintf(&operacion.op, "\t%s", op);
  operacion.res = recuperaResLC(expr1);
  operacion.arg1 = etq;
  operacion.arg2 = NULL;
  
  
  insertaLC(codigo, finalLC(codigo), operacion);
  
  liberar_reg(recuperaResLC(codigo));

  return codigo;
}


ListaC generar_etiqueta(char *etq){
  ListaC codigo = creaLC();

  Operacion operacion;
  asprintf(&operacion.op,"%s:",etq);
  operacion.res = NULL;
  operacion.arg1 = NULL;
  operacion.arg2 = NULL;

  insertaLC(codigo, finalLC(codigo), operacion);

  return codigo;
}


ListaC generar_b(char *etiqueta){
  ListaC codigo = creaLC();

  Operacion operacion;
  operacion.op = "\tb";
  operacion.res = etiqueta;
  operacion.arg1 = NULL;
  operacion.arg2 = NULL;

  insertaLC(codigo, finalLC(codigo), operacion);

  return codigo;
};




ListaC generar_print_asciiz(char *etiqueta){
  
  ListaC lista_codigo = creaLC();
  
  Operacion li_v0, syscall, la_asciiz, move_s0, move_s1, move_a0, move_v0;

  
  
  move_s0.op = "\tmove";
  move_s0.res = "$s0";
  move_s0.arg1 = "$a0";
  move_s0.arg2 = NULL;
  insertaLC(lista_codigo, finalLC(lista_codigo), move_s0);

  move_s1.op = "\tmove";
  move_s1.res = "$s1";
  move_s1.arg1 = "$v0";
  move_s1.arg2 = NULL;
  insertaLC(lista_codigo, finalLC(lista_codigo), move_s1);

  
  
  li_v0.op = "\tli";
  li_v0.res = "$v0";
  li_v0.arg1 = "4";
  li_v0.arg2 = NULL;
  insertaLC(lista_codigo, finalLC(lista_codigo), li_v0);

  
  la_asciiz.op = "\tla";
  la_asciiz.res = "$a0";
  asprintf(&la_asciiz.arg1, "%s", etiqueta);
  la_asciiz.arg2 = NULL;
  insertaLC(lista_codigo, finalLC(lista_codigo), la_asciiz);

  syscall.op = "\tsyscall";
  syscall.res = NULL;
  syscall.arg1 = NULL;
  syscall.arg2 = NULL;
  insertaLC(lista_codigo, finalLC(lista_codigo), syscall);
  
  move_a0.op = "\tmove";
  move_a0.res = "$a0";
  move_a0.arg1 = "$s0";
  move_a0.arg2 = NULL;
  insertaLC(lista_codigo, finalLC(lista_codigo), move_a0);

  move_v0.op = "\tmove";
  move_v0.res = "$v0";
  move_v0.arg1 = "$s1";
  move_v0.arg2 = NULL;
  insertaLC(lista_codigo, finalLC(lista_codigo), move_v0);

  
  liberar_reg(li_v0.res);
  liberar_reg(la_asciiz.res);

  return lista_codigo;
}


ListaC generar_print_expresiones(ListaC lista_codigo){
  
  Operacion move_expr, li_v0, syscall;
  
  char *reg_res = recuperaResLC(lista_codigo);

  li_v0.op = "\tli";
  li_v0.res = "$v0";
  li_v0.arg1 = "1";
  li_v0.arg2 = NULL;
  insertaLC(lista_codigo, finalLC(lista_codigo), li_v0);

  move_expr.op = "\tmove";
  move_expr.res = "$a0";
  move_expr.arg1 = reg_res;
  move_expr.arg2 = NULL;
  insertaLC(lista_codigo, finalLC(lista_codigo), move_expr);

  syscall.op = "\tsyscall";
  syscall.res = NULL;
  syscall.arg1 = NULL;
  syscall.arg2 = NULL;
  insertaLC(lista_codigo, finalLC(lista_codigo), syscall);

  
  liberar_reg(move_expr.res);
  liberar_reg(move_expr.arg1);
  liberar_reg(li_v0.res);

  return lista_codigo;
}

ListaC generar_read(char *ide){
  ListaC lista_codigo = creaLC();
  Simbolo s = getSimboloStackTS(stack_ts, ide);
  
  Operacion li_v0, syscall, sw_res, move_s0, move_s1, move_a0, move_v0;

  move_s0.op = "\tmove";
  move_s0.res = "$s0";
  move_s0.arg1 = "$a0";
  move_s0.arg2 = NULL;
  insertaLC(lista_codigo, finalLC(lista_codigo), move_s0);

  move_s1.op = "\tmove";
  move_s1.res = "$s1";
  move_s1.arg1 = "$v0";
  move_s1.arg2 = NULL;
  insertaLC(lista_codigo, finalLC(lista_codigo), move_s1);

  li_v0.op = "\tli";
  li_v0.res = "$v0";
  li_v0.arg1 = "5";
  li_v0.arg2 = NULL;
  insertaLC(lista_codigo, finalLC(lista_codigo), li_v0);

  syscall.op = "\tsyscall";
  syscall.res = NULL;
  syscall.arg1 = NULL;
  syscall.arg2 = NULL;
  insertaLC(lista_codigo, finalLC(lista_codigo), syscall);

  sw_res.op = "\tsw";
  sw_res.res = li_v0.res;
  asprintf(&sw_res.arg1, "%d($sp)", s.var_const_local.offset);
  sw_res.arg2 = NULL;
  insertaLC(lista_codigo, finalLC(lista_codigo), sw_res);

  move_a0.op = "\tmove";
  move_a0.res = "$a0";
  move_a0.arg1 = "$s0";
  move_a0.arg2 = NULL;
  insertaLC(lista_codigo, finalLC(lista_codigo), move_a0);

  move_v0.op = "\tmove";
  move_v0.res = "$v0";
  move_v0.arg1 = "$s1";
  move_v0.arg2 = NULL;
  insertaLC(lista_codigo, finalLC(lista_codigo), move_v0);

  liberar_reg(li_v0.res);

  return lista_codigo;
}

ListaC generar_exit(){
  ListaC lista_codigo = creaLC();

  
  Operacion operacion1, operacion2;

  
  operacion1.op = "\tli";
  operacion2.op = "\tsyscall";

  
  operacion1.res = "$v0";
  operacion2.res = NULL;

  
  operacion1.arg1 = "10";
  operacion2.arg1 = NULL;

  
  operacion1.arg2 = NULL;
  operacion2.arg2 = NULL;

  
  insertaLC(lista_codigo, finalLC(lista_codigo), operacion1);
  insertaLC(lista_codigo, finalLC(lista_codigo), operacion2);

  
  liberar_reg(operacion1.res);

  return lista_codigo;
}

ListaC generar_inicio_marco_pila_llamada(Args args){
  ListaC codigo = args.codigo_argumentos;
  int num_args = args.num;
  int size = num_args*4;

  Operacion addiu;
  addiu.op = "\taddiu";
  addiu.res = "$sp";
  addiu.arg1 = "$sp";
  asprintf(&addiu.arg2, "-%d", size);
  insertaLC(codigo, finalLC(codigo), addiu);

  for (int i = 0; i < num_args; i++) {
    Operacion sw_args;
    sw_args.op = "\tsw";
    asprintf(&sw_args.res, "$a%d", i);
    asprintf(&sw_args.arg1, "%d($sp)", i*4);
    sw_args.arg2 = NULL;
    insertaLC(codigo, finalLC(codigo), sw_args);
  }

  for(int i = 0; i < num_args; i++){
    Operacion move;
    move.op = "\tmove";
    asprintf(&move.res, "$a%d", i); 
    move.arg1 = args.registros[i];
    move.arg2 = NULL;
    insertaLC(codigo, finalLC(codigo), move);
  }
  
  return codigo;
}

ListaC generar_llamada_funcion(char *func_name, Args args) {
  TablaHash bottom_stack_ts = bottomStackTS(stack_ts);
  Simbolo funcion = buscaSimboloTS(bottom_stack_ts, func_name);

  ListaC cod = creaLC();

  
  Operacion jal;
  jal.op = "\tjal";
  jal.res = func_name;
  jal.arg1 = NULL;
  jal.arg2 = NULL;
  insertaLC(cod, finalLC(cod), jal);
  
  if(funcion.func.ret == TIPO_INT){
    Operacion move_resultado;
    move_resultado.op = "\tmove";
    move_resultado.res = obtener_reg(TEMPORAL);
    move_resultado.arg1 = "$v0";
    move_resultado.arg2 = NULL;
    insertaLC(cod, finalLC(cod), move_resultado);

    guardaResLC(cod, move_resultado.res);

  }

  
  if (args.registros != NULL) free(args.registros);
  
  return cod;
}

ListaC generar_fin_marco_pila_llamada(Args args){
  ListaC codigo = creaLC();
  int num_args = args.num;
  int size = num_args*4;

  for (int i = 0; i < num_args; i++) {
    Operacion lw_arg;
    lw_arg.op = "\tlw";
    asprintf(&lw_arg.res, "$a%d", i);
    asprintf(&lw_arg.arg1, "%d($sp)", i*4);
    lw_arg.arg2 = NULL;
    insertaLC(codigo, finalLC(codigo), lw_arg);
  }

  Operacion addiu;
  addiu.op = "\taddiu";
  addiu.res = "$sp";
  addiu.arg1 = "$sp";
  asprintf(&addiu.arg2, "%d", size);
  insertaLC(codigo, finalLC(codigo), addiu);

  return codigo;
}


ListaC generar_inicio_marco_pila(int is_func_main) {
  ListaC c = creaLC();
  TablaHash ts = topStackTS(stack_ts);

  
  
  int size = 4 + 10 * 4;

  Operacion addiu;
  addiu.op = "\taddiu";
  addiu.res = "$sp";
  addiu.arg1 = "$sp";
  asprintf(&addiu.arg2, "-%d", size);
  insertaLC(c, finalLC(c), addiu);

  if(is_func_main == 0){
    Operacion sw_ra;
    sw_ra.op = "\tsw";
    sw_ra.res = "$ra";
    sw_ra.arg1 = "0($sp)";
    sw_ra.arg2 = NULL;
    insertaLC(c, finalLC(c), sw_ra);

    
    for(int i = 0 ; i < 10; i++){
      int offset = 4+i*4;

      Operacion sw_locales;
      sw_locales.op = "\tsw";
      asprintf(&sw_locales.res, "$t%d", i);
      asprintf(&sw_locales.arg1, "%d($sp)", offset);
      sw_locales.arg2 = NULL;
      insertaLC(c, finalLC(c), sw_locales);
    }
    
    Operacion move;
    move.op = "\tmove";
    move.res = "$v0";
    move.arg1 = "$zero";
    move.arg2 = NULL;
    insertaLC(c, finalLC(c), move);
  }

  return c;
}

ListaC generar_fin_marco_pila(int is_func_main, char *label) {
  ListaC c = creaLC();
  TablaHash ts = topStackTS(stack_ts);

  
  
  int size = 4 + 10 * 4;

  if(is_func_main == 0){
    
    for(int i = 9; i >= 0; i--){
      int offset = 4+i*4;
      
      Operacion lw_locales;
      lw_locales.op = "\tlw";
      asprintf(&lw_locales.res, "$t%d", i);
      asprintf(&lw_locales.arg1, "%d($sp)", offset);
      lw_locales.arg2 = NULL;
      insertaLC(c, finalLC(c), lw_locales);
    }

    Operacion lw_ra;
    lw_ra.op = "\tlw";
    lw_ra.res = "$ra";
    lw_ra.arg1 = "0($sp)";
    lw_ra.arg2 = NULL;
    insertaLC(c, finalLC(c), lw_ra);
  }

  Operacion addiu;
  addiu.op = "\taddiu";
  addiu.res = "$sp";
  addiu.arg1 = "$sp";
  asprintf(&addiu.arg2, "%d", size);
  insertaLC(c, finalLC(c), addiu);

  if(is_func_main == 0){
    Operacion jr;
    jr.op = "\tjr";
    jr.res = "$ra";
    jr.arg1 = jr.arg2 = NULL;

    insertaLC(c, finalLC(c), jr);
  }

  return c;
}

ListaC generar_inicio_llaves(int num_vars){
  ListaC c = creaLC();
  int size = num_vars * 4;

  Operacion addiu;
  addiu.op = "\taddiu";
  addiu.res = "$sp";
  addiu.arg1 = "$sp";
  asprintf(&addiu.arg2, "-%d", size);
  insertaLC(c, finalLC(c), addiu);
}

ListaC generar_fin_llaves(int num_vars){
  ListaC c = creaLC();
  int size = num_vars * 4;

  Operacion addiu;
  addiu.op = "\taddiu";
  addiu.res = "$sp";
  addiu.arg1 = "$sp";
  asprintf(&addiu.arg2, "%d", size);
  insertaLC(c, finalLC(c), addiu);
}


ListaC generar_return(char *label) {
  ListaC lista_codigo = creaLC();

  ListaC b_fin_funcion = generar_b(label);

  concatenaLC(lista_codigo, b_fin_funcion);

  return lista_codigo;
}


ListaC generar_return_con_valor(ListaC expr, char *label) {
  ListaC codigo = expr;

  
  Operacion operacion1;
  operacion1.op = "\tmove";
  operacion1.res = "$v0";
  operacion1.arg1 = recuperaResLC(expr);
  operacion1.arg2 = NULL;

  insertaLC(codigo, finalLC(codigo), operacion1);

  
  liberar_reg(operacion1.arg1);

  ListaC b_fin_funcion = generar_b(label);

  concatenaLC(codigo, b_fin_funcion);

  return codigo;
}