%{
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
%}

%union
{
	SymbolInfo a_symbol;
	
	char a_string[1000];
	int a_int;
	float a_float;
}

%start program

%token <a_int> UINT_LITERAL INT_LITERAL
%token <a_float> FLOAT_LITERAL
%token <a_string> STRING_LITERAL

%token <a_string> TOKEN_ID TOKEN_COMMA TOKEN_GE TOKEN_LE TOKEN_LESS TOKEN_GREATER TOKEN_EQUALS TOKEN_NE TOKEN_SEMICOLON TOKEN_R_BRACKET TOKEN_L_BRACKET TOKEN_DOT
TOKEN_L_PAREN TOKEN_R_PAREN TOKEN_L_BRACE TOKEN_R_BRACE TOKEN_ASSIGN TOKEN_ADD TOKEN_SUB TOKEN_MUL TOKEN_DIV TOKEN_REM TOKEN_WRITELN TOKEN_READ_INT

// keywords
TOKEN_INT TOKEN_FLOAT TOKEN_VOID TOKEN_IF TOKEN_ELSE TOKEN_RETURN TOKEN_WHILE TOKEN_TYPEOF TOKEN_PRAGMA

%type <a_string> addop mulop type_specifier relop
%type <a_symbol> var factor term expression additive_expression simple_expression return_stmt expression_stmt var_declaration statement
	statement_list call arg_list args compound_stmt fun_declaration declaration declaration_list ufcs selection_stmt iteration_stmt
	property params fun_params writeln_stmt read_int_stmt

%%
program: declaration_list
{
	//printf("--- program ---\n");
	//InstrList_print($1.code);
	
	threeCodes = $1.code;
}
	;

declaration_list: declaration_list declaration	{ if( !errorOccured ) { $$.code = InstrList_create(); InstrList_concat($$.code, $1.code); InstrList_concat($$.code, $2.code); } }
				| declaration					{ $$.code = $1.code; }
				
declaration	: var_declaration	{ $$.code = $1.code; }
			| fun_declaration	{ $$.code = $1.code; }
	;
	
var_declaration	: type_specifier TOKEN_ID TOKEN_SEMICOLON
{
	$$.code = InstrList_create();
	
	Symbol *s = varDeclaration($1, $2, 0);
	if( s != NULL && !errorOccured )
	{
		if( strcmp(s->type, "int") == 0 )
			codeGenLoadInt($$.code, s->place, 0);
		else if( strcmp(s->type, "float") == 0 )
			codeGenLoadFloat($$.code, s->place, NAN);
	}
}
| type_specifier TOKEN_ID TOKEN_L_BRACKET UINT_LITERAL TOKEN_R_BRACKET TOKEN_SEMICOLON
{
	$$.code = InstrList_create();
	
	char buffer[1000];
	strcpy(buffer, $1);
	strcat(buffer, "[]");
	
	//printf("var_declaration type: %s\n", buffer);
	Symbol *s = varDeclaration(buffer, $2, $4);
	
	if( s != NULL )
	{
		uint32_t place = s->place; // get its place to put the length into it. we'll make a new place for the arrays address
		
		//printf("place = %u\n", place);
		
		if( !errorOccured )
		{
			codeGenLoadInt($$.code, place, $4); // the size of the array is stored at the beginning
			
			if( strcmp(s->type, "int[]") == 0 )
			{
				uint32_t i;
				
				s->place = genPlace();
				codeGenLoadInt($$.code, s->place, 0); 	// load the value at the 1st address
				
				for(i = 1; i < $4; ++i)				// load the rest
					codeGenLoadInt($$.code, genPlace(), 0);
			}
		}
	}
}
				| type_specifier error TOKEN_SEMICOLON								{ char buffer[100]; sprintf(buffer, "expecting identifier"); yyerror(buffer); }
				| type_specifier TOKEN_ID TOKEN_ASSIGN error TOKEN_SEMICOLON		{ char buffer[100]; sprintf(buffer, "C- disallows variable declaration and assignment at the same time. Use %s %s; %s = ...", $1, $2, $2); yyerror(buffer); }
	;
	
