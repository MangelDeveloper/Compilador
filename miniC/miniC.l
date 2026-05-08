/* Sección de definiciones */
%{
	/* Código literal que se coloca en lex.yy.cc al comienzo */
	#include <stdio.h>
    #include <stdlib.h>
	#include "miniC.tab.h"
	#include <errno.h>
	#include <limits.h>
	
	/* Flex genera un archivo llamado lex.yy.c donde mete el método yylex();
	importante no crear métodos que puedan colisionar */
	int errores = 0;
	int inicio_comentario = 0;
	int inicio_string = 0;
	/* Solo se podrá asignar valores entre 0 y 2³¹-1 = 2147483647 */
    #define MAX_INT 2147483647
%}

LETTER              [a-zA-Z_]
DIGIT               [0-9]
SPACE               [ \n\t\r]+
NAME_VAR            {LETTER}({LETTER}|{DIGIT})*
SINGLE_COMMENT      "//".*
NUMBER              {DIGIT}+
ERR_LEX             [^a-zA-Z_0-9(){};," \n\t\r+\-*/=<>]+

%option yylineno

/* Condición de contexto */
%x comentario 
%x string

%%

 /* Sección de reglas */
{SINGLE_COMMENT}            { }
{SPACE}                     { }
"/*"						{
	inicio_comentario = yylineno;
	BEGIN(comentario);
}
<comentario>"*/"			{BEGIN(INITIAL);}
<comentario>.|\n 			{ }
<comentario><<EOF>> 		{
	errores++;
	printf("Error léxico en línea %d: comentario sin cerrar\n", inicio_comentario);
	//Ponemos return 0 porque en el while del main la condición es != 0 y debe parar en algún momento
	return 0;
}
\"							{
	inicio_string = yylineno;
	BEGIN(string); 
	yymore();
}
<string>\"					{
	BEGIN(INITIAL);
	yylval.cadena = strdup(yytext);
	return CAD;
}
<string>.|\\\"			    { yymore(); }
<string><<EOF>> 		    {
	errores++;
	printf("Error léxico en línea %d: cadena sin cerrar\n", inicio_string);
	//Ponemos return 0 porque en el while del main la condición es != 0 y debe parar en algún momento
	return 0;
}


 /* Cuando cumple una expresión regular devuelve el método - realmente Flex crea un autómata finito determinista sobre estas expresiones regulares */
"void"						{return VOI;}
"var"						{return VAR;}
"const"						{return CON;}
"int"						{return INT;}
"if"						{return IF;}
"else"						{return ELS;}
"do"						{return DO;}
"while"						{return WHI;}
"break"						{return BRK;}
"for"						{return FOR;}
"print"                     {return PRI;}
"read"						{return REA;}
"return"					{return RET;}
{NAME_VAR}                  {
    if(yyleng > 32){
        printf("Error léxico en línea %d: La variable %s no puede exceder los 32 caracteres\n",yylineno,yytext);
        errores++;
    }

	yylval.cadena = strdup(yytext);

    return IDE;
}
"="                         {return IGU;}
";"                         {return PYC;}
"+"                         {return MAS;}
"-"                         {return MEN;}
"*"                         {return POR;}
"/"                         {return DIV;}
"("                         {return PAI;}
")"                         {return PAD;}
"{"							{return LLI;}
"}"							{return LLD;}
","							{return COM;}
"=="						{return EQ;}
"!="						{return NEQ;}
"<"							{return LT;}
"<="						{return LTE;}
">"							{return GT;}
">="						{return GTE;}
{NUMBER}                    {
	errno = 0;
    long valor = strtol(yytext, NULL, 10);
	
    if(errno == ERANGE || valor > INT_MAX){
        errores++;
		printf("Error léxico en línea %d: el número '%s' supera el valor máximo permitido\n", yylineno, yytext);
	}

	yylval.cadena = strdup(yytext);

    return NUM;
}
 /*El propósito de ERR_LEX es mero aprendizaje, realmente se podría resumir en poner . al final del todo que indicaría que cualquier caracter o cadena que no cumpla cierta expresión regular pasaría por ese . como error léxico*/
{ERR_LEX}                   {
	errores++;
	printf("Error léxico en línea %d: símbolo no reconocido '%s'\n", yylineno, yytext);
}

%%