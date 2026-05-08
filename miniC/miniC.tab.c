/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "./miniC/miniC.y"

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

#line 119 "./miniC/miniC.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "miniC.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDE = 3,                        /* IDE  */
  YYSYMBOL_CAD = 4,                        /* CAD  */
  YYSYMBOL_NUM = 5,                        /* NUM  */
  YYSYMBOL_VOI = 6,                        /* VOI  */
  YYSYMBOL_VAR = 7,                        /* VAR  */
  YYSYMBOL_CON = 8,                        /* CON  */
  YYSYMBOL_INT = 9,                        /* INT  */
  YYSYMBOL_IF = 10,                        /* IF  */
  YYSYMBOL_ELS = 11,                       /* ELS  */
  YYSYMBOL_WHI = 12,                       /* WHI  */
  YYSYMBOL_PRI = 13,                       /* PRI  */
  YYSYMBOL_REA = 14,                       /* REA  */
  YYSYMBOL_DO = 15,                        /* DO  */
  YYSYMBOL_FOR = 16,                       /* FOR  */
  YYSYMBOL_BRK = 17,                       /* BRK  */
  YYSYMBOL_RET = 18,                       /* RET  */
  YYSYMBOL_MAS = 19,                       /* "+"  */
  YYSYMBOL_MEN = 20,                       /* "-"  */
  YYSYMBOL_POR = 21,                       /* "*"  */
  YYSYMBOL_DIV = 22,                       /* "/"  */
  YYSYMBOL_IGU = 23,                       /* "="  */
  YYSYMBOL_PYC = 24,                       /* ";"  */
  YYSYMBOL_PAI = 25,                       /* "("  */
  YYSYMBOL_PAD = 26,                       /* ")"  */
  YYSYMBOL_LLI = 27,                       /* "{"  */
  YYSYMBOL_LLD = 28,                       /* "}"  */
  YYSYMBOL_COM = 29,                       /* ","  */
  YYSYMBOL_EQ = 30,                        /* "=="  */
  YYSYMBOL_NEQ = 31,                       /* "!="  */
  YYSYMBOL_GT = 32,                        /* ">"  */
  YYSYMBOL_GTE = 33,                       /* ">="  */
  YYSYMBOL_LT = 34,                        /* "<"  */
  YYSYMBOL_LTE = 35,                       /* "<="  */
  YYSYMBOL_UMINUS = 36,                    /* UMINUS  */
  YYSYMBOL_NOELSE = 37,                    /* NOELSE  */
  YYSYMBOL_YYACCEPT = 38,                  /* $accept  */
  YYSYMBOL_program = 39,                   /* program  */
  YYSYMBOL_40_1 = 40,                      /* $@1  */
  YYSYMBOL_global_declarations = 41,       /* global_declarations  */
  YYSYMBOL_global_declaration = 42,        /* global_declaration  */
  YYSYMBOL_global_id_list = 43,            /* global_id_list  */
  YYSYMBOL_global_id_decl = 44,            /* global_id_decl  */
  YYSYMBOL_function_list = 45,             /* function_list  */
  YYSYMBOL_function = 46,                  /* function  */
  YYSYMBOL_47_2 = 47,                      /* $@2  */
  YYSYMBOL_48_3 = 48,                      /* $@3  */
  YYSYMBOL_param_list = 49,                /* param_list  */
  YYSYMBOL_param_decl = 50,                /* param_decl  */
  YYSYMBOL_return_function = 51,           /* return_function  */
  YYSYMBOL_block = 52,                     /* block  */
  YYSYMBOL_53_4 = 53,                      /* $@4  */
  YYSYMBOL_body = 54,                      /* body  */
  YYSYMBOL_declaration = 55,               /* declaration  */
  YYSYMBOL_56_5 = 56,                      /* $@5  */
  YYSYMBOL_57_6 = 57,                      /* $@6  */
  YYSYMBOL_tipo = 58,                      /* tipo  */
  YYSYMBOL_id_list = 59,                   /* id_list  */
  YYSYMBOL_id_decl = 60,                   /* id_decl  */
  YYSYMBOL_statement = 61,                 /* statement  */
  YYSYMBOL_62_7 = 62,                      /* $@7  */
  YYSYMBOL_63_8 = 63,                      /* $@8  */
  YYSYMBOL_64_9 = 64,                      /* $@9  */
  YYSYMBOL_asignation = 65,                /* asignation  */
  YYSYMBOL_66_10 = 66,                     /* $@10  */
  YYSYMBOL_print_list = 67,                /* print_list  */
  YYSYMBOL_print_item = 68,                /* print_item  */
  YYSYMBOL_read_list = 69,                 /* read_list  */
  YYSYMBOL_arg_list = 70,                  /* arg_list  */
  YYSYMBOL_expression = 71,                /* expression  */
  YYSYMBOL_call_function = 72              /* call_function  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   233

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  78
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  156

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   292


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    90,    90,    90,   136,   137,   141,   145,   146,   150,
     151,   155,   156,   160,   168,   160,   219,   223,   224,   232,
     241,   242,   245,   245,   272,   273,   274,   278,   278,   279,
     279,   283,   287,   288,   292,   293,   301,   302,   303,   309,
     315,   316,   329,   348,   348,   369,   369,   388,   388,   409,
     418,   419,   423,   423,   432,   433,   437,   438,   445,   450,
     460,   465,   472,   484,   485,   486,   487,   488,   489,   490,
     491,   492,   493,   494,   495,   496,   497,   498,   506
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  static const char *const yy_sname[] =
  {
  "end of file", "error", "invalid token", "IDE", "CAD", "NUM", "VOI",
  "VAR", "CON", "INT", "IF", "ELS", "WHI", "PRI", "REA", "DO", "FOR",
  "BRK", "RET", "+", "-", "*", "/", "=", ";", "(", ")", "{", "}", ",",
  "==", "!=", ">", ">=", "<", "<=", "UMINUS", "NOELSE", "$accept",
  "program", "$@1", "global_declarations", "global_declaration",
  "global_id_list", "global_id_decl", "function_list", "function", "$@2",
  "$@3", "param_list", "param_decl", "return_function", "block", "$@4",
  "body", "declaration", "$@5", "$@6", "tipo", "id_list", "id_decl",
  "statement", "$@7", "$@8", "$@9", "asignation", "$@10", "print_list",
  "print_item", "read_list", "arg_list", "expression", "call_function", YY_NULLPTR
  };
  return yy_sname[yysymbol];
}
#endif

#define YYPACT_NINF (-88)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -88,     6,   -88,   -88,    53,   -88,    13,   -88,   -88,    77,
     -88,    32,   -88,    58,   -88,    41,    44,     7,   -88,   -88,
      76,   -88,    58,    78,   -88,   -88,    89,   -19,   -88,   -88,
     -88,    78,    74,   -88,   -88,   -88,   -88,    62,    79,   -88,
     -88,    80,   -88,    81,    82,   -88,   -88,    91,     0,   -88,
     -88,   -88,   -88,    92,    94,    24,    96,    13,    13,    24,
      88,    38,    99,     1,   105,   -88,    79,   -88,    24,   -88,
      24,    90,   -88,   -88,   -88,    42,   181,    24,   100,   100,
     107,    24,   -88,    59,   -88,   181,   -88,    67,   119,   129,
     -88,   124,    24,    24,    24,    24,   -88,    24,    24,    24,
      24,    24,    24,   -88,    24,   181,   111,     8,   -88,     9,
       1,   141,   112,    38,   123,   132,   126,   -88,   125,   -88,
      18,    18,   -88,   -88,   198,   198,   198,   198,   198,   198,
     181,    24,   -88,   100,   -88,   137,     1,   -88,   -88,   -88,
     -88,    24,    24,   181,   -88,     1,   -88,   158,   175,   -88,
     128,   129,   -88,   127,     1,   -88
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     4,     1,     0,    21,     0,    20,     5,     3,
      11,     0,    31,     0,    12,     0,     9,     0,     7,    13,
       0,     6,     0,    16,    10,     8,     0,     0,    17,    19,
      14,     0,     0,    18,    22,    15,    26,     0,    52,    27,
      29,     0,    43,     0,     0,    45,    47,     0,     0,    23,
      40,    24,    25,     0,     0,    60,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    49,    77,    76,     0,    39,
       0,     0,    63,    36,    37,     0,    61,     0,     0,     0,
       0,     0,    57,     0,    54,    56,    58,     0,     0,     0,
      74,     0,     0,     0,     0,     0,    38,     0,     0,     0,
       0,     0,     0,    78,     0,    53,    34,     0,    32,     0,
       0,     0,     0,     0,     0,     0,     0,    52,     0,    75,
      70,    71,    72,    73,    65,    64,    66,    67,    68,    69,
      62,     0,    28,     0,    30,    41,     0,    50,    55,    51,
      59,     0,     0,    35,    33,     0,    44,     0,     0,    42,
       0,     0,    46,     0,     0,    48
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -88,   -88,   -88,   -88,   -88,   -88,   142,   -88,   156,   -88,
     -88,   -88,   135,   -88,   136,   -88,   -88,   -88,   -88,   -88,
      40,   102,    36,   -54,   -88,   -88,   -88,   -87,   -88,   -88,
      57,   -88,   -88,   -47,   -37
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,     4,     8,    17,    18,     9,    10,    23,
      32,    27,    28,    11,    50,    36,    37,    51,    57,    58,
      13,   107,   108,    52,    60,    63,    64,    53,    56,    83,
      84,    87,    75,    85,    72
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      54,    71,   118,    66,    38,    67,     3,    30,    76,    88,
      31,    41,    80,    42,    43,    44,    45,    46,    47,    48,
      68,    90,    12,    91,    69,    70,    54,    66,    34,    67,
     105,    21,   132,   134,   111,    15,    22,   133,   133,    94,
      95,    66,    82,    67,    68,   120,   121,   122,   123,    70,
     124,   125,   126,   127,   128,   129,   135,   130,    68,     5,
       6,    16,     7,    70,   153,    38,    19,    20,   103,    39,
      40,   104,    41,    54,    42,    43,    44,    45,    46,    47,
      48,    24,   146,     5,   143,   112,     7,    26,   113,    34,
      49,   149,    29,   114,   147,   148,   115,    78,    79,    54,
     155,    34,    86,   106,    55,    59,    61,    62,    54,    92,
      93,    94,    95,    81,    96,    65,    73,    54,    74,    77,
      97,    98,    99,   100,   101,   102,    92,    93,    94,    95,
      89,   116,   117,   110,   131,   140,   137,    97,    98,    99,
     100,   101,   102,    92,    93,    94,    95,   139,   145,   142,
     119,   141,   152,   154,    97,    98,    99,   100,   101,   102,
      92,    93,    94,    95,    25,    14,    33,   136,    35,   144,
     138,    97,    98,    99,   100,   101,   102,    92,    93,    94,
      95,   109,     0,     0,   150,     0,     0,     0,    97,    98,
      99,   100,   101,   102,    92,    93,    94,    95,     0,   151,
      92,    93,    94,    95,     0,    97,    98,    99,   100,   101,
     102,    97,    98,    99,   100,   101,   102,    92,    93,    94,
      95,     0,     0,     0,     0,     0,     0,     0,    -1,    -1,
      -1,    -1,    -1,    -1
};

static const yytype_int16 yycheck[] =
{
      37,    48,    89,     3,     3,     5,     0,    26,    55,    63,
      29,    10,    59,    12,    13,    14,    15,    16,    17,    18,
      20,    68,     9,    70,    24,    25,    63,     3,    27,     5,
      77,    24,    24,    24,    81,     3,    29,    29,    29,    21,
      22,     3,     4,     5,    20,    92,    93,    94,    95,    25,
      97,    98,    99,   100,   101,   102,   110,   104,    20,     6,
       7,     3,     9,    25,   151,     3,    25,    23,    26,     7,
       8,    29,    10,   110,    12,    13,    14,    15,    16,    17,
      18,     5,   136,     6,   131,    26,     9,     9,    29,    27,
      28,   145,     3,    26,   141,   142,    29,    57,    58,   136,
     154,    27,     3,     3,    25,    25,    25,    25,   145,    19,
      20,    21,    22,    25,    24,    24,    24,   154,    24,    23,
      30,    31,    32,    33,    34,    35,    19,    20,    21,    22,
      25,    12,     3,    26,    23,     3,    24,    30,    31,    32,
      33,    34,    35,    19,    20,    21,    22,    24,    11,    24,
      26,    25,    24,    26,    30,    31,    32,    33,    34,    35,
      19,    20,    21,    22,    22,     9,    31,    26,    32,   133,
     113,    30,    31,    32,    33,    34,    35,    19,    20,    21,
      22,    79,    -1,    -1,    26,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    19,    20,    21,    22,    -1,    24,
      19,    20,    21,    22,    -1,    30,    31,    32,    33,    34,
      35,    30,    31,    32,    33,    34,    35,    19,    20,    21,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    39,    40,     0,    41,     6,     7,     9,    42,    45,
      46,    51,     9,    58,    46,     3,     3,    43,    44,    25,
      23,    24,    29,    47,     5,    44,     9,    49,    50,     3,
      26,    29,    48,    50,    27,    52,    53,    54,     3,     7,
       8,    10,    12,    13,    14,    15,    16,    17,    18,    28,
      52,    55,    61,    65,    72,    25,    66,    56,    57,    25,
      62,    25,    25,    63,    64,    24,     3,     5,    20,    24,
      25,    71,    72,    24,    24,    70,    71,    23,    58,    58,
      71,    25,     4,    67,    68,    71,     3,    69,    61,    25,
      71,    71,    19,    20,    21,    22,    24,    30,    31,    32,
      33,    34,    35,    26,    29,    71,     3,    59,    60,    59,
      26,    71,    26,    29,    26,    29,    12,     3,    65,    26,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    23,    24,    29,    24,    61,    26,    24,    68,    24,
       3,    25,    24,    71,    60,    11,    61,    71,    71,    61,
      26,    24,    24,    65,    26,    61
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    38,    40,    39,    41,    41,    42,    43,    43,    44,
      44,    45,    45,    47,    48,    46,    49,    49,    49,    50,
      51,    51,    53,    52,    54,    54,    54,    56,    55,    57,
      55,    58,    59,    59,    60,    60,    61,    61,    61,    61,
      61,    61,    61,    62,    61,    63,    61,    64,    61,    61,
      61,    61,    66,    65,    67,    67,    68,    68,    69,    69,
      70,    70,    70,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    72
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     3,     0,     2,     4,     1,     3,     1,
       3,     1,     2,     0,     0,     8,     0,     1,     3,     2,
       1,     1,     0,     4,     2,     2,     0,     0,     5,     0,
       5,     1,     1,     3,     1,     3,     2,     2,     3,     2,
       1,     5,     7,     0,     6,     0,     8,     0,    10,     2,
       5,     5,     0,     4,     1,     3,     1,     1,     1,     3,
       0,     1,     3,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     3,     1,     1,     4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif



static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yystrlen (yysymbol_name (yyarg[yyi]));
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp = yystpcpy (yyp, yysymbol_name (yyarg[yyi++]));
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* $@1: %empty  */
#line 90 "./miniC/miniC.y"
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
  }