type_specifier	: TOKEN_INT				{ /*printf("type_specifier -> %s\n", $1);*/ }
				| TOKEN_FLOAT			{ /*printf("type_specifier -> %s\n", $1);*/ }
				| TOKEN_VOID			{ /*printf("type_specifier -> %s\n", $1);*/ }
				| TOKEN_TYPEOF TOKEN_L_PAREN TOKEN_ID TOKEN_R_PAREN	{ inferTypeOfIdentifier($$, $3); }
	;

fun_declaration : type_specifier TOKEN_ID TOKEN_L_PAREN fun_params TOKEN_R_PAREN compound_stmt
		{
			Symbol *func = funcDeclaration($1, $2, paramTypesVec, 0);
			
			destroyCurrentScope();
			
			if( !errorOccured )
			{
				$$.code = InstrList_create();
				codeGenFuncLabel($$.code, func);
				InstrList_concat($$.code, $4.code);
				InstrList_concat($$.code, $6.code);
				InstrList_destroy($6.code);
				
				if( strcmp($$.type, "void") == 0 )
				{
					assert($$.code->head && "$$.code->head is null");
					
					InstructionNode *p = $$.code->head;
					while( p->next )
						p = p->next;
					if( p->instrType != INSTR_RET )
						codeGenReturn($$.code, "void", 0);
				}
			}
			
			
			resetPlace(); // reset place counter to 0
		}
	;
	
	
// fun_params exists so that the parameters will be check before the compound_stmt of fun_declaration
fun_params: params
				{
					functionBraceCount = 1;
					
					SymbolTable *st;
					size_t i;
					
					createNewScope();
					st = symbolTable;
					
					for(i = 0; i < paramTypesVec->length; ++i)
						varDeclaration(paramTypesVec->t[i], paramNamesVec->t[i], 0);

					$$.code = $1.code;
				}
	;
	
params	: param_list					{ if( !errorOccured ) { $$.code = InstrList_create(); codeGenFirstArgPlace($$.code); } }
		| TOKEN_VOID					{ if( !errorOccured ) $$.code = InstrList_create(); }
		|								{ if( !errorOccured ) $$.code = InstrList_create(); }
	;
	
param_list	: param_list TOKEN_COMMA param		{ }
			| param								{ }
			| param_list TOKEN_COMMA error		{ yyerror("expected parameter after ‘,’"); }
	;

param: type_specifier TOKEN_ID
{
	if( strcmp($1, "void") == 0 )
	{
		yyerror("\"void\" cannot be used as a type for a variable");
	}
	else
	{
		StrVec_insert(paramTypesVec, $1);
		StrVec_insert(paramNamesVec, $2);
		//printf("Normal parameter %s %s!\n", $1, $2);
	}
}
		| type_specifier TOKEN_ID TOKEN_L_BRACKET TOKEN_R_BRACKET	{ char buff[100]; if( strcmp($1, "void") == 0 ) { yyerror("\"void\" cannot be used as a type for a variable"); } else { sprintf(buff, "%s[]", $1); StrVec_insert(paramTypesVec, buff); StrVec_insert(paramNamesVec, $2); printf("Array parameter(1)\n"); } sprintf(buff, "%s[]", $1); }
		| type_specifier TOKEN_L_BRACKET TOKEN_R_BRACKET TOKEN_ID	{ char buff[100]; if( strcmp($1, "void") == 0 ) { yyerror("\"void\" cannot be used as a type for a variable"); } else { sprintf(buff, "%s[]", $1); StrVec_insert(paramTypesVec, buff); StrVec_insert(paramNamesVec, $4); printf("Array parameter(2)\n"); } sprintf(buff, "%s[]", $1); }
		| type_specifier TOKEN_ID TOKEN_L_BRACKET error				{ char buffer[100]; sprintf(buffer, "error after ‘%s %s[’", $1, $2); yyerror(buffer); }
		| type_specifier TOKEN_L_BRACKET error TOKEN_ID				{ char buffer[100]; sprintf(buffer, "error after ‘%s[’", $1); yyerror(buffer); }
	;

compound_stmt: TOKEN_L_BRACE /*local_declarations*/ statement_list TOKEN_R_BRACE	{ $$.code = $2.code; }
	;
	
/*local_declarations:
					| local_declarations var_declaration
	;*/
	
statement_list:							{ if( !errorOccured ) $$.code = InstrList_create(); }
			| statement_list statement	{ if( !errorOccured ) { InstrList_concat($$.code, $2.code); InstrList_destroy($2.code); } }
	;
	
