/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_MINIC_MINIC_TAB_H_INCLUDED
# define YY_YY_MINIC_MINIC_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 51 "./miniC/miniC.y"

  #include "../GeneracionCodigo/listaCodigo.h"
  #include "funciones.h"

#line 54 "./miniC/miniC.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDE = 258,                     /* IDE  */
    CAD = 259,                     /* CAD  */
    NUM = 260,                     /* NUM  */
    VOI = 261,                     /* VOI  */
    VAR = 262,                     /* VAR  */
    CON = 263,                     /* CON  */
    INT = 264,                     /* INT  */
    IF = 265,                      /* IF  */
    ELS = 266,                     /* ELS  */
    WHI = 267,                     /* WHI  */
    PRI = 268,                     /* PRI  */
    REA = 269,                     /* REA  */
    DO = 270,                      /* DO  */
    FOR = 271,                     /* FOR  */
    BRK = 272,                     /* BRK  */
    RET = 273,                     /* RET  */
    MAS = 274,                     /* "+"  */
    MEN = 275,                     /* "-"  */
    POR = 276,                     /* "*"  */
    DIV = 277,                     /* "/"  */
    IGU = 278,                     /* "="  */
    PYC = 279,                     /* ";"  */
    PAI = 280,                     /* "("  */
    PAD = 281,                     /* ")"  */
    LLI = 282,                     /* "{"  */
    LLD = 283,                     /* "}"  */
    COM = 284,                     /* ","  */
    EQ = 285,                      /* "=="  */
    NEQ = 286,                     /* "!="  */
    GT = 287,                      /* ">"  */
    GTE = 288,                     /* ">="  */
    LT = 289,                      /* "<"  */
    LTE = 290,                     /* "<="  */
    UMINUS = 291,                  /* UMINUS  */
    NOELSE = 292                   /* NOELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 56 "./miniC/miniC.y"

    char* cadena;
    //Lista de código 
    ListaC codigo;
    //Para saber el tipo de retorno de una función
    TipoRetorno tipo_retorno;
    //Número de parámetros para param_list
    Params params;
    //Número de argumentos y su código generado de arg_list
    Args args;

#line 120 "./miniC/miniC.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_MINIC_MINIC_TAB_H_INCLUDED  */
