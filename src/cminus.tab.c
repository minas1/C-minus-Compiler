/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7.12-4996"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "cminus.y"

	#include <stdio.h>
	#include <string.h>
	#include <stdbool.h>
	
	#include "util.h"
	#include "symboltable.h"
	#include "strvec.h"
	#include "intvec.h"
	#include "three-code-helper.h"
	#include "math.h"
	
	extern char *yytext; // using flex
	
	#define YYDEBUG_LEXER_TEXT yytext
	
	extern SymbolTable *symbolTable;				// the global symbol table, in cmc.c
	
	extern StrVec *paramTypesVec;					// string vector used to store parameters inside
	extern StrVec *paramNamesVec;
	
	extern StrVec *paramTypesVecCall;				// store types for function calls
	
	extern StrVec *returnTypes;						// returns in a function, their lines and scope depth
	extern IntVec *returnTypesLines;
	extern IntVec *scopeDepths;
	
	extern int functionBraceCount;
	
	extern InstructionList *threeCodes;
	
	extern bool errorOccured;

/* Line 371 of yacc.c  */
#line 102 "cminus.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "cminus.tab.h".  */
#ifndef YY_YY_CMINUS_TAB_H_INCLUDED
# define YY_YY_CMINUS_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     UINT_LITERAL = 258,
     INT_LITERAL = 259,
     FLOAT_LITERAL = 260,
     STRING_LITERAL = 261,
     TOKEN_ID = 262,
     TOKEN_COMMA = 263,
     TOKEN_GE = 264,
     TOKEN_LE = 265,
     TOKEN_LESS = 266,
     TOKEN_GREATER = 267,
     TOKEN_EQUALS = 268,
     TOKEN_NE = 269,
     TOKEN_SEMICOLON = 270,
     TOKEN_R_BRACKET = 271,
     TOKEN_L_BRACKET = 272,
     TOKEN_DOT = 273,
     TOKEN_L_PAREN = 274,
     TOKEN_R_PAREN = 275,
     TOKEN_L_BRACE = 276,
     TOKEN_R_BRACE = 277,
     TOKEN_ASSIGN = 278,
     TOKEN_ADD = 279,
     TOKEN_SUB = 280,
     TOKEN_MUL = 281,
     TOKEN_DIV = 282,
     TOKEN_REM = 283,
     TOKEN_WRITELN = 284,
     TOKEN_READ_INT = 285,
     TOKEN_INT = 286,
     TOKEN_FLOAT = 287,
     TOKEN_VOID = 288,
     TOKEN_IF = 289,
     TOKEN_ELSE = 290,
     TOKEN_RETURN = 291,
     TOKEN_WHILE = 292,
     TOKEN_TYPEOF = 293,
     TOKEN_PRAGMA = 294
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 36 "cminus.y"

	SymbolInfo a_symbol;
	
	char a_string[1000];
	int a_int;
	float a_float;


/* Line 387 of yacc.c  */
#line 193 "cminus.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_CMINUS_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 221 "cminus.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif


/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   229

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  89
/* YYNRULES -- Number of states.  */
#define YYNSTATES  156

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   294

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
      35,    36,    37,    38,    39
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    18,    25,
      29,    35,    37,    39,    41,    46,    53,    55,    57,    59,
      60,    64,    66,    70,    73,    78,    83,    88,    93,    97,
      98,   101,   103,   105,   107,   109,   111,   113,   115,   121,
     124,   132,   138,   146,   152,   157,   160,   164,   168,   172,
     174,   176,   181,   185,   187,   189,   191,   193,   195,   197,
     199,   203,   205,   209,   211,   213,   217,   219,   221,   223,
     225,   229,   231,   233,   235,   237,   239,   241,   243,   245,
     249,   254,   259,   266,   270,   274,   275,   277,   281,   283
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      41,     0,    -1,    42,    -1,    42,    43,    -1,    43,    -1,
      44,    -1,    46,    -1,    45,     7,    15,    -1,    45,     7,
      17,     3,    16,    15,    -1,    45,     1,    15,    -1,    45,
       7,    23,     1,    15,    -1,    31,    -1,    32,    -1,    33,
      -1,    38,    19,     7,    20,    -1,    45,     7,    19,    47,
      20,    51,    -1,    48,    -1,    49,    -1,    33,    -1,    -1,
      49,     8,    50,    -1,    50,    -1,    49,     8,     1,    -1,
      45,     7,    -1,    45,     7,    17,    16,    -1,    45,    17,
      16,     7,    -1,    45,     7,    17,     1,    -1,    45,    17,
       1,     7,    -1,    21,    52,    22,    -1,    -1,    52,    53,
      -1,    55,    -1,    51,    -1,    56,    -1,    57,    -1,    58,
      -1,    44,    -1,    54,    -1,    29,    19,    61,    20,    15,
      -1,    59,    15,    -1,    39,    19,     7,     8,     6,    20,
      15,    -1,    34,    19,    61,    20,    53,    -1,    34,    19,
      61,    20,    53,    35,    53,    -1,    37,    19,    59,    20,
      53,    -1,    37,    19,     1,    20,    -1,    36,    15,    -1,
      36,    59,    15,    -1,    36,     1,    15,    -1,    60,    23,
      59,    -1,    61,    -1,     7,    -1,     7,    17,    59,    16,
      -1,    63,    62,    63,    -1,    63,    -1,     9,    -1,    11,
      -1,    12,    -1,    10,    -1,    13,    -1,    14,    -1,    63,
      64,    65,    -1,    65,    -1,    63,    64,     1,    -1,    24,
      -1,    25,    -1,    65,    66,    67,    -1,    67,    -1,    26,
      -1,    27,    -1,    28,    -1,    19,    59,    20,    -1,    60,
      -1,    69,    -1,     3,    -1,     4,    -1,     5,    -1,    70,
      -1,    71,    -1,    68,    -1,    30,    19,    20,    -1,     7,
      19,    72,    20,    -1,     7,    19,     1,    20,    -1,    67,
      18,     7,    19,    72,    20,    -1,    67,    18,     7,    -1,
      45,    18,     7,    -1,    -1,    73,    -1,    73,     8,    59,
      -1,    59,    -1,    73,     8,     1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    62,    62,    71,    72,    74,    75,    78,    91,   125,
     126,   129,   130,   131,   132,   135,   168,   185,   186,   187,
     190,   191,   192,   195,   208,   209,   210,   211,   214,   221,
     222,   225,   226,   227,   228,   229,   230,   231,   234,   237,
     238,   242,   266,   303,   330,   334,   343,   350,   353,   385,
     388,   408,   454,   487,   495,   496,   497,   498,   499,   500,
     503,   525,   530,   533,   534,   538,   557,   560,   561,   562,
     565,   566,   567,   568,   569,   570,   571,   572,   573,   576,
     589,   612,   616,   643,   655,   667,   668,   671,   683,   689
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "UINT_LITERAL", "INT_LITERAL",
  "FLOAT_LITERAL", "STRING_LITERAL", "TOKEN_ID", "TOKEN_COMMA", "TOKEN_GE",
  "TOKEN_LE", "TOKEN_LESS", "TOKEN_GREATER", "TOKEN_EQUALS", "TOKEN_NE",
  "TOKEN_SEMICOLON", "TOKEN_R_BRACKET", "TOKEN_L_BRACKET", "TOKEN_DOT",
  "TOKEN_L_PAREN", "TOKEN_R_PAREN", "TOKEN_L_BRACE", "TOKEN_R_BRACE",
  "TOKEN_ASSIGN", "TOKEN_ADD", "TOKEN_SUB", "TOKEN_MUL", "TOKEN_DIV",
  "TOKEN_REM", "TOKEN_WRITELN", "TOKEN_READ_INT", "TOKEN_INT",
  "TOKEN_FLOAT", "TOKEN_VOID", "TOKEN_IF", "TOKEN_ELSE", "TOKEN_RETURN",
  "TOKEN_WHILE", "TOKEN_TYPEOF", "TOKEN_PRAGMA", "$accept", "program",
  "declaration_list", "declaration", "var_declaration", "type_specifier",
  "fun_declaration", "fun_params", "params", "param_list", "param",
  "compound_stmt", "statement_list", "statement", "writeln_stmt",
  "expression_stmt", "selection_stmt", "iteration_stmt", "return_stmt",
  "expression", "var", "simple_expression", "relop", "additive_expression",
  "addop", "term", "mulop", "factor", "read_int_stmt", "call", "ufcs",
  "property", "args", "arg_list", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    40,    41,    42,    42,    43,    43,    44,    44,    44,
      44,    45,    45,    45,    45,    46,    47,    48,    48,    48,
      49,    49,    49,    50,    50,    50,    50,    50,    51,    52,
      52,    53,    53,    53,    53,    53,    53,    53,    54,    55,
      55,    56,    56,    57,    57,    58,    58,    58,    59,    59,
      60,    60,    61,    61,    62,    62,    62,    62,    62,    62,
      63,    63,    63,    64,    64,    65,    65,    66,    66,    66,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    68,
      69,    69,    70,    71,    71,    72,    72,    73,    73,    73
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     3,     6,     3,
       5,     1,     1,     1,     4,     6,     1,     1,     1,     0,
       3,     1,     3,     2,     4,     4,     4,     4,     3,     0,
       2,     1,     1,     1,     1,     1,     1,     1,     5,     2,
       7,     5,     7,     5,     4,     2,     3,     3,     3,     1,
       1,     4,     3,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     3,     1,     1,     3,     1,     1,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       4,     4,     6,     3,     3,     0,     1,     3,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    11,    12,    13,     0,     0,     2,     4,     5,     0,
       6,     0,     1,     3,     0,     0,     0,     9,     7,     0,
      19,     0,    14,     0,    13,     0,     0,    16,    17,    21,
       0,     0,    23,     0,     0,     0,    10,     8,     0,     0,
       0,    29,    15,    22,    20,    26,    24,    27,    25,     0,
      73,    74,    75,    50,     0,    28,     0,     0,     0,     0,
       0,     0,    36,     0,    32,    30,    37,    31,    33,    34,
      35,     0,    71,    49,    53,    61,    66,    78,    72,    76,
      77,     0,     0,     0,     0,     0,     0,     0,     0,    45,
       0,     0,     0,     0,     0,    39,     0,    54,    57,    55,
      56,    58,    59,    63,    64,     0,     0,    67,    68,    69,
       0,     0,     0,     0,    88,     0,    86,    70,    71,     0,
      79,     0,    47,    46,     0,     0,     0,    84,    48,    52,
      62,    60,    65,    83,    51,    81,    80,     0,     0,     0,
      44,     0,     0,    85,    89,    87,    38,    41,    43,     0,
       0,     0,     0,    82,    42,    40
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     5,     6,     7,    62,    83,    10,    26,    27,    28,
      29,    64,    49,    65,    66,    67,    68,    69,    70,    71,
      72,    73,   105,    74,   106,    75,   110,    76,    77,    78,
      79,    80,   115,   116
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -125
static const yytype_int16 yypact[] =
{
     164,  -125,  -125,  -125,   -18,     5,   164,  -125,  -125,    12,
    -125,     9,  -125,  -125,    -6,    50,    11,  -125,  -125,    31,
     178,    37,  -125,    34,    43,    38,    46,  -125,    48,  -125,
      42,    60,    62,     2,    81,    10,  -125,  -125,     7,    76,
     106,  -125,  -125,  -125,  -125,  -125,  -125,  -125,  -125,   133,
    -125,  -125,  -125,    84,   175,  -125,    95,   105,   107,    21,
     114,   116,  -125,     3,  -125,  -125,  -125,  -125,  -125,  -125,
    -125,   110,   121,  -125,   118,    66,   131,  -125,  -125,  -125,
    -125,   175,    57,   132,   136,   175,   140,   175,   153,  -125,
     159,    67,   169,    89,   170,  -125,   175,  -125,  -125,  -125,
    -125,  -125,  -125,  -125,  -125,   175,    77,  -125,  -125,  -125,
     175,   174,   173,   179,  -125,   180,   190,  -125,  -125,   181,
    -125,   183,  -125,  -125,   184,   192,   206,  -125,  -125,    22,
    -125,    66,   131,   196,  -125,  -125,  -125,   115,   202,   154,
    -125,   154,   212,   175,  -125,  -125,  -125,   185,  -125,   199,
     201,   154,   207,  -125,  -125,  -125
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -125,  -125,  -125,   217,   111,     0,  -125,  -125,  -125,  -125,
     189,   191,  -125,  -124,  -125,  -125,  -125,  -125,  -125,   -52,
     -73,    36,  -125,   122,  -125,   120,  -125,   119,  -125,  -125,
    -125,  -125,    85,  -125
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -86
static const yytype_int16 yytable[] =
{
       9,    11,    84,    39,    14,    12,     9,    90,    45,    17,
      93,    43,   118,    14,   118,   147,    16,   148,    40,    15,
      25,    94,    88,    46,    50,    51,    52,   154,    53,   112,
     114,    22,   118,   118,    23,    25,    89,   118,    30,   125,
      54,     1,     2,     3,   128,    32,   103,   104,     4,    63,
      31,    57,     1,     2,     3,    33,    35,    36,   113,     4,
      50,    51,    52,   -18,    53,    18,    34,    19,   124,    20,
      50,    51,    52,    21,    53,    37,    54,   -85,   130,    38,
      50,    51,    52,    47,    53,   145,    54,    57,     1,     2,
       3,   114,   107,   108,   109,     4,    54,    57,     1,     2,
       3,    81,    41,    82,    18,     4,    19,    57,     1,     2,
       3,     8,    21,    48,    85,     4,   144,     8,    50,    51,
      52,   119,    53,   121,    86,    95,    87,    97,    98,    99,
     100,   101,   102,    91,    54,    92,    50,    51,    52,    63,
      53,    63,   103,   104,    96,    57,     1,     2,     3,   111,
      94,    63,    54,     4,    41,    55,   117,    50,    51,    52,
     120,    53,    56,    57,     1,     2,     3,    58,   122,    59,
      60,     4,    61,    54,   123,    41,   126,   127,    50,    51,
      52,   133,    53,    56,    57,     1,     2,     3,    58,   134,
      59,    60,     4,    61,    54,     1,     2,     3,   137,   135,
     136,   138,     4,   139,   140,    57,     1,     2,     3,     1,
       2,    24,   141,     4,   142,   143,     4,   146,   149,   152,
     151,   153,   155,    13,    44,    42,   131,   129,   150,   132
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-125)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_uint8 yycheck[] =
{
       0,    19,    54,     1,     1,     0,     6,    59,     1,    15,
       7,     1,    85,     1,    87,   139,     7,   141,    16,     7,
      20,    18,     1,    16,     3,     4,     5,   151,     7,    81,
      82,    20,   105,   106,     3,    35,    15,   110,     1,    91,
      19,    31,    32,    33,    96,     7,    24,    25,    38,    49,
      16,    30,    31,    32,    33,    17,     8,    15,     1,    38,
       3,     4,     5,    20,     7,    15,    20,    17,     1,    19,
       3,     4,     5,    23,     7,    15,    19,    20,     1,    17,
       3,     4,     5,     7,     7,   137,    19,    30,    31,    32,
      33,   143,    26,    27,    28,    38,    19,    30,    31,    32,
      33,    17,    21,    19,    15,    38,    17,    30,    31,    32,
      33,     0,    23,     7,    19,    38,     1,     6,     3,     4,
       5,    85,     7,    87,    19,    15,    19,     9,    10,    11,
      12,    13,    14,    19,    19,    19,     3,     4,     5,   139,
       7,   141,    24,    25,    23,    30,    31,    32,    33,    18,
      18,   151,    19,    38,    21,    22,    20,     3,     4,     5,
      20,     7,    29,    30,    31,    32,    33,    34,    15,    36,
      37,    38,    39,    19,    15,    21,     7,     7,     3,     4,
       5,     7,     7,    29,    30,    31,    32,    33,    34,    16,
      36,    37,    38,    39,    19,    31,    32,    33,     8,    20,
      20,    20,    38,    20,    20,    30,    31,    32,    33,    31,
      32,    33,    20,    38,     8,    19,    38,    15,     6,    20,
      35,    20,    15,     6,    35,    34,   106,   105,   143,   110
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    31,    32,    33,    38,    41,    42,    43,    44,    45,
      46,    19,     0,    43,     1,     7,     7,    15,    15,    17,
      19,    23,    20,     3,    33,    45,    47,    48,    49,    50,
       1,    16,     7,    17,    20,     8,    15,    15,    17,     1,
      16,    21,    51,     1,    50,     1,    16,     7,     7,    52,
       3,     4,     5,     7,    19,    22,    29,    30,    34,    36,
      37,    39,    44,    45,    51,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    63,    65,    67,    68,    69,    70,
      71,    17,    19,    45,    59,    19,    19,    19,     1,    15,
      59,    19,    19,     7,    18,    15,    23,     9,    10,    11,
      12,    13,    14,    24,    25,    62,    64,    26,    27,    28,
      66,    18,    59,     1,    59,    72,    73,    20,    60,    61,
      20,    61,    15,    15,     1,    59,     7,     7,    59,    63,
       1,    65,    67,     7,    16,    20,    20,     8,    20,    20,
      20,    20,     8,    19,     1,    59,    15,    53,    53,     6,
      72,    35,    20,    20,    53,    15
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YYUSE (yytype);
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
/* Line 1787 of yacc.c  */
#line 63 "cminus.y"
    {
	//printf("--- program ---\n");
	//InstrList_print($1.code);
	
	threeCodes = (yyvsp[(1) - (1)].a_symbol).code;
}
    break;

  case 3:
/* Line 1787 of yacc.c  */
#line 71 "cminus.y"
    { if( !errorOccured ) { (yyval.a_symbol).code = InstrList_create(); InstrList_concat((yyval.a_symbol).code, (yyvsp[(1) - (2)].a_symbol).code); InstrList_concat((yyval.a_symbol).code, (yyvsp[(2) - (2)].a_symbol).code); } }
    break;

  case 4:
/* Line 1787 of yacc.c  */
#line 72 "cminus.y"
    { (yyval.a_symbol).code = (yyvsp[(1) - (1)].a_symbol).code; }
    break;

  case 5:
/* Line 1787 of yacc.c  */
#line 74 "cminus.y"
    { (yyval.a_symbol).code = (yyvsp[(1) - (1)].a_symbol).code; }
    break;

  case 6:
/* Line 1787 of yacc.c  */
#line 75 "cminus.y"
    { (yyval.a_symbol).code = (yyvsp[(1) - (1)].a_symbol).code; }
    break;

  case 7:
/* Line 1787 of yacc.c  */
#line 79 "cminus.y"
    {
	(yyval.a_symbol).code = InstrList_create();
	
	Symbol *s = varDeclaration((yyvsp[(1) - (3)].a_string), (yyvsp[(2) - (3)].a_string), 0);
	if( s != NULL && !errorOccured )
	{
		if( strcmp(s->type, "int") == 0 )
			codeGenLoadInt((yyval.a_symbol).code, s->place, 0);
		else if( strcmp(s->type, "float") == 0 )
			codeGenLoadFloat((yyval.a_symbol).code, s->place, NAN);
	}
}
    break;

  case 8:
/* Line 1787 of yacc.c  */
#line 92 "cminus.y"
    {
	(yyval.a_symbol).code = InstrList_create();
	
	char buffer[1000];
	strcpy(buffer, (yyvsp[(1) - (6)].a_string));
	strcat(buffer, "[]");
	
	//printf("var_declaration type: %s\n", buffer);
	Symbol *s = varDeclaration(buffer, (yyvsp[(2) - (6)].a_string), (yyvsp[(4) - (6)].a_int));
	
	if( s != NULL )
	{
		uint32_t place = s->place; // get its place to put the length into it. we'll make a new place for the arrays address
		
		//printf("place = %u\n", place);
		
		if( !errorOccured )
		{
			codeGenLoadInt((yyval.a_symbol).code, place, (yyvsp[(4) - (6)].a_int)); // the size of the array is stored at the beginning
			
			if( strcmp(s->type, "int[]") == 0 )
			{
				uint32_t i;
				
				s->place = genPlace();
				codeGenLoadInt((yyval.a_symbol).code, s->place, 0); 	// load the value at the 1st address
				
				for(i = 1; i < (yyvsp[(4) - (6)].a_int); ++i)				// load the rest
					codeGenLoadInt((yyval.a_symbol).code, genPlace(), 0);
			}
		}
	}
}
    break;

  case 9:
/* Line 1787 of yacc.c  */
#line 125 "cminus.y"
    { char buffer[100]; sprintf(buffer, "expecting identifier"); yyerror(buffer); }
    break;

  case 10:
/* Line 1787 of yacc.c  */
#line 126 "cminus.y"
    { char buffer[100]; sprintf(buffer, "C- disallows variable declaration and assignment at the same time. Use %s %s; %s = ...", (yyvsp[(1) - (5)].a_string), (yyvsp[(2) - (5)].a_string), (yyvsp[(2) - (5)].a_string)); yyerror(buffer); }
    break;

  case 11:
/* Line 1787 of yacc.c  */
#line 129 "cminus.y"
    { /*printf("type_specifier -> %s\n", $1);*/ }
    break;

  case 12:
/* Line 1787 of yacc.c  */
#line 130 "cminus.y"
    { /*printf("type_specifier -> %s\n", $1);*/ }
    break;

  case 13:
/* Line 1787 of yacc.c  */
#line 131 "cminus.y"
    { /*printf("type_specifier -> %s\n", $1);*/ }
    break;

  case 14:
/* Line 1787 of yacc.c  */
#line 132 "cminus.y"
    { inferTypeOfIdentifier((yyval.a_string), (yyvsp[(3) - (4)].a_string)); }
    break;

  case 15:
/* Line 1787 of yacc.c  */
#line 136 "cminus.y"
    {
			Symbol *func = funcDeclaration((yyvsp[(1) - (6)].a_string), (yyvsp[(2) - (6)].a_string), paramTypesVec, 0);
			
			destroyCurrentScope();
			
			if( !errorOccured )
			{
				(yyval.a_symbol).code = InstrList_create();
				codeGenFuncLabel((yyval.a_symbol).code, func);
				InstrList_concat((yyval.a_symbol).code, (yyvsp[(4) - (6)].a_symbol).code);
				InstrList_concat((yyval.a_symbol).code, (yyvsp[(6) - (6)].a_symbol).code);
				InstrList_destroy((yyvsp[(6) - (6)].a_symbol).code);
				
				if( strcmp((yyval.a_symbol).type, "void") == 0 )
				{
					assert((yyval.a_symbol).code->head && "$$.code->head is null");
					
					InstructionNode *p = (yyval.a_symbol).code->head;
					while( p->next )
						p = p->next;
					if( p->instrType != INSTR_RET )
						codeGenReturn((yyval.a_symbol).code, "void", 0);
				}
			}
			
			
			resetPlace(); // reset place counter to 0
		}
    break;

  case 16:
/* Line 1787 of yacc.c  */
#line 169 "cminus.y"
    {
					functionBraceCount = 1;
					
					SymbolTable *st;
					size_t i;
					
					createNewScope();
					st = symbolTable;
					
					for(i = 0; i < paramTypesVec->length; ++i)
						varDeclaration(paramTypesVec->t[i], paramNamesVec->t[i], 0);

					(yyval.a_symbol).code = (yyvsp[(1) - (1)].a_symbol).code;
				}
    break;

  case 17:
/* Line 1787 of yacc.c  */
#line 185 "cminus.y"
    { if( !errorOccured ) { (yyval.a_symbol).code = InstrList_create(); codeGenFirstArgPlace((yyval.a_symbol).code); } }
    break;

  case 18:
/* Line 1787 of yacc.c  */
#line 186 "cminus.y"
    { if( !errorOccured ) (yyval.a_symbol).code = InstrList_create(); }
    break;

  case 19:
/* Line 1787 of yacc.c  */
#line 187 "cminus.y"
    { if( !errorOccured ) (yyval.a_symbol).code = InstrList_create(); }
    break;

  case 20:
/* Line 1787 of yacc.c  */
#line 190 "cminus.y"
    { }
    break;

  case 21:
/* Line 1787 of yacc.c  */
#line 191 "cminus.y"
    { }
    break;

  case 22:
/* Line 1787 of yacc.c  */
#line 192 "cminus.y"
    { yyerror("expected parameter after ‘,’"); }
    break;

  case 23:
/* Line 1787 of yacc.c  */
#line 196 "cminus.y"
    {
	if( strcmp((yyvsp[(1) - (2)].a_string), "void") == 0 )
	{
		yyerror("\"void\" cannot be used as a type for a variable");
	}
	else
	{
		StrVec_insert(paramTypesVec, (yyvsp[(1) - (2)].a_string));
		StrVec_insert(paramNamesVec, (yyvsp[(2) - (2)].a_string));
		//printf("Normal parameter %s %s!\n", $1, $2);
	}
}
    break;

  case 24:
/* Line 1787 of yacc.c  */
#line 208 "cminus.y"
    { char buff[100]; if( strcmp((yyvsp[(1) - (4)].a_string), "void") == 0 ) { yyerror("\"void\" cannot be used as a type for a variable"); } else { sprintf(buff, "%s[]", (yyvsp[(1) - (4)].a_string)); StrVec_insert(paramTypesVec, buff); StrVec_insert(paramNamesVec, (yyvsp[(2) - (4)].a_string)); printf("Array parameter(1)\n"); } sprintf(buff, "%s[]", (yyvsp[(1) - (4)].a_string)); }
    break;

  case 25:
/* Line 1787 of yacc.c  */
#line 209 "cminus.y"
    { char buff[100]; if( strcmp((yyvsp[(1) - (4)].a_string), "void") == 0 ) { yyerror("\"void\" cannot be used as a type for a variable"); } else { sprintf(buff, "%s[]", (yyvsp[(1) - (4)].a_string)); StrVec_insert(paramTypesVec, buff); StrVec_insert(paramNamesVec, (yyvsp[(4) - (4)].a_string)); printf("Array parameter(2)\n"); } sprintf(buff, "%s[]", (yyvsp[(1) - (4)].a_string)); }
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 210 "cminus.y"
    { char buffer[100]; sprintf(buffer, "error after ‘%s %s[’", (yyvsp[(1) - (4)].a_string), (yyvsp[(2) - (4)].a_string)); yyerror(buffer); }
    break;

  case 27:
/* Line 1787 of yacc.c  */
#line 211 "cminus.y"
    { char buffer[100]; sprintf(buffer, "error after ‘%s[’", (yyvsp[(1) - (4)].a_string)); yyerror(buffer); }
    break;

  case 28:
/* Line 1787 of yacc.c  */
#line 214 "cminus.y"
    { (yyval.a_symbol).code = (yyvsp[(2) - (3)].a_symbol).code; }
    break;

  case 29:
/* Line 1787 of yacc.c  */
#line 221 "cminus.y"
    { if( !errorOccured ) (yyval.a_symbol).code = InstrList_create(); }
    break;

  case 30:
/* Line 1787 of yacc.c  */
#line 222 "cminus.y"
    { if( !errorOccured ) { InstrList_concat((yyval.a_symbol).code, (yyvsp[(2) - (2)].a_symbol).code); InstrList_destroy((yyvsp[(2) - (2)].a_symbol).code); } }
    break;

  case 31:
/* Line 1787 of yacc.c  */
#line 225 "cminus.y"
    { (yyval.a_symbol).code = (yyvsp[(1) - (1)].a_symbol).code; }
    break;

  case 32:
/* Line 1787 of yacc.c  */
#line 226 "cminus.y"
    { (yyval.a_symbol).code = (yyvsp[(1) - (1)].a_symbol).code; }
    break;

  case 33:
/* Line 1787 of yacc.c  */
#line 227 "cminus.y"
    { (yyval.a_symbol).code = (yyvsp[(1) - (1)].a_symbol).code; }
    break;

  case 34:
/* Line 1787 of yacc.c  */
#line 228 "cminus.y"
    { (yyval.a_symbol).code = (yyvsp[(1) - (1)].a_symbol).code; }
    break;

  case 35:
/* Line 1787 of yacc.c  */
#line 229 "cminus.y"
    { (yyval.a_symbol).code = (yyvsp[(1) - (1)].a_symbol).code; }
    break;

  case 36:
/* Line 1787 of yacc.c  */
#line 230 "cminus.y"
    { (yyval.a_symbol).code = (yyvsp[(1) - (1)].a_symbol).code; }
    break;

  case 37:
/* Line 1787 of yacc.c  */
#line 231 "cminus.y"
    { (yyval.a_symbol).code = (yyvsp[(1) - (1)].a_symbol).code; }
    break;

  case 38:
/* Line 1787 of yacc.c  */
#line 234 "cminus.y"
    { (yyval.a_symbol).code = (yyvsp[(3) - (5)].a_symbol).code; codeGenWriteln((yyval.a_symbol).code, (yyvsp[(3) - (5)].a_symbol).type, (yyvsp[(3) - (5)].a_symbol).place); }
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 237 "cminus.y"
    { if( !errorOccured ) { (yyval.a_symbol).code = InstrList_create(); InstrList_concat((yyval.a_symbol).code, (yyvsp[(1) - (2)].a_symbol).code); InstrList_destroy((yyvsp[(1) - (2)].a_symbol).code); } }
    break;

  case 40:
/* Line 1787 of yacc.c  */
#line 238 "cminus.y"
    { (yyval.a_symbol).code = InstrList_create(); pragmaString((yyvsp[(3) - (7)].a_string), (yyvsp[(5) - (7)].a_string)); }
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 243 "cminus.y"
    {
	if( strcmp((yyvsp[(3) - (5)].a_symbol).type, "int") != 0 )
	{
		char buffer[1000];
		sprintf(buffer, "condition of \"if\" statement must be integral, not %s", (yyvsp[(3) - (5)].a_symbol).type);
		yyerror(buffer);
	}
	
	if( !errorOccured )
	{
		(yyval.a_symbol).code = InstrList_create();
		(yyval.a_symbol).after = genLabel(); // $$.begin isn't need for "if" statements
		InstrList_concat((yyval.a_symbol).code, (yyvsp[(3) - (5)].a_symbol).code);
		
		codeGenIfNot((yyval.a_symbol).code, (yyval.a_symbol).after, (yyvsp[(3) - (5)].a_symbol).place);
		InstrList_concat((yyval.a_symbol).code, (yyvsp[(5) - (5)].a_symbol).code);
		codeGenLabel((yyval.a_symbol).code, (yyval.a_symbol).after);
		
		InstrList_destroy((yyvsp[(3) - (5)].a_symbol).code);
		InstrList_destroy((yyvsp[(5) - (5)].a_symbol).code);
	}
	
}
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 267 "cminus.y"
    {
	if( strcmp((yyvsp[(3) - (7)].a_symbol).type, "int") != 0 )
	{
		char buffer[1000];
		sprintf(buffer, "condition of \"if\" statement must be integral, not %s", (yyvsp[(3) - (7)].a_symbol).type);
		yyerror(buffer);
	}
	
	if( !errorOccured )
	{
		(yyval.a_symbol).code = InstrList_create();
		(yyval.a_symbol).after = genLabel(); // $$.begin isn't need for "if" statements
		
		// generate a label for jumping to when the "if" is finished
		// (needed because else the code would execute "if" and "else" as well)
		uint32_t afterElseLabel = genLabel();
		codeGenUnconditionalJump((yyvsp[(5) - (7)].a_symbol).code, afterElseLabel);
		
		InstrList_concat((yyval.a_symbol).code, (yyvsp[(3) - (7)].a_symbol).code);
		
		codeGenIfNot((yyval.a_symbol).code, (yyval.a_symbol).after, (yyvsp[(3) - (7)].a_symbol).place);
		InstrList_concat((yyval.a_symbol).code, (yyvsp[(5) - (7)].a_symbol).code);
		
		
		codeGenLabel((yyval.a_symbol).code, (yyval.a_symbol).after);
		InstrList_concat((yyval.a_symbol).code, (yyvsp[(7) - (7)].a_symbol).code);
		codeGenLabel((yyval.a_symbol).code, afterElseLabel);
		
		InstrList_destroy((yyvsp[(3) - (7)].a_symbol).code);
		InstrList_destroy((yyvsp[(5) - (7)].a_symbol).code);
		InstrList_destroy((yyvsp[(7) - (7)].a_symbol).code);
	}
}
    break;

  case 43:
/* Line 1787 of yacc.c  */
#line 304 "cminus.y"
    {
	if( strcmp((yyvsp[(3) - (5)].a_symbol).type, "int") != 0 )
	{
		char buffer[1000];
		sprintf(buffer, "condition of \"while\" statement must be integral, not %s", (yyvsp[(3) - (5)].a_symbol).type);
		yyerror(buffer);
	}
	
	if( !errorOccured )
	{
		(yyval.a_symbol).code = InstrList_create();
		(yyval.a_symbol).begin = genLabel();
		(yyval.a_symbol).after = genLabel();
		
		codeGenLabel((yyval.a_symbol).code, (yyval.a_symbol).begin);
		InstrList_concat((yyval.a_symbol).code, (yyvsp[(3) - (5)].a_symbol).code);
		codeGenWhileNot((yyval.a_symbol).code, (yyval.a_symbol).begin, (yyval.a_symbol).after, (yyvsp[(3) - (5)].a_symbol).place);
		InstrList_concat((yyval.a_symbol).code, (yyvsp[(5) - (5)].a_symbol).code);
		codeGenUnconditionalJump((yyval.a_symbol).code, (yyval.a_symbol).begin);
		codeGenLabel((yyval.a_symbol).code, (yyval.a_symbol).after);
		
		InstrList_destroy((yyvsp[(3) - (5)].a_symbol).code);
		InstrList_destroy((yyvsp[(5) - (5)].a_symbol).code);
	}
	
}
    break;

  case 44:
/* Line 1787 of yacc.c  */
#line 330 "cminus.y"
    { yyclearin; yyerror("wrong while stament"); }
    break;

  case 45:
/* Line 1787 of yacc.c  */
#line 334 "cminus.y"
    {
															returnStatement("void");
															if( !errorOccured )
															{
																(yyval.a_symbol).code = InstrList_create();
																codeGenReturn((yyval.a_symbol).code, "void", UINT32_MAX);
															}
															
														}
    break;

  case 46:
/* Line 1787 of yacc.c  */
#line 343 "cminus.y"
    {
															returnStatement((yyvsp[(2) - (3)].a_symbol).type);
															
															(yyval.a_symbol).code = (yyvsp[(2) - (3)].a_symbol).code;
															if( !errorOccured ) codeGenReturn((yyval.a_symbol).code, (yyvsp[(2) - (3)].a_symbol).type, (yyvsp[(2) - (3)].a_symbol).place);
															
														}
    break;

  case 47:
/* Line 1787 of yacc.c  */
#line 350 "cminus.y"
    { yyerror("error after \"return\""); }
    break;

  case 48:
/* Line 1787 of yacc.c  */
#line 354 "cminus.y"
    {
	// if the types are not compatible
	if( strcmp((yyvsp[(1) - (3)].a_symbol).type, (yyvsp[(3) - (3)].a_symbol).type) != 0 )
	{
		if( strcmp((yyvsp[(1) - (3)].a_symbol).type, TYPE_ERROR) != 0 && strcmp((yyvsp[(3) - (3)].a_symbol).type, TYPE_ERROR) != 0 )
		{
			char buffer[1000];
			sprintf(buffer, "incompatible types \"%s\" and \"%s\"", (yyvsp[(1) - (3)].a_symbol).type, (yyvsp[(3) - (3)].a_symbol).type);
			yyerror(buffer);
		}
		strcpy((yyval.a_symbol).type, TYPE_ERROR);
	}
	else
	{
		strcpy((yyval.a_symbol).type, (yyvsp[(1) - (3)].a_symbol).type);
		(yyval.a_symbol).place = (yyvsp[(1) - (3)].a_symbol).place;
		
		if( !errorOccured )
		{
			(yyval.a_symbol).code = InstrList_create();
			InstrList_concat((yyval.a_symbol).code, (yyvsp[(1) - (3)].a_symbol).code);
			InstrList_concat((yyval.a_symbol).code, (yyvsp[(3) - (3)].a_symbol).code);
		
			codeGenAssign((yyval.a_symbol).code, (yyvsp[(3) - (3)].a_symbol).type, (yyvsp[(1) - (3)].a_symbol).place, (yyvsp[(3) - (3)].a_symbol).place);
			
			InstrList_destroy((yyvsp[(1) - (3)].a_symbol).code);
			InstrList_destroy((yyvsp[(3) - (3)].a_symbol).code);
		}
	}
}
    break;

  case 49:
/* Line 1787 of yacc.c  */
#line 385 "cminus.y"
    { strcpy((yyval.a_symbol).type, (yyvsp[(1) - (1)].a_symbol).type); (yyval.a_symbol).place = (yyvsp[(1) - (1)].a_symbol).place; (yyval.a_symbol).code = (yyvsp[(1) - (1)].a_symbol).code; }
    break;

  case 50:
/* Line 1787 of yacc.c  */
#line 389 "cminus.y"
    {
	SymbolArray *s = SymbolTable_find(symbolTable, (yyvsp[(1) - (1)].a_string), SEARCH_ALL_PARENTS);
	if( s->length == 0 )
	{
		char buffer[1000];
		sprintf(buffer, "undeclared variable \"%s\"", (yyvsp[(1) - (1)].a_string));
		yyerror(buffer);
		strcpy((yyval.a_symbol).type, TYPE_ERROR);
	}
	else
	{
		strcpy((yyval.a_symbol).type,s->symbols[0]->type);
		(yyval.a_symbol).place = s->symbols[0]->place;
		(yyval.a_symbol).code = InstrList_create();
	}
	
	free(s);
}
    break;

  case 51:
/* Line 1787 of yacc.c  */
#line 409 "cminus.y"
    {
	SymbolArray *s = SymbolTable_find(symbolTable, (yyvsp[(1) - (4)].a_string), SEARCH_ALL_PARENTS);
	if( s->length == 0 )
	{
		char buffer[1000];
		sprintf(buffer, "undeclared array \"%s\"", (yyvsp[(1) - (4)].a_string));
		yyerror(buffer);
		strcpy((yyval.a_symbol).type, TYPE_ERROR);
	}
	else if( strcmp((yyvsp[(3) - (4)].a_symbol).type, "int") != 0 )
	{
		char buffer[1000];
		sprintf(buffer, "array index must be an integral value, not %s", (yyvsp[(3) - (4)].a_symbol).type);
		yyerror(buffer);
		strcpy((yyval.a_symbol).type, TYPE_ERROR);
	}
	else
	{
		Symbol *symbol = s->symbols[0];
		
		char *type = (char*)malloc(sizeof(char) * (strlen(symbol->type) + 1));
		strcpy(type, symbol->type);
		removeChar(type, '['); // remove the brackets get the contained type
		removeChar(type, ']');	// e.g int[] will become int
		strcpy((yyval.a_symbol).type, type);
		
		free(type);
		
		if( !errorOccured )
		{
			(yyval.a_symbol).code = InstrList_create();
			InstrList_concat((yyval.a_symbol).code, (yyvsp[(3) - (4)].a_symbol).code);
			
			(yyval.a_symbol).place = genPlace();
			
			codeGenLoadFromOffset((yyval.a_symbol).code, (yyval.a_symbol).type, (yyval.a_symbol).place, symbol->place, (yyvsp[(3) - (4)].a_symbol).place);
			
			InstrList_destroy((yyvsp[(3) - (4)].a_symbol).code);
		}
	}

	free(s);
}
    break;

  case 52:
/* Line 1787 of yacc.c  */
#line 455 "cminus.y"
    {
		opBinary(&(yyvsp[(1) - (3)].a_symbol), &(yyvsp[(3) - (3)].a_symbol), "<", &(yyval.a_symbol));
		
		if( !errorOccured )
		{
			(yyval.a_symbol).place = genPlace();
			InstrList_concat((yyval.a_symbol).code, (yyvsp[(3) - (3)].a_symbol).code);
			
			(yyval.a_symbol).code = (yyvsp[(1) - (3)].a_symbol).code;
			
			if( strcmp((yyvsp[(2) - (3)].a_string), "<") == 0 )
				codeGenComparisonOp((yyval.a_symbol).code, (yyval.a_symbol).type, INSTR_LESS, (yyval.a_symbol).place, (yyvsp[(1) - (3)].a_symbol).place, (yyvsp[(3) - (3)].a_symbol).place);
			else if( strcmp((yyvsp[(2) - (3)].a_string), "<=") == 0 )
				codeGenComparisonOp((yyval.a_symbol).code, (yyval.a_symbol).type, INSTR_LESS_EQUAL, (yyval.a_symbol).place, (yyvsp[(1) - (3)].a_symbol).place, (yyvsp[(3) - (3)].a_symbol).place);
			else if( strcmp((yyvsp[(2) - (3)].a_string), "==") == 0 )
				codeGenComparisonOp((yyval.a_symbol).code, (yyval.a_symbol).type, INSTR_EQUAL, (yyval.a_symbol).place, (yyvsp[(1) - (3)].a_symbol).place, (yyvsp[(3) - (3)].a_symbol).place);
			else if( strcmp((yyvsp[(2) - (3)].a_string), "!=") == 0 )
				codeGenComparisonOp((yyval.a_symbol).code, (yyval.a_symbol).type, INSTR_NOT_EQUAL, (yyval.a_symbol).place, (yyvsp[(1) - (3)].a_symbol).place, (yyvsp[(3) - (3)].a_symbol).place);
			else if( strcmp((yyvsp[(2) - (3)].a_string), ">") == 0 )
				codeGenComparisonOp((yyval.a_symbol).code, (yyval.a_symbol).type, INSTR_GREATER, (yyval.a_symbol).place, (yyvsp[(1) - (3)].a_symbol).place, (yyvsp[(3) - (3)].a_symbol).place);
			else if( strcmp((yyvsp[(2) - (3)].a_string), ">=") == 0 )
				codeGenComparisonOp((yyval.a_symbol).code, (yyval.a_symbol).type, INSTR_GREATER_EQUAL, (yyval.a_symbol).place, (yyvsp[(1) - (3)].a_symbol).place, (yyvsp[(3) - (3)].a_symbol).place);
			else
			{
				assert(0 && "simple_expr -> additive_expr relop additive_expr: relop is not valid");
			}
				
				
			InstrList_destroy((yyvsp[(3) - (3)].a_symbol).code);
		}
	}
    break;

  case 53:
/* Line 1787 of yacc.c  */
#line 488 "cminus.y"
    {
		strcpy((yyval.a_symbol).type, (yyvsp[(1) - (1)].a_symbol).type);
		(yyval.a_symbol).place = (yyvsp[(1) - (1)].a_symbol).place;
		(yyval.a_symbol).code = (yyvsp[(1) - (1)].a_symbol).code;
	}
    break;

  case 60:
/* Line 1787 of yacc.c  */
#line 504 "cminus.y"
    {
				opBinary(&(yyvsp[(1) - (3)].a_symbol), &(yyvsp[(3) - (3)].a_symbol), "+", &(yyval.a_symbol)); // + or - doesn't matter
				
				if( !errorOccured )
				{
					(yyval.a_symbol).place = genPlace();
					(yyval.a_symbol).code = InstrList_create();
					
					InstrList_concat((yyval.a_symbol).code, (yyvsp[(1) - (3)].a_symbol).code);
					InstrList_concat((yyval.a_symbol).code, (yyvsp[(3) - (3)].a_symbol).code);
					
					if( strcmp((yyvsp[(2) - (3)].a_string), "+") == 0 )
						codeGenAdd((yyval.a_symbol).code, (yyval.a_symbol).type, (yyval.a_symbol).place, (yyvsp[(1) - (3)].a_symbol).place, (yyvsp[(3) - (3)].a_symbol).place);
					else // subtraction here
						codeGenSub((yyval.a_symbol).code, (yyval.a_symbol).type, (yyval.a_symbol).place, (yyvsp[(1) - (3)].a_symbol).place, (yyvsp[(3) - (3)].a_symbol).place);
						
					// do some cleanup like good programmers we are
					InstrList_destroy((yyvsp[(1) - (3)].a_symbol).code);
					InstrList_destroy((yyvsp[(3) - (3)].a_symbol).code);
				}
			}
    break;

  case 61:
/* Line 1787 of yacc.c  */
#line 525 "cminus.y"
    {
				strcpy((yyval.a_symbol).type, (yyvsp[(1) - (1)].a_symbol).type);
				(yyval.a_symbol).place = (yyvsp[(1) - (1)].a_symbol).place;
				(yyval.a_symbol).code = (yyvsp[(1) - (1)].a_symbol).code;
			}
    break;

  case 62:
/* Line 1787 of yacc.c  */
#line 530 "cminus.y"
    { yyerror("expression missing term"); }
    break;

  case 63:
/* Line 1787 of yacc.c  */
#line 533 "cminus.y"
    {}
    break;

  case 64:
/* Line 1787 of yacc.c  */
#line 534 "cminus.y"
    {}
    break;

  case 65:
/* Line 1787 of yacc.c  */
#line 538 "cminus.y"
    {
							opBinary(&(yyvsp[(1) - (3)].a_symbol), &(yyvsp[(3) - (3)].a_symbol), (yyvsp[(2) - (3)].a_string), &(yyval.a_symbol));
							
							if( !errorOccured )
							{
								(yyval.a_symbol).place = genPlace();
								(yyval.a_symbol).code = InstrList_create();
								
								InstrList_concat((yyval.a_symbol).code, (yyvsp[(1) - (3)].a_symbol).code);
								InstrList_concat((yyval.a_symbol).code, (yyvsp[(3) - (3)].a_symbol).code);
								
								if( strcmp((yyvsp[(2) - (3)].a_string), "*") == 0 )		codeGenMul((yyval.a_symbol).code, (yyval.a_symbol).type, (yyval.a_symbol).place, (yyvsp[(1) - (3)].a_symbol).place, (yyvsp[(3) - (3)].a_symbol).place);
								else if( strcmp((yyvsp[(2) - (3)].a_string), "/") == 0 )	codeGenDiv((yyval.a_symbol).code, (yyval.a_symbol).type, (yyval.a_symbol).place, (yyvsp[(1) - (3)].a_symbol).place, (yyvsp[(3) - (3)].a_symbol).place);
								else							codeGenRem((yyval.a_symbol).code, (yyval.a_symbol).type, (yyval.a_symbol).place, (yyvsp[(1) - (3)].a_symbol).place, (yyvsp[(3) - (3)].a_symbol).place); // % operator
								
								InstrList_destroy((yyvsp[(1) - (3)].a_symbol).code);
								InstrList_destroy((yyvsp[(3) - (3)].a_symbol).code);
							}
						}
    break;

  case 66:
/* Line 1787 of yacc.c  */
#line 557 "cminus.y"
    { strcpy((yyval.a_symbol).type, (yyvsp[(1) - (1)].a_symbol).type); (yyval.a_symbol).place = (yyvsp[(1) - (1)].a_symbol).place; (yyval.a_symbol).code = (yyvsp[(1) - (1)].a_symbol).code; }
    break;

  case 70:
/* Line 1787 of yacc.c  */
#line 565 "cminus.y"
    { strcpy((yyval.a_symbol).type, (yyvsp[(2) - (3)].a_symbol).type); (yyval.a_symbol).place = (yyvsp[(2) - (3)].a_symbol).place; (yyval.a_symbol).code = (yyvsp[(2) - (3)].a_symbol).code; }
    break;

  case 71:
/* Line 1787 of yacc.c  */
#line 566 "cminus.y"
    { strcpy((yyval.a_symbol).type, (yyvsp[(1) - (1)].a_symbol).type); (yyval.a_symbol).place = (yyvsp[(1) - (1)].a_symbol).place; (yyval.a_symbol).code = (yyvsp[(1) - (1)].a_symbol).code; }
    break;

  case 72:
/* Line 1787 of yacc.c  */
#line 567 "cminus.y"
    { strcpy((yyval.a_symbol).type, (yyvsp[(1) - (1)].a_symbol).type);	(yyval.a_symbol).place = (yyvsp[(1) - (1)].a_symbol).place; (yyval.a_symbol).code = (yyvsp[(1) - (1)].a_symbol).code; }
    break;

  case 73:
/* Line 1787 of yacc.c  */
#line 568 "cminus.y"
    { strcpy((yyval.a_symbol).type, "int");	(yyval.a_symbol).place = genPlace(); (yyval.a_symbol).code = InstrList_create(); if( !errorOccured ) codeGenLoadInt((yyval.a_symbol).code, (yyval.a_symbol).place, (yyvsp[(1) - (1)].a_int)); }
    break;

  case 74:
/* Line 1787 of yacc.c  */
#line 569 "cminus.y"
    { strcpy((yyval.a_symbol).type, "int");	(yyval.a_symbol).place = genPlace(); (yyval.a_symbol).code = InstrList_create(); if( !errorOccured ) codeGenLoadInt((yyval.a_symbol).code, (yyval.a_symbol).place, (yyvsp[(1) - (1)].a_int)); }
    break;

  case 75:
/* Line 1787 of yacc.c  */
#line 570 "cminus.y"
    { strcpy((yyval.a_symbol).type, "float"); (yyval.a_symbol).place = genPlace(); (yyval.a_symbol).code = InstrList_create(); if( !errorOccured ) codeGenLoadFloat((yyval.a_symbol).code, (yyval.a_symbol).place, (yyvsp[(1) - (1)].a_float)); }
    break;

  case 76:
/* Line 1787 of yacc.c  */
#line 571 "cminus.y"
    { strcpy((yyval.a_symbol).type, (yyvsp[(1) - (1)].a_symbol).type); (yyval.a_symbol).place = (yyvsp[(1) - (1)].a_symbol).place; (yyval.a_symbol).code = (yyvsp[(1) - (1)].a_symbol).code; }
    break;

  case 77:
/* Line 1787 of yacc.c  */
#line 572 "cminus.y"
    { strcpy((yyval.a_symbol).type, (yyvsp[(1) - (1)].a_symbol).type); (yyval.a_symbol).place = (yyvsp[(1) - (1)].a_symbol).place; (yyval.a_symbol).code = (yyvsp[(1) - (1)].a_symbol).code; }
    break;

  case 78:
/* Line 1787 of yacc.c  */
#line 573 "cminus.y"
    { (yyval.a_symbol).place = (yyvsp[(1) - (1)].a_symbol).place; (yyval.a_symbol).code = (yyvsp[(1) - (1)].a_symbol).code; }
    break;

  case 79:
/* Line 1787 of yacc.c  */
#line 577 "cminus.y"
    {
	if( !errorOccured )
	{
		(yyval.a_symbol).code = InstrList_create();
		(yyval.a_symbol).place = genPlace();
		strcpy((yyval.a_symbol).type, "int");
		codeGenReadInt((yyval.a_symbol).code, (yyval.a_symbol).place);
	}
}
    break;

  case 80:
/* Line 1787 of yacc.c  */
#line 590 "cminus.y"
    {
	const Symbol *s = functionCall((yyval.a_symbol).type, (yyvsp[(1) - (4)].a_string));
	
	if( !errorOccured )
	{
		(yyval.a_symbol).code = InstrList_create();

		// push params into stack/registers whatever
		InstrList_concat((yyval.a_symbol).code, (yyvsp[(3) - (4)].a_symbol).code);
		
		(yyval.a_symbol).place = genPlace();
		
		codeGenFuncCall((yyval.a_symbol).code, s, (yyval.a_symbol).place);
		
		uint32_t paramsToPop = InstrList_count((yyvsp[(3) - (4)].a_symbol).code, INSTR_FUNC_PARAM_PUSH);
		if( paramsToPop != 0 )
			codeGenPopParams((yyval.a_symbol).code, paramsToPop); // pop $3.code->length params. THAT'S NOT THE SIZE IN BYTES
		
		InstrList_destroy((yyvsp[(3) - (4)].a_symbol).code);
	}
}
    break;

  case 81:
/* Line 1787 of yacc.c  */
#line 612 "cminus.y"
    { }
    break;

  case 82:
/* Line 1787 of yacc.c  */
#line 617 "cminus.y"
    {
	const Symbol *s = ufcs((yyval.a_symbol).type, (yyvsp[(1) - (6)].a_symbol).type, (yyvsp[(3) - (6)].a_string));

	if( !errorOccured )
	{
		(yyval.a_symbol).code = InstrList_create();
		
		// push params into stack/register whatever
		InstrList_concat((yyval.a_symbol).code, (yyvsp[(5) - (6)].a_symbol).code);
		InstrList_concat((yyval.a_symbol).code, (yyvsp[(1) - (6)].a_symbol).code);
		codeGenPushParam((yyval.a_symbol).code, (yyvsp[(1) - (6)].a_symbol).place);
		
		(yyval.a_symbol).place = genPlace(); // where to put the result
		
		codeGenFuncCall((yyval.a_symbol).code, s, (yyval.a_symbol).place);
		
		uint32_t paramsToPop = InstrList_count((yyvsp[(5) - (6)].a_symbol).code, INSTR_FUNC_PARAM_PUSH) + 1; // +1 for ufcs first parameter
		if( paramsToPop != 0 )
			codeGenPopParams((yyval.a_symbol).code, paramsToPop);
		
		InstrList_destroy((yyvsp[(5) - (6)].a_symbol).code);
		InstrList_destroy((yyvsp[(1) - (6)].a_symbol).code);
	}
}
    break;

  case 83:
/* Line 1787 of yacc.c  */
#line 644 "cminus.y"
    {
	property((yyval.a_symbol).type, (yyvsp[(1) - (3)].a_symbol).type, (yyvsp[(3) - (3)].a_string));
	
	if( !errorOccured )
	{
		(yyval.a_symbol).code = InstrList_create();
		(yyval.a_symbol).place = genPlace();
		codeGenProperty((yyval.a_symbol).code, (yyvsp[(1) - (3)].a_symbol).type, (yyvsp[(3) - (3)].a_string), (yyval.a_symbol).place, (yyvsp[(1) - (3)].a_symbol).place - 1);
		InstrList_destroy((yyvsp[(1) - (3)].a_symbol).code);
	}
}
    break;

  case 84:
/* Line 1787 of yacc.c  */
#line 656 "cminus.y"
    {
	property((yyval.a_symbol).type, (yyvsp[(1) - (3)].a_string), (yyvsp[(3) - (3)].a_string));
	if( !errorOccured )
	{
		(yyval.a_symbol).code = InstrList_create();
		(yyval.a_symbol).place = genPlace();
		codeGenProperty((yyval.a_symbol).code, (yyvsp[(1) - (3)].a_string), (yyvsp[(3) - (3)].a_string), (yyval.a_symbol).place, UINT32_MAX);
	}
}
    break;

  case 85:
/* Line 1787 of yacc.c  */
#line 667 "cminus.y"
    { if( !errorOccured ) (yyval.a_symbol).code = InstrList_create(); }
    break;

  case 86:
/* Line 1787 of yacc.c  */
#line 668 "cminus.y"
    { if( !errorOccured ) (yyval.a_symbol).code = (yyvsp[(1) - (1)].a_symbol).code; }
    break;

  case 87:
/* Line 1787 of yacc.c  */
#line 671 "cminus.y"
    {
												StrVec_insert(paramTypesVecCall, (yyvsp[(3) - (3)].a_symbol).type);
											
												(yyval.a_symbol).code = (yyvsp[(3) - (3)].a_symbol).code;
												
												if( !errorOccured )
												{
													codeGenPushParam((yyval.a_symbol).code, (yyvsp[(3) - (3)].a_symbol).place);
													InstrList_concat((yyval.a_symbol).code, (yyvsp[(1) - (3)].a_symbol).code);
													InstrList_destroy((yyvsp[(1) - (3)].a_symbol).code);
												}
											}
    break;

  case 88:
/* Line 1787 of yacc.c  */
#line 683 "cminus.y"
    {
												StrVec_insert(paramTypesVecCall, (yyvsp[(1) - (1)].a_symbol).type);
												
												(yyval.a_symbol).code = (yyvsp[(1) - (1)].a_symbol).code;
												if( !errorOccured ) codeGenPushParam((yyval.a_symbol).code, (yyvsp[(1) - (1)].a_symbol).place);
											}
    break;

  case 89:
/* Line 1787 of yacc.c  */
#line 689 "cminus.y"
    { yyerror("missing expression after ‘,’"); }
    break;


/* Line 1787 of yacc.c  */
#line 2487 "cminus.tab.c"
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2050 of yacc.c  */
#line 691 "cminus.y"