statement	: expression_stmt	{ $$.code = $1.code; }
			| compound_stmt		{ $$.code = $1.code; }
			| selection_stmt	{ $$.code = $1.code; }
			| iteration_stmt	{ $$.code = $1.code; }
			| return_stmt		{ $$.code = $1.code; }
			| var_declaration	{ $$.code = $1.code; }
			| writeln_stmt		{ $$.code = $1.code; }
	;

writeln_stmt: TOKEN_WRITELN TOKEN_L_PAREN simple_expression TOKEN_R_PAREN TOKEN_SEMICOLON	{ $$.code = $3.code; codeGenWriteln($$.code, $3.type, $3.place); }
	;

expression_stmt	: expression TOKEN_SEMICOLON	{ if( !errorOccured ) { $$.code = InstrList_create(); InstrList_concat($$.code, $1.code); InstrList_destroy($1.code); } }
				| TOKEN_PRAGMA TOKEN_L_PAREN TOKEN_ID TOKEN_COMMA STRING_LITERAL TOKEN_R_PAREN TOKEN_SEMICOLON { $$.code = InstrList_create(); pragmaString($3, $5); }
	;

// #15
selection_stmt	: TOKEN_IF TOKEN_L_PAREN simple_expression TOKEN_R_PAREN statement					
{
	if( strcmp($3.type, "int") != 0 )
	{
		char buffer[1000];
		sprintf(buffer, "condition of \"if\" statement must be integral, not %s", $3.type);
		yyerror(buffer);
	}
	
	if( !errorOccured )
	{
		$$.code = InstrList_create();
		$$.after = genLabel(); // $$.begin isn't need for "if" statements
		InstrList_concat($$.code, $3.code);
		
		codeGenIfNot($$.code, $$.after, $3.place);
		InstrList_concat($$.code, $5.code);
		codeGenLabel($$.code, $$.after);
		
		InstrList_destroy($3.code);
		InstrList_destroy($5.code);
	}
	
}
| TOKEN_IF TOKEN_L_PAREN simple_expression TOKEN_R_PAREN statement TOKEN_ELSE statement
{
	if( strcmp($3.type, "int") != 0 )
	{
		char buffer[1000];
		sprintf(buffer, "condition of \"if\" statement must be integral, not %s", $3.type);
		yyerror(buffer);
	}
	
	if( !errorOccured )
	{
		$$.code = InstrList_create();
		$$.after = genLabel(); // $$.begin isn't need for "if" statements
		
		// generate a label for jumping to when the "if" is finished
		// (needed because else the code would execute "if" and "else" as well)
		uint32_t afterElseLabel = genLabel();
		codeGenUnconditionalJump($5.code, afterElseLabel);
		
		InstrList_concat($$.code, $3.code);
		
		codeGenIfNot($$.code, $$.after, $3.place);
		InstrList_concat($$.code, $5.code);
		
		
		codeGenLabel($$.code, $$.after);
		InstrList_concat($$.code, $7.code);
		codeGenLabel($$.code, afterElseLabel);
		
		InstrList_destroy($3.code);
		InstrList_destroy($5.code);
		InstrList_destroy($7.code);
	}
}
	;

// # 16
iteration_stmt	: TOKEN_WHILE TOKEN_L_PAREN expression TOKEN_R_PAREN statement
{
	if( strcmp($3.type, "int") != 0 )
	{
		char buffer[1000];
		sprintf(buffer, "condition of \"while\" statement must be integral, not %s", $3.type);
		yyerror(buffer);
	}
	
	if( !errorOccured )
	{
		$$.code = InstrList_create();
		$$.begin = genLabel();
		$$.after = genLabel();
		
		codeGenLabel($$.code, $$.begin);
		InstrList_concat($$.code, $3.code);
		codeGenWhileNot($$.code, $$.begin, $$.after, $3.place);
		InstrList_concat($$.code, $5.code);
		codeGenUnconditionalJump($$.code, $$.begin);
		codeGenLabel($$.code, $$.after);
		
		InstrList_destroy($3.code);
		InstrList_destroy($5.code);
	}
	
}
	| TOKEN_WHILE TOKEN_L_PAREN error TOKEN_R_PAREN					{ yyclearin; yyerror("wrong while stament"); }
	;

