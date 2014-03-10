/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison interface for Yacc-like parsers in C
   
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
/* Line 2053 of yacc.c  */
#line 36 "cminus.y"

	SymbolInfo a_symbol;
	
	char a_string[1000];
	int a_int;
	float a_float;


/* Line 2053 of yacc.c  */
#line 105 "cminus.tab.h"
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
