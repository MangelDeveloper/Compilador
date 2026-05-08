#include <stdio.h>
#include <stdlib.h>

extern int errores;
extern char *yytext;
extern FILE *yyin;
extern int yylex();
extern int yyparse();


/* Sección de código de usuario */
int main(int argc, char *argv[]){

    if(argc != 2){
        printf("Número incorrecto de argumentos...");
        exit(1);
    }

    yyin = fopen(argv[1],"r");
    if(yyin == NULL){
        printf("No se ha podido encontrar el archivo");
        exit(2);
    }
    
    yyparse();
    fclose(yyin);
    
    printf("Número de errores: %d\n",errores);
}