// # 17
return_stmt: TOKEN_RETURN TOKEN_SEMICOLON				{
															returnStatement("void");
															if( !errorOccured )
															{
																$$.code = InstrList_create();
																codeGenReturn($$.code, "void", UINT32_MAX);
															}
															
														}
		| TOKEN_RETURN expression TOKEN_SEMICOLON		{
															returnStatement($2.type);
															
															$$.code = $2.code;
															if( !errorOccured ) codeGenReturn($$.code, $2.type, $2.place);
															
														}
			| TOKEN_RETURN error TOKEN_SEMICOLON		{ yyerror("error after \"return\""); }
	;
	
expression:	var TOKEN_ASSIGN expression
{
	// if the types are not compatible
	if( strcmp($1.type, $3.type) != 0 )
	{
		if( strcmp($1.type, TYPE_ERROR) != 0 && strcmp($3.type, TYPE_ERROR) != 0 )
		{
			char buffer[1000];
			sprintf(buffer, "incompatible types \"%s\" and \"%s\"", $1.type, $3.type);
			yyerror(buffer);
		}
		strcpy($$.type, TYPE_ERROR);
	}
	else
	{
		strcpy($$.type, $1.type);
		$$.place = $1.place;
		
		if( !errorOccured )
		{
			$$.code = InstrList_create();
			InstrList_concat($$.code, $1.code);
			InstrList_concat($$.code, $3.code);
		
			codeGenAssign($$.code, $3.type, $1.place, $3.place);
			
			InstrList_destroy($1.code);
			InstrList_destroy($3.code);
		}
	}
}
										
			| simple_expression			{ strcpy($$.type, $1.type); $$.place = $1.place; $$.code = $1.code; }
	;

var: TOKEN_ID
{
	SymbolArray *s = SymbolTable_find(symbolTable, $1, SEARCH_ALL_PARENTS);
	if( s->length == 0 )
	{
		char buffer[1000];
		sprintf(buffer, "undeclared variable \"%s\"", $1);
		yyerror(buffer);
		strcpy($$.type, TYPE_ERROR);
	}
	else
	{
		strcpy($$.type,s->symbols[0]->type);
		$$.place = s->symbols[0]->place;
		$$.code = InstrList_create();
	}
	
	free(s);
}
						
| TOKEN_ID TOKEN_L_BRACKET expression TOKEN_R_BRACKET
{
	SymbolArray *s = SymbolTable_find(symbolTable, $1, SEARCH_ALL_PARENTS);
	if( s->length == 0 )
	{
		char buffer[1000];
		sprintf(buffer, "undeclared array \"%s\"", $1);
		yyerror(buffer);
		strcpy($$.type, TYPE_ERROR);
	}
	else if( strcmp($3.type, "int") != 0 )
	{
		char buffer[1000];
		sprintf(buffer, "array index must be an integral value, not %s", $3.type);
		yyerror(buffer);
		strcpy($$.type, TYPE_ERROR);
	}
	else
	{
		Symbol *symbol = s->symbols[0];
		
		char *type = (char*)malloc(sizeof(char) * (strlen(symbol->type) + 1));
		strcpy(type, symbol->type);
		removeChar(type, '['); // remove the brackets get the contained type
		removeChar(type, ']');	// e.g int[] will become int
		strcpy($$.type, type);
		
		free(type);
		
		if( !errorOccured )
		{
			$$.code = InstrList_create();
			InstrList_concat($$.code, $3.code);
			
			$$.place = genPlace();
			
			codeGenLoadFromOffset($$.code, $$.type, $$.place, symbol->place, $3.place);
			
			InstrList_destroy($3.code);
		}
	}

	free(s);
}
	;
	