#line 1531 "./miniC/miniC.tab.c"
    break;

  case 3: /* program: $@1 global_declarations function_list  */
#line 109 "./miniC/miniC.y"
                                      {
    //Comprobamos si sigue existiendo el main
    if (has_main == 0) print_error(MAIN_ERR);
    
    ListaC listaCodigo = (yyvsp[0].codigo);

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
#line 1560 "./miniC/miniC.tab.c"
    break;

  case 9: /* global_id_decl: IDE  */
#line 150 "./miniC/miniC.y"
                        { declarar_id_global((yyvsp[0].cadena), "0"); }
#line 1566 "./miniC/miniC.tab.c"
    break;

  case 10: /* global_id_decl: IDE "=" NUM  */
#line 151 "./miniC/miniC.y"
                        { declarar_id_global((yyvsp[-2].cadena), (yyvsp[0].cadena));  }
#line 1572 "./miniC/miniC.tab.c"
    break;

  case 11: /* function_list: function  */
#line 155 "./miniC/miniC.y"
           { (yyval.codigo) = (yyvsp[0].codigo); }
#line 1578 "./miniC/miniC.tab.c"
    break;

  case 12: /* function_list: function_list function  */
#line 156 "./miniC/miniC.y"
                           { concatenaLC((yyvsp[-1].codigo), (yyvsp[0].codigo)); (yyval.codigo) = (yyvsp[-1].codigo); liberaLC((yyvsp[0].codigo)); }
#line 1584 "./miniC/miniC.tab.c"
    break;

  case 13: /* $@2: %empty  */
#line 160 "./miniC/miniC.y"
                          {
    //Reinicimamos el booleano a false
    is_func_main = 0;

    is_main((yyvsp[-1].cadena));

    TablaHash ts = creaTS(PARAMETRO_TS);
    pushStackTS(stack_ts, ts);
  }
#line 1598 "./miniC/miniC.tab.c"
    break;

  case 14: /* $@3: %empty  */
#line 168 "./miniC/miniC.y"
                   {
    //Obtengo el tipo que se espera devolver en la función
    tipo_funcion_actual = (yyvsp[-5].tipo_retorno);
    //Nombre de la función
    char *function_name = (yyvsp[-4].cadena);
    //Parámetros de la función
    Params params = (yyvsp[-1].params);
    //Booleano para saber si tiene return
    has_return = 0;

    //Inserto la función en la tabla de símbolos global (la tabla de símbolos más profunda de la pila)
    declarar_funcion(function_name, tipo_funcion_actual, params);

    //Escribimos la etiqueta fin de función
    fin_funcion = nueva_etiqueta("fin_funcion");
  }
#line 1619 "./miniC/miniC.tab.c"
    break;

  case 15: /* function: return_function IDE "(" $@2 param_list ")" $@3 block  */
#line 183 "./miniC/miniC.y"
          {
      //Tipo de retorno de la función
      TipoRetorno tipo_retorno = (yyvsp[-7].tipo_retorno);
      //Nombre de la función
      char* function_name = (yyvsp[-6].cadena);
      //Parámetros de la función
      Params params = (yyvsp[-3].params);

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
      concatenaLC(codigo, (yyvsp[0].codigo));

      if(is_func_main == 0) 
        concatenaLC(codigo, generar_etiqueta(fin_funcion));

      ListaC fin_marco_pila = generar_fin_marco_pila(is_func_main, fin_funcion);
      concatenaLC(codigo, fin_marco_pila);

      (yyval.codigo) = codigo;
      popStackTS(stack_ts);
    }
#line 1657 "./miniC/miniC.tab.c"
    break;

  case 16: /* param_list: %empty  */
#line 219 "./miniC/miniC.y"
           { 
    (yyval.params).num = 0;
    (yyval.params).nombres = NULL;
  }
#line 1666 "./miniC/miniC.tab.c"
    break;

  case 18: /* param_list: param_list "," param_decl  */
#line 224 "./miniC/miniC.y"
                              { 
    (yyval.params).num = (yyvsp[-2].params).num + (yyvsp[0].params).num;
    (yyval.params).nombres = realloc((yyvsp[-2].params).nombres, (yyval.params).num * sizeof(char*));
    (yyval.params).nombres[(yyvsp[-2].params).num] = (yyvsp[0].params).nombres[0];
  }
#line 1676 "./miniC/miniC.tab.c"
    break;

  case 19: /* param_decl: INT IDE  */
#line 232 "./miniC/miniC.y"
          { 
    declarar_id((yyvsp[0].cadena), PARAMETRO);
    (yyval.params).num = 1;
    (yyval.params).nombres = malloc(sizeof(char*));
    (yyval.params).nombres[0] = (yyvsp[0].cadena);
  }
#line 1687 "./miniC/miniC.tab.c"
    break;

  case 20: /* return_function: INT  */
#line 241 "./miniC/miniC.y"
      { (yyval.tipo_retorno) = TIPO_INT; }
#line 1693 "./miniC/miniC.tab.c"
    break;

  case 21: /* return_function: VOI  */
#line 242 "./miniC/miniC.y"
        { (yyval.tipo_retorno) = TIPO_VOID; }
#line 1699 "./miniC/miniC.tab.c"
    break;

  case 22: /* $@4: %empty  */
#line 245 "./miniC/miniC.y"
        { 
      TablaHash ts = creaTS(LOCAL_TS);
      pushStackTS(stack_ts, ts);
      stack_push_int(stack_offset, 0);
    }
#line 1709 "./miniC/miniC.tab.c"
    break;

  case 23: /* block: "{" $@4 body "}"  */
#line 249 "./miniC/miniC.y"
               { 
      int num_simbolos = numSimbolos(topStackTS(stack_ts));

      ListaC codigo = creaLC();
      if(num_simbolos > 0) {
        ListaC inicio_llaves = generar_inicio_llaves(num_simbolos);
        concatenaLC(codigo, inicio_llaves);
      }

      concatenaLC(codigo, (yyvsp[-1].codigo));

      if(num_simbolos > 0){
        ListaC fin_llaves = generar_fin_llaves(num_simbolos);
        concatenaLC(codigo, fin_llaves);
      }

      stack_pop_int(stack_offset);
      popStackTS(stack_ts);
      (yyval.codigo) = codigo;
    }
#line 1734 "./miniC/miniC.tab.c"
    break;

  case 24: /* body: body declaration  */
#line 272 "./miniC/miniC.y"
                     { concatenaLC((yyvsp[-1].codigo), (yyvsp[0].codigo)); (yyval.codigo) = (yyvsp[-1].codigo); liberaLC((yyvsp[0].codigo)); }
#line 1740 "./miniC/miniC.tab.c"
    break;

  case 25: /* body: body statement  */
#line 273 "./miniC/miniC.y"
                   { concatenaLC((yyvsp[-1].codigo), (yyvsp[0].codigo)); (yyval.codigo) = (yyvsp[-1].codigo); liberaLC((yyvsp[0].codigo)); }
#line 1746 "./miniC/miniC.tab.c"
    break;

  case 26: /* body: %empty  */
#line 274 "./miniC/miniC.y"
           { (yyval.codigo) = creaLC();}
#line 1752 "./miniC/miniC.tab.c"
    break;

  case 27: /* $@5: %empty  */
#line 278 "./miniC/miniC.y"
        { t = VARIABLE_LOCAL; }
#line 1758 "./miniC/miniC.tab.c"
    break;

  case 28: /* declaration: VAR $@5 tipo id_list ";"  */
#line 278 "./miniC/miniC.y"
                                                 { (yyval.codigo) = (yyvsp[-1].codigo); }
#line 1764 "./miniC/miniC.tab.c"
    break;

  case 29: /* $@6: %empty  */
#line 279 "./miniC/miniC.y"
        { t = CONSTANTE; }
#line 1770 "./miniC/miniC.tab.c"
    break;

  case 30: /* declaration: CON $@6 tipo id_list ";"  */
#line 279 "./miniC/miniC.y"
                                            { (yyval.codigo) = (yyvsp[-1].codigo); }
#line 1776 "./miniC/miniC.tab.c"
    break;

  case 32: /* id_list: id_decl  */
#line 287 "./miniC/miniC.y"
            { (yyval.codigo) = (yyvsp[0].codigo); }
#line 1782 "./miniC/miniC.tab.c"
    break;

  case 33: /* id_list: id_list "," id_decl  */
#line 288 "./miniC/miniC.y"
                        { concatenaLC((yyvsp[-2].codigo), (yyvsp[0].codigo)); (yyval.codigo) = (yyvsp[-2].codigo); liberaLC((yyvsp[0].codigo)); }
#line 1788 "./miniC/miniC.tab.c"
    break;

  case 34: /* id_decl: IDE  */
#line 292 "./miniC/miniC.y"
                        { declarar_id((yyvsp[0].cadena), t); (yyval.codigo) = creaLC(); }
#line 1794 "./miniC/miniC.tab.c"
    break;

  case 35: /* id_decl: IDE "=" expression  */
#line 293 "./miniC/miniC.y"
                        { 
    declarar_id((yyvsp[-2].cadena), t);
    Simbolo s = getSimboloStackTS(stack_ts, (yyvsp[-2].cadena));
    (yyval.codigo) = generar_store((yyvsp[0].codigo), s);
  }
#line 1804 "./miniC/miniC.tab.c"
    break;

  case 36: /* statement: asignation ";"  */
#line 301 "./miniC/miniC.y"
                 { (yyval.codigo) = (yyvsp[-1].codigo); }
#line 1810 "./miniC/miniC.tab.c"
    break;

  case 37: /* statement: call_function ";"  */
#line 302 "./miniC/miniC.y"
                      { (yyval.codigo) = (yyvsp[-1].codigo); }
#line 1816 "./miniC/miniC.tab.c"
    break;

  case 38: /* statement: RET expression ";"  */
#line 303 "./miniC/miniC.y"
                       { 
    //Este será el return para funciones que devuelve un INT
    has_return = 1;
    check_return(tipo_funcion_actual, TIPO_INT);
    (yyval.codigo) = generar_return_con_valor((yyvsp[-1].codigo),fin_funcion);
  }
#line 1827 "./miniC/miniC.tab.c"
    break;

  case 39: /* statement: RET ";"  */
#line 309 "./miniC/miniC.y"
            { 
    //Este será el return vacío 
    has_return = 1;
    check_return(tipo_funcion_actual, TIPO_VOID);
    (yyval.codigo) = generar_return(fin_funcion);
  }
#line 1838 "./miniC/miniC.tab.c"
    break;

  case 40: /* statement: block  */
#line 315 "./miniC/miniC.y"
          { (yyval.codigo) = (yyvsp[0].codigo); }
#line 1844 "./miniC/miniC.tab.c"
    break;

  case 41: /* statement: IF "(" expression ")" statement  */
#line 316 "./miniC/miniC.y"
                                                 {
    char *etiqueta_end_if = nueva_etiqueta("end_if");

    ListaC if_simple = creaLC();
    ListaC salto_condicional = generar_salto_condicional("beqz", (yyvsp[-2].codigo), etiqueta_end_if);
    ListaC etiqueta = generar_etiqueta(etiqueta_end_if);
    
    concatenaLC(if_simple, salto_condicional);
    concatenaLC(if_simple, (yyvsp[0].codigo));
    concatenaLC(if_simple, etiqueta);

    (yyval.codigo) = if_simple;
  }
#line 1862 "./miniC/miniC.tab.c"
    break;

  case 42: /* statement: IF "(" expression ")" statement ELS statement  */
#line 329 "./miniC/miniC.y"
                                                  {
    char *etiqueta1 = nueva_etiqueta("else");
    char *etiqueta2 = nueva_etiqueta("end_if");

    ListaC if_else = creaLC();
    ListaC salto_condicional = generar_salto_condicional("beqz", (yyvsp[-4].codigo), etiqueta1);
    ListaC b = generar_b(etiqueta2); 
    ListaC etiqueta_else = generar_etiqueta(etiqueta1);
    ListaC etiqueta_end_if = generar_etiqueta(etiqueta2);

    concatenaLC(if_else, salto_condicional);
    concatenaLC(if_else, (yyvsp[-2].codigo));
    concatenaLC(if_else, b);
    concatenaLC(if_else, etiqueta_else);
    concatenaLC(if_else, (yyvsp[0].codigo));
    concatenaLC(if_else, etiqueta_end_if);

    (yyval.codigo) = if_else;
  }
#line 1886 "./miniC/miniC.tab.c"
    break;

  case 43: /* $@7: %empty  */
#line 348 "./miniC/miniC.y"
        { stack_push(etiquetas_loop, nueva_etiqueta("while_end")); }
#line 1892 "./miniC/miniC.tab.c"
    break;

  case 44: /* statement: WHI $@7 "(" expression ")" statement  */
#line 348 "./miniC/miniC.y"
                                                                                                 {
    //Creamos la etiqueta del inicio while
    char *etiqueta1 = nueva_etiqueta("while_start");
    char *etiqueta2 = stack_top(etiquetas_loop);
    
    ListaC while_loop = creaLC();
    ListaC etiqueta_while_start = generar_etiqueta(etiqueta1);
    ListaC salto_condicional = generar_salto_condicional("beqz",(yyvsp[-2].codigo), etiqueta2);
    ListaC b = generar_b(etiqueta1);
    ListaC etiqueta_while_end = generar_etiqueta(etiqueta2);

    concatenaLC(while_loop, etiqueta_while_start);
    concatenaLC(while_loop, salto_condicional);
    concatenaLC(while_loop, (yyvsp[0].codigo));
    concatenaLC(while_loop, b);
    concatenaLC(while_loop, etiqueta_while_end);
    
    (yyval.codigo) = while_loop;

    stack_pop(etiquetas_loop);
  }
#line 1918 "./miniC/miniC.tab.c"
    break;

  case 45: /* $@8: %empty  */
#line 369 "./miniC/miniC.y"
       { stack_push(etiquetas_loop, nueva_etiqueta("do_while_end")); }
#line 1924 "./miniC/miniC.tab.c"
    break;

  case 46: /* statement: DO $@8 statement WHI "(" expression ")" ";"  */
#line 369 "./miniC/miniC.y"
                                                                                                            { 
    //Creamos la etiqueta del inicio while
    char *etiqueta1 = nueva_etiqueta("do_while_start");
    char *etiqueta2 = stack_top(etiquetas_loop);

    ListaC do_while_loop = creaLC();
    ListaC etiqueta_do_while_start = generar_etiqueta(etiqueta1);
    ListaC etiqueta_do_while_end = generar_etiqueta(etiqueta2);
    ListaC salto_condicional = generar_salto_condicional("bnez", (yyvsp[-2].codigo), etiqueta1);

    concatenaLC(do_while_loop, etiqueta_do_while_start);
    concatenaLC(do_while_loop, (yyvsp[-5].codigo));
    concatenaLC(do_while_loop, salto_condicional);
    concatenaLC(do_while_loop, etiqueta_do_while_end);

    (yyval.codigo) = do_while_loop;

    stack_pop(etiquetas_loop);
  }
#line 1948 "./miniC/miniC.tab.c"
    break;

  case 47: /* $@9: %empty  */
#line 388 "./miniC/miniC.y"
        { stack_push(etiquetas_loop, nueva_etiqueta("for_end")); }
#line 1954 "./miniC/miniC.tab.c"
    break;

  case 48: /* statement: FOR $@9 "(" asignation ";" expression ";" asignation ")" statement  */
#line 388 "./miniC/miniC.y"
                                                                                                                              { 
    char *etiqueta1 = nueva_etiqueta("for_start");
    char *etiqueta2 = stack_top(etiquetas_loop);

    ListaC for_loop = creaLC();
    ListaC etiqueta_for_start = generar_etiqueta(etiqueta1);
    ListaC salto_condicional = generar_salto_condicional("beqz", (yyvsp[-4].codigo), etiqueta2);
    ListaC b = generar_b(etiqueta1);
    ListaC etiqueta_for_end = generar_etiqueta(etiqueta2);

    concatenaLC(for_loop, (yyvsp[-6].codigo));
    concatenaLC(for_loop, etiqueta_for_start);
    concatenaLC(for_loop, salto_condicional);
    concatenaLC(for_loop, (yyvsp[0].codigo));
    concatenaLC(for_loop, (yyvsp[-2].codigo));
    concatenaLC(for_loop, b);
    concatenaLC(for_loop, etiqueta_for_end);
    
    (yyval.codigo) = for_loop;
    stack_pop(etiquetas_loop);
  }
#line 1980 "./miniC/miniC.tab.c"
    break;

  case 49: /* statement: BRK ";"  */
#line 409 "./miniC/miniC.y"
            {
    ListaC cod_break = creaLC();
    if(!stack_empty(etiquetas_loop)){
      ListaC salto_incondicional = generar_b(stack_top(etiquetas_loop));
      concatenaLC(cod_break,salto_incondicional);
    }else print_error(BREAK_ERR);     
    
    (yyval.codigo) = cod_break;
  }
#line 1994 "./miniC/miniC.tab.c"
    break;

  case 50: /* statement: PRI "(" print_list ")" ";"  */
#line 418 "./miniC/miniC.y"
                                { (yyval.codigo) = (yyvsp[-2].codigo); }
#line 2000 "./miniC/miniC.tab.c"
    break;

  case 51: /* statement: REA "(" read_list ")" ";"  */
#line 419 "./miniC/miniC.y"
                                { (yyval.codigo) = (yyvsp[-2].codigo); }
#line 2006 "./miniC/miniC.tab.c"
    break;

  case 52: /* $@10: %empty  */
#line 423 "./miniC/miniC.y"
      { 
    check_id((yyvsp[0].cadena)); 
    check_const((yyvsp[0].cadena), not_mod_const); 
  }
#line 2015 "./miniC/miniC.tab.c"
    break;

  case 53: /* asignation: IDE $@10 "=" expression  */
#line 426 "./miniC/miniC.y"
                   { 
    Simbolo s = getSimboloStackTS(stack_ts, (yyvsp[-3].cadena));
    (yyval.codigo) = generar_store((yyvsp[0].codigo), s); 
  }
#line 2024 "./miniC/miniC.tab.c"
    break;

  case 54: /* print_list: print_item  */
#line 432 "./miniC/miniC.y"
                                { (yyval.codigo) = (yyvsp[0].codigo); }
#line 2030 "./miniC/miniC.tab.c"
    break;

  case 55: /* print_list: print_list "," print_item  */
#line 433 "./miniC/miniC.y"
                                { concatenaLC((yyvsp[-2].codigo), (yyvsp[0].codigo)); (yyval.codigo) = (yyvsp[-2].codigo); }
#line 2036 "./miniC/miniC.tab.c"
    break;

  case 56: /* print_item: expression  */
#line 437 "./miniC/miniC.y"
                { (yyval.codigo) = generar_print_expresiones((yyvsp[0].codigo)); }
#line 2042 "./miniC/miniC.tab.c"
    break;

  case 57: /* print_item: CAD  */
#line 438 "./miniC/miniC.y"
            { 
    char *etiqueta_asciiz = escribir_asciiz((yyvsp[0].cadena)); 
    (yyval.codigo) = generar_print_asciiz(etiqueta_asciiz); 
  }
#line 2051 "./miniC/miniC.tab.c"
    break;

  case 58: /* read_list: IDE  */
#line 445 "./miniC/miniC.y"
                                              { 
      check_id((yyvsp[0].cadena));
      check_const((yyvsp[0].cadena), not_read_const); 
      (yyval.codigo) = generar_read((yyvsp[0].cadena)); 
    }
#line 2061 "./miniC/miniC.tab.c"
    break;

  case 59: /* read_list: read_list "," IDE  */
#line 450 "./miniC/miniC.y"
                                              { 
      check_id((yyvsp[0].cadena));
      check_const((yyvsp[0].cadena), not_read_const); 
      ListaC read = generar_read((yyvsp[0].cadena));  
      concatenaLC((yyvsp[-2].codigo), read); 
      (yyval.codigo) = (yyvsp[-2].codigo);
    }
#line 2073 "./miniC/miniC.tab.c"
    break;

  case 60: /* arg_list: %empty  */
#line 460 "./miniC/miniC.y"
           { 
      (yyval.args).codigo_argumentos = NULL;
      (yyval.args).registros = NULL;
      (yyval.args).num = 0;
    }
#line 2083 "./miniC/miniC.tab.c"
    break;

  case 61: /* arg_list: expression  */
#line 465 "./miniC/miniC.y"
               {
    (yyval.args).num = 1;
    (yyval.args).codigo_argumentos = (yyvsp[0].codigo);

    (yyval.args).registros = (char**)malloc(sizeof(char*));
    (yyval.args).registros[0] = recuperaResLC((yyvsp[0].codigo));
  }
#line 2095 "./miniC/miniC.tab.c"
    break;

  case 62: /* arg_list: arg_list "," expression  */
#line 472 "./miniC/miniC.y"
                            {
    (yyval.args).num = (yyvsp[-2].args).num + 1;

    concatenaLC((yyvsp[-2].args).codigo_argumentos, (yyvsp[0].codigo));
    (yyval.args).codigo_argumentos = (yyvsp[-2].args).codigo_argumentos;

    (yyval.args).registros = (char**)realloc((yyvsp[-2].args).registros, (yyval.args).num * sizeof(char*));
    (yyval.args).registros[(yyvsp[-2].args).num] = recuperaResLC((yyvsp[0].codigo));
  }
#line 2109 "./miniC/miniC.tab.c"
    break;

  case 63: /* expression: call_function  */
#line 484 "./miniC/miniC.y"
                                  { (yyval.codigo) = (yyvsp[0].codigo); }
#line 2115 "./miniC/miniC.tab.c"
    break;

  case 64: /* expression: expression "!=" expression  */
#line 485 "./miniC/miniC.y"
                                  { (yyval.codigo) = generar_expresion_binaria((yyvsp[-2].codigo), (yyvsp[0].codigo), "sne"); }
#line 2121 "./miniC/miniC.tab.c"
    break;

  case 65: /* expression: expression "==" expression  */
#line 486 "./miniC/miniC.y"
                                  { (yyval.codigo) = generar_expresion_binaria((yyvsp[-2].codigo), (yyvsp[0].codigo), "seq"); }
#line 2127 "./miniC/miniC.tab.c"
    break;

  case 66: /* expression: expression ">" expression  */
#line 487 "./miniC/miniC.y"
                                  { (yyval.codigo) = generar_expresion_binaria((yyvsp[-2].codigo), (yyvsp[0].codigo), "sgt"); }
#line 2133 "./miniC/miniC.tab.c"
    break;

  case 67: /* expression: expression ">=" expression  */
#line 488 "./miniC/miniC.y"
                                  { (yyval.codigo) = generar_expresion_binaria((yyvsp[-2].codigo), (yyvsp[0].codigo), "sge"); }
#line 2139 "./miniC/miniC.tab.c"
    break;

  case 68: /* expression: expression "<" expression  */
#line 489 "./miniC/miniC.y"
                                  { (yyval.codigo) = generar_expresion_binaria((yyvsp[-2].codigo), (yyvsp[0].codigo), "slt"); }
#line 2145 "./miniC/miniC.tab.c"
    break;

  case 69: /* expression: expression "<=" expression  */
#line 490 "./miniC/miniC.y"
                                  { (yyval.codigo) = generar_expresion_binaria((yyvsp[-2].codigo), (yyvsp[0].codigo), "sle"); }
#line 2151 "./miniC/miniC.tab.c"
    break;

  case 70: /* expression: expression "+" expression  */
#line 491 "./miniC/miniC.y"
                                  { (yyval.codigo) = generar_expresion_binaria((yyvsp[-2].codigo), (yyvsp[0].codigo), "add"); }
#line 2157 "./miniC/miniC.tab.c"
    break;

  case 71: /* expression: expression "-" expression  */
#line 492 "./miniC/miniC.y"
                                  { (yyval.codigo) = generar_expresion_binaria((yyvsp[-2].codigo), (yyvsp[0].codigo), "sub"); }
#line 2163 "./miniC/miniC.tab.c"
    break;

  case 72: /* expression: expression "*" expression  */
#line 493 "./miniC/miniC.y"
                                  { (yyval.codigo) = generar_expresion_binaria((yyvsp[-2].codigo), (yyvsp[0].codigo), "mul"); }
#line 2169 "./miniC/miniC.tab.c"
    break;

  case 73: /* expression: expression "/" expression  */
#line 494 "./miniC/miniC.y"
                                  { (yyval.codigo) = generar_expresion_binaria((yyvsp[-2].codigo), (yyvsp[0].codigo), "div"); }
#line 2175 "./miniC/miniC.tab.c"
    break;

  case 74: /* expression: "-" expression  */
#line 495 "./miniC/miniC.y"
                                  { (yyval.codigo) = generar_expresion_unaria((yyvsp[0].codigo)); }
#line 2181 "./miniC/miniC.tab.c"
    break;

  case 75: /* expression: "(" expression ")"  */
#line 496 "./miniC/miniC.y"
                                  { (yyval.codigo) = (yyvsp[-1].codigo); }
#line 2187 "./miniC/miniC.tab.c"
    break;

  case 76: /* expression: NUM  */
#line 497 "./miniC/miniC.y"
                                  { (yyval.codigo) = generar_load_immediate((yyvsp[0].cadena)); }
#line 2193 "./miniC/miniC.tab.c"
    break;

  case 77: /* expression: IDE  */
#line 498 "./miniC/miniC.y"
                                  {
    check_id((yyvsp[0].cadena));
    Simbolo s = getSimboloStackTS(stack_ts, (yyvsp[0].cadena));
    (yyval.codigo) = generar_load_simbolo(s);
  }
#line 2203 "./miniC/miniC.tab.c"
    break;

  case 78: /* call_function: IDE "(" arg_list ")"  */
#line 506 "./miniC/miniC.y"
                       {
    Args args = (yyvsp[-1].args);
    int num_args = args.num;
    
    check_funcion((yyvsp[-3].cadena), num_args);

    ListaC codigo = creaLC();

    //Generamos el incio del marco de pila de la llamada
    if(num_args > 0) concatenaLC(codigo, generar_inicio_marco_pila_llamada(args));

    //Genera los argumentos del código
    ListaC args_codigo = generar_llamada_funcion((yyvsp[-3].cadena), args);
    char *res = recuperaResLC(args_codigo);
    concatenaLC(codigo, args_codigo);
    guardaResLC(codigo, res);

    //Generamos el fin del marco de pila de la llamada
    if(num_args > 0) concatenaLC(codigo, generar_fin_marco_pila_llamada(args));

    (yyval.codigo) = codigo;
  }
#line 2230 "./miniC/miniC.tab.c"
    break;


#line 2234 "./miniC/miniC.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 529 "./miniC/miniC.y"


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