simple_expression: additive_expression relop additive_expression
	{
		opBinary(&$1, &$3, "<", &$$);
		
		if( !errorOccured )
		{
			$$.place = genPlace();
			InstrList_concat($$.code, $3.code);
			
			$$.code = $1.code;
			
			if( strcmp($2, "<") == 0 )
				codeGenComparisonOp($$.code, $$.type, INSTR_LESS, $$.place, $1.place, $3.place);
			else if( strcmp($2, "<=") == 0 )
				codeGenComparisonOp($$.code, $$.type, INSTR_LESS_EQUAL, $$.place, $1.place, $3.place);
			else if( strcmp($2, "==") == 0 )
				codeGenComparisonOp($$.code, $$.type, INSTR_EQUAL, $$.place, $1.place, $3.place);
			else if( strcmp($2, "!=") == 0 )
				codeGenComparisonOp($$.code, $$.type, INSTR_NOT_EQUAL, $$.place, $1.place, $3.place);
			else if( strcmp($2, ">") == 0 )
				codeGenComparisonOp($$.code, $$.type, INSTR_GREATER, $$.place, $1.place, $3.place);
			else if( strcmp($2, ">=") == 0 )
				codeGenComparisonOp($$.code, $$.type, INSTR_GREATER_EQUAL, $$.place, $1.place, $3.place);
			else
			{
				assert(0 && "simple_expr -> additive_expr relop additive_expr: relop is not valid");
			}
				
				
			InstrList_destroy($3.code);
		}
	}
	
	| additive_expression
	{
		strcpy($$.type, $1.type);
		$$.place = $1.place;
		$$.code = $1.code;
	}
	;
	
relop: TOKEN_GE
	| TOKEN_LESS
	| TOKEN_GREATER
	| TOKEN_LE
	| TOKEN_EQUALS
	| TOKEN_NE
	;
	
additive_expression: additive_expression addop term 	
			{
				opBinary(&$1, &$3, "+", &$$); // + or - doesn't matter
				
				if( !errorOccured )
				{
					$$.place = genPlace();
					$$.code = InstrList_create();
					
					InstrList_concat($$.code, $1.code);
					InstrList_concat($$.code, $3.code);
					
					if( strcmp($2, "+") == 0 )
						codeGenAdd($$.code, $$.type, $$.place, $1.place, $3.place);
					else // subtraction here
						codeGenSub($$.code, $$.type, $$.place, $1.place, $3.place);
						
					// do some cleanup like good programmers we are
					InstrList_destroy($1.code);
					InstrList_destroy($3.code);
				}
			}
| term		{
				strcpy($$.type, $1.type);
				$$.place = $1.place;
				$$.code = $1.code;
			}
| additive_expression addop error	{ yyerror("expression missing term"); } // error handling
	;

addop: TOKEN_ADD		{}
	| TOKEN_SUB			{}
	;

//----------------------------------------------- TERM -------------------------------------------------------------------
term: term mulop factor	{
							opBinary(&$1, &$3, $2, &$$);
							
							if( !errorOccured )
							{
								$$.place = genPlace();
								$$.code = InstrList_create();
								
								InstrList_concat($$.code, $1.code);
								InstrList_concat($$.code, $3.code);
								
								if( strcmp($2, "*") == 0 )		codeGenMul($$.code, $$.type, $$.place, $1.place, $3.place);
								else if( strcmp($2, "/") == 0 )	codeGenDiv($$.code, $$.type, $$.place, $1.place, $3.place);
								else							codeGenRem($$.code, $$.type, $$.place, $1.place, $3.place); // % operator
								
								InstrList_destroy($1.code);
								InstrList_destroy($3.code);
							}
						}
	| factor			{ strcpy($$.type, $1.type); $$.place = $1.place; $$.code = $1.code; }
	;
//---------------------------------------------- mul op --------------------------------------------------------------------
mulop: TOKEN_MUL
	| TOKEN_DIV
	| TOKEN_REM // remainder
	;

factor: TOKEN_L_PAREN expression TOKEN_R_PAREN	{ strcpy($$.type, $2.type); $$.place = $2.place; $$.code = $2.code; }
	| var										{ strcpy($$.type, $1.type); $$.place = $1.place; $$.code = $1.code; }
	| call										{ strcpy($$.type, $1.type);	$$.place = $1.place; $$.code = $1.code; }
	| UINT_LITERAL								{ strcpy($$.type, "int");	$$.place = genPlace(); $$.code = InstrList_create(); if( !errorOccured ) codeGenLoadInt($$.code, $$.place, $1); }
	| INT_LITERAL								{ strcpy($$.type, "int");	$$.place = genPlace(); $$.code = InstrList_create(); if( !errorOccured ) codeGenLoadInt($$.code, $$.place, $1); }
	| FLOAT_LITERAL								{ strcpy($$.type, "float"); $$.place = genPlace(); $$.code = InstrList_create(); if( !errorOccured ) codeGenLoadFloat($$.code, $$.place, $1); }
	| ufcs										{ strcpy($$.type, $1.type); $$.place = $1.place; $$.code = $1.code; }
	| property									{ strcpy($$.type, $1.type); $$.place = $1.place; $$.code = $1.code; }
	| read_int_stmt								{ $$.place = $1.place; $$.code = $1.code; }
	;
	
read_int_stmt: TOKEN_READ_INT TOKEN_L_PAREN TOKEN_R_PAREN
{
	if( !errorOccured )
	{
		$$.code = InstrList_create();
		$$.place = genPlace();
		strcpy($$.type, "int");
		codeGenReadInt($$.code, $$.place);
	}
}
;
	
//--------------------------------------------- FUNCTION CALL -------------------------------------------------------------
call: TOKEN_ID TOKEN_L_PAREN args TOKEN_R_PAREN	
{
	const Symbol *s = functionCall($$.type, $1);
	
	if( !errorOccured )
	{
		$$.code = InstrList_create();

		// push params into stack/registers whatever
		InstrList_concat($$.code, $3.code);
		
		$$.place = genPlace();
		
		codeGenFuncCall($$.code, s, $$.place);
		
		uint32_t paramsToPop = InstrList_count($3.code, INSTR_FUNC_PARAM_PUSH);
		if( paramsToPop != 0 )
			codeGenPopParams($$.code, paramsToPop); // pop $3.code->length params. THAT'S NOT THE SIZE IN BYTES
		
		InstrList_destroy($3.code);
	}
}
		
	| TOKEN_ID TOKEN_L_PAREN error TOKEN_R_PAREN	{ }
	;

//---------------------------------------------- UFCS ---------------------------------------------------------------------
ufcs: factor TOKEN_DOT TOKEN_ID TOKEN_L_PAREN args TOKEN_R_PAREN
{
	const Symbol *s = ufcs($$.type, $1.type, $3);

	if( !errorOccured )
	{
		$$.code = InstrList_create();
		
		// push params into stack/register whatever
		InstrList_concat($$.code, $5.code);
		InstrList_concat($$.code, $1.code);
		codeGenPushParam($$.code, $1.place);
		
		$$.place = genPlace(); // where to put the result
		
		codeGenFuncCall($$.code, s, $$.place);
		
		uint32_t paramsToPop = InstrList_count($5.code, INSTR_FUNC_PARAM_PUSH) + 1; // +1 for ufcs first parameter
		if( paramsToPop != 0 )
			codeGenPopParams($$.code, paramsToPop);
		
		InstrList_destroy($5.code);
		InstrList_destroy($1.code);
	}
}
	;

property: factor TOKEN_DOT TOKEN_ID
{
	property($$.type, $1.type, $3);
	
	if( !errorOccured )
	{
		$$.code = InstrList_create();
		$$.place = genPlace();
		codeGenProperty($$.code, $1.type, $3, $$.place, $1.place - 1);
		InstrList_destroy($1.code);
	}
}
| type_specifier TOKEN_DOT TOKEN_ID
{
	property($$.type, $1, $3);
	if( !errorOccured )
	{
		$$.code = InstrList_create();
		$$.place = genPlace();
		codeGenProperty($$.code, $1, $3, $$.place, UINT32_MAX);
	}
}
	;

args:			{ if( !errorOccured ) $$.code = InstrList_create(); }
	| arg_list	{ if( !errorOccured ) $$.code = $1.code; }
	;
	
arg_list: arg_list TOKEN_COMMA expression	{
												StrVec_insert(paramTypesVecCall, $3.type);
											
												$$.code = $3.code;
												
												if( !errorOccured )
												{
													codeGenPushParam($$.code, $3.place);
													InstrList_concat($$.code, $1.code);
													InstrList_destroy($1.code);
												}
											}
	| expression							{
												StrVec_insert(paramTypesVecCall, $1.type);
												
												$$.code = $1.code;
												if( !errorOccured ) codeGenPushParam($$.code, $1.place);
											}
	| arg_list TOKEN_COMMA error			{ yyerror("missing expression after ‘,’"); }
	;
%%
