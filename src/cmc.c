#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "symboltable.h"
#include "symbol.h"
#include "strvec.h"
#include "intvec.h"
#include "util.h"
#include "cminus.tab.h"
#include "three-code-helper.h"

extern FILE *yyin;

SymbolTable *symbolTable;		// the global symbol table

StrVec *paramTypesVec;			// string vector used for function parameter types DECLARATIONS
StrVec *paramNamesVec;			// string vector used for the names of function parameters

StrVec *paramTypesVecCall;		// string vector used for function parameter CALLING! (not declaring)

StrVec *localIdentifiers;		// holds the names of local declarations. used to test them with function arguments
IntVec *localIdentifierLines;	// line of declaration

StrVec *returnTypes;			// types returned in a function. e.g "return 5" will store "int"
IntVec *returnTypesDepths;		// depths of the "return(s)"
IntVec *returnTypesLines;		// line of type returned

int functionBraceCount = 0;		// braces found in function declaration

InstructionList *threeCodes;

bool errorOccured = false;		// has an error occured?

/// returns 1 if symbol is an array / returns an array, 0 othersize
int isArray(const Symbol *symbol);

/// declares a variable or array
Symbol* varDeclaration(const char *type, const char *name, size_t len);

/// declares a function
Symbol* funcDeclaration(const char *returnType, const char *name, StrVec *paramTypesVec, size_t len);

/// Compares two functions and returns 1 if they have the same argument types
int funCmp(const Symbol *f1, const Symbol *f2);

/// creates a new symbol table and set the old one as its parent
void createNewScope();

/// destroys the current symbol table and set its parent as the current one
void destroyCurrentScope();

/// binary operators
void opBinary(const SymbolInfo *t1, const SymbolInfo *t2, const char *op, SymbolInfo *resultType);

/// function call
const Symbol* functionCall(char *resultType, const char *id);

/// universal function call syntax with an expression (simple_expression) at the left of the dot
const Symbol* ufcs(char *resultType, const char *type, const char *func);

/// when a "return" is found in a function, save it so we can test later if it matches the
/// function's return type. The check happens inside funcDeclaration()
void returnStatement(const char *type);

/// checks if the "returns" in the given function match the its return type
/// the data for the returns are in returnTypes, returnTypesDepths and returnTypesLines
void checkFunctionReturns(const Symbol *func);

/// infers the type of id and store it result. If id was not declared, TYPE_ERROR ise put into result
void inferTypeOfIdentifier(char *result, const char *id);

/// accepts a compiler pragma and does something with it
void pragmaString(const char *pragmaType, const char *command);

/// generate assembly for x86
void genAssemlby_x86(const InstructionList *l, FILE *f);

int main(int argc, char **argv)
{
	if( argc != 3 )
	{
		fprintf(stderr, "Usage: cmc FILE EXECUTABLE_NAME\n");
		exit(1);
	}
	
	// init
	symbolTable = SymbolTable_create();
	
	paramTypesVec = StrVec_create();
	paramNamesVec = StrVec_create();
	
	paramTypesVecCall = StrVec_create();
	
	localIdentifiers = StrVec_create();
	localIdentifierLines = IntVec_create();
	
	returnTypes = StrVec_create();
	returnTypesDepths = IntVec_create();
	returnTypesLines = IntVec_create();
	
	yyin = fopen(argv[1], "r");
	
	// run
	yyparse();
	
	// de-allocate
	StrVec_destroy(paramTypesVec);
	StrVec_destroy(paramTypesVecCall);
	StrVec_destroy(paramNamesVec);
	StrVec_destroy(localIdentifiers);
	IntVec_destroy(localIdentifierLines);
	StrVec_destroy(returnTypes);
	IntVec_destroy(returnTypesDepths);
	IntVec_destroy(returnTypesLines);
	
	SymbolTable_destroy(symbolTable);
	
	if( !errorOccured )
	{
		char buffer[1000];
		sprintf(buffer, "%s__tmp.s", argv[1]);
		FILE *output = fopen(buffer, "w");
		
		// generate assembly
		genAssemlby_x86(threeCodes, output);
		fclose(output);
	
		char commandBuffer[1000];
		sprintf(commandBuffer, "gcc %s -o %s -m32", buffer, argv[2]);
		FILE *pipe = popen(commandBuffer, "w");
		fclose(pipe);
		
		//remove(buffer); // remove the generated file
		
	}
}

int isArray(const Symbol *symbol)
{
	assert(symbol && "symbol is null");
	assert(symbol->type && "symbol->type is null");
	
	size_t len = strlen(symbol->type);
	
	return symbol->type[len-2] == '[' && symbol->type[len-1] == ']';
}

/// declares a variable or array
Symbol* varDeclaration(const char *type, const char *name, size_t len)
{
	Symbol *symbol = NULL;
	
	//printf("declaring variable %s %s in %p\n", type, name, symbolTable);
	
	// search for a variable/function with the same name
	// Note: Replace SEARCH_LOCAL_ONLY to SEARCH_ALL_PARENTS to disable shadow declarations
	SymbolArray *local = SymbolTable_find(symbolTable, name, SEARCH_LOCAL_ONLY);
	
	// go to global scope to check for functions with the same name
	SymbolTable *sb = symbolTable;
	while( sb->parent )
		sb = sb->parent;
	
	SymbolArray *global = SymbolTable_find(sb, name, SEARCH_LOCAL_ONLY); // local only or all parents is the same in this case
	
	if( strcmp(type, "void") == 0 ) // void types are not allowed for variables
	{
		yyerror("\"void\" cannot be a type for a variable");
		return;
	}
	
	// if there is no other symbol with the same name, it's ok
	if( local->length == 0 && global->length == 0 )
	{
		symbol = Symbol_create(SYMBOL_VARIABLE);
		
		Symbol_setType(symbol, type);
		Symbol_setName(symbol, name);
		symbol->len = len;
		symbol->place = genPlace();
		
		SymbolTable_insert(symbolTable, symbol);
		
		StrVec_insert(localIdentifiers, name);
		IntVec_insert(localIdentifierLines, getLineNo());
	}
	else
	{
		// if there is a local variable with the same name, it is an error
		if( local->length != 0 )
		{
			char buffer[1000], buffer2[1100];
			
			Symbol_toString(local->symbols[0], buffer);
			
			if( len == 0 )
				sprintf(buffer2, "%s %s: \"%s\" was declared earlier as \"%s\"", type, name, name, buffer);
			else
				sprintf(buffer2, "%s[%lu] %s: \"%s\" was declared earlier as \"%s\"", type, len, name, name, buffer);
		
			yyerror(buffer2);
		}
		// in global scope, it is an error only if the name matches a function name
		else
		{
			size_t i, ok = 1;
			char buffer[1000], buffer2[1100];
			
			for(i = 0; i < global->length && ok; ++i)
			{
				switch(global->symbols[i]->symbolType)
				{
				case SYMBOL_FUNCTION:
					Symbol_toString(global->symbols[i], buffer);
					
					if( len == 0 )
						sprintf(buffer2, "%s %s: \"%s\" was declared earlier as \"%s\"", type, name, name, buffer);
					else
						sprintf(buffer2, "%s[%lu] %s: \"%s\" was declared earlier as \"%s\"", type, len, name, name, buffer);
				
					yyerror(buffer2);
					ok = 0;
					break;
				}
			}
			
			if( ok )
			{
				symbol = Symbol_create(SYMBOL_VARIABLE);
		
				Symbol_setType(symbol, type);
				Symbol_setName(symbol, name);
				symbol->len = len;
				symbol->place = genPlace();
				
				SymbolTable_insert(symbolTable, symbol);
				
				StrVec_insert(localIdentifiers, name);
				IntVec_insert(localIdentifierLines, getLineNo());
				
				printf("^variable %s %s declared. place = %u\n", symbol->type, symbol->name, symbol->place);
			}
		}
	}
	
	free(local);
	free(global);
	
	return symbol;
}

Symbol* funcDeclaration(const char *returnType, const char *name, StrVec *paramTypesVec, size_t len)
{
	Symbol *symbol = NULL;
	
	// search for a variable/function with the same name
	//printf("in func declaration -- %p\n", symbolTable);
	
	SymbolArray *s = SymbolTable_find(symbolTable, name, SEARCH_ALL_PARENTS);
	
	// if the symbol has not been declared
	if( s->length == 0 )
	{
		symbol = Symbol_create(SYMBOL_FUNCTION);
		size_t i, j;
		
		// add the parameters of the function to it. those are saved in "st" (the symbol table of the function)
		for(i = 0; i < paramTypesVec->length; ++i)
			Symbol_addParam(symbol, paramTypesVec->t[i]);

		Symbol_setType(symbol, returnType);
		Symbol_setName(symbol, name);
		symbol->len = len;
		
		//Symbol_print(symbol, stdout);
		SymbolTable_insert(symbolTable->parent, symbol);
		checkFunctionReturns(symbol);
	}
	else // if the symbol HAS been declared
	{
		// construct the tested function
		uint64_t i;
		int ok = 1;
		
		symbol = Symbol_create(SYMBOL_FUNCTION);
		
		// add the parameters of the function to it. those are saved in "st" (the symbol table of the function)
		for(i = 0; i < paramTypesVec->length; ++i)
			Symbol_addParam(symbol, paramTypesVec->t[i]);
		
		Symbol_setType(symbol, returnType);
		Symbol_setName(symbol, name);
		symbol->len = len;
		
		for(i = 0; i < s->length; ++i)
		{
			// if a variable and the function have the same name,
			// it means that a local variable was declared with the same name. report an error
			if( s->symbols[i]->symbolType == SYMBOL_VARIABLE )
			{
				char sStr[500];
				char s2Str[500];
				char buffer[1000];
			
				Symbol_toString(s->symbols[i], sStr);
				Symbol_toString(symbol, s2Str);
			
				sprintf(buffer, "\"%s\" has been already declared as %s", sStr, s2Str);
				yyerror(buffer);
					
				ok = 0;
				break;
			}
			else
			{
				// if the two function don't have arguments of the same type, it's ok
				if( !funCmp(s->symbols[i], symbol) )
				{
				}
				else
				{
					char sStr[500];
					char buffer[1000];
				
					Symbol_toString(s->symbols[i], sStr);
				
					sprintf(buffer, "%s has been already declared", sStr);
					yyerror(buffer);
					
					ok = 0;
					break;
				}
			}
		}
	
		if( ok == 1 )
		{
			//Symbol_print(symbol, stdout);
			SymbolTable_insert(symbolTable->parent, symbol);
			checkFunctionReturns(symbol);
		}
	}
	
	free(s);
	
	StrVec_clear(paramTypesVec);
	StrVec_clear(paramNamesVec);
	
	StrVec_clear(localIdentifiers);
	IntVec_clear(localIdentifierLines);
	
	StrVec_clear(returnTypes);
	IntVec_clear(returnTypesDepths);
	IntVec_clear(returnTypesLines);
	
	functionBraceCount = 0;
	
	return symbol;
}

/**
 * compares the argument types of two functions
 * E.g:
 * void f(int x);
 * void f(int y);
 * @return 1 if corresponding types of the functions are the same
 * @return 0 otherwise
 */
int funCmp(const Symbol *f1, const Symbol *f2)
{
	assert(f1 && "f1 is null");
	assert(f2 && "f2 is null");
	assert(f1->symbolType == SYMBOL_FUNCTION && "f1 is not a function");
	assert(f2->symbolType == SYMBOL_FUNCTION && "f2 is not a function");
	
	// compare number of arguments first
	if( f1->numParams != f2->numParams )
		return 0;
	
	unsigned short i;
	
	// compare argument types
	for(i = 0; i < f1->numParams; ++i)
	{
		if( strcmp(f1->params[i], f2->params[i]) != 0 )
			return 0;
	}
	
	return 1;
}

void createNewScope()
{	
	SymbolTable *st = SymbolTable_create();	// create a new symbol table
	st->parent = symbolTable;				// set the current one as its parent
	symbolTable = st;						// set the current symbol table to the newly created one
	
	//printf("Creating new scope() : %p\n", st);
}

void destroyCurrentScope()
{
	//printf("Destroying current scope() : %p\n", symbolTable);
	
	SymbolTable *parent = symbolTable->parent;
	
	SymbolTable_destroy(symbolTable);
	symbolTable = parent;
}

void opBinary(const SymbolInfo *t1, const SymbolInfo *t2, const char *op, SymbolInfo *resultType)
{
	if( strcmp(t1->type, t2->type) != 0 )
	{
		char buffer[1000];
		sprintf(buffer, "incompatible types \"%s\" and \"%s\"", t1->type, t2->type);
		yyerror(buffer);
		strcpy(resultType->type, TYPE_ERROR);
	}
	else if( (strcmp(t1->type, "int") != 0 || strcmp(t2->type, "int") != 0) && strcmp(op, "%") == 0 )
	{
		yyerror("both types for \"%\" must be \"int\"");
		strcpy(resultType->type, TYPE_ERROR);
	}
	else
	{	
		strcpy(resultType->type, t1->type);
	}
}

const Symbol* functionCall(char *resultType, const char *id)
{
	const Symbol *match = NULL;
	
	/*printf("CALL: printing symbol table\n");
	SymbolTable_print(symbolTable, stdout);
	puts("---------------");*/
	
	// function call
	SymbolArray *s = SymbolTable_find(symbolTable, id, SEARCH_ALL_PARENTS);
	
	int i;

	// if zero overloads for this tokenID exist, the function is not declared
	if( s->length == 0 )
	{
		char buffer[1000];
		sprintf(buffer, "%s() has not been declared", id);
		yyerror(buffer);
		strcpy(resultType, TYPE_ERROR);
	}
	else
	{
		//printf("s->length = %lu\n", s->length);
		
		uint64_t i;
		for(i = 0; i < s->length; ++i) // foreach matching symbol
		{
			const Symbol *symbol = s->symbols[i];
			
			if( symbol->symbolType != SYMBOL_FUNCTION ) // skip non-functions
				continue;
			
			// skip functions with different number of arguments
			if( symbol->numParams != paramTypesVecCall->length )
			{
				//printf("different number of arguments. symbol->numParams = %u, paramTypesVec->length = %u\n", symbol->numParams, paramTypesVecCall->length);
				continue;
			}
				
			uint64_t j;
			int innerMatch = 1;
			for(j = 0; j < symbol->numParams; ++j)
			{
				// if a type doesn't match, the function signatures don't match
				if( strcmp(symbol->params[j], paramTypesVecCall->t[j]) != 0 )
				{
					innerMatch = 0;
					break;
				}
			}
			if( innerMatch ) // if the function arguments match
			{
				match = symbol;
				break;
			}
		}
		
		if( !match )
		{
			char buffer[1000];
			sprintf(buffer, "%s(", id);
			
			for(i = 0; i < paramTypesVecCall->length; ++i)
			{
				strcat(buffer, paramTypesVecCall->t[i]);
				if( i < paramTypesVecCall->length - 1 )
					strcat(buffer, ", ");
			}
			strcat(buffer, ") does not match any declared function");
			yyerror(buffer);
			strcpy(resultType, TYPE_ERROR);
		}
		else
		{
			strcpy(resultType, match->type);
		}
	}

	free(s);
	StrVec_clear(paramTypesVecCall);
	
	return match;
}

/// universal function call syntax with an identifier at the left of the dot
const Symbol* ufcs(char *resultType, const char *type, const char *func)
{
	StrVec_insertFront(paramTypesVecCall, type);
	return functionCall(resultType, func);
}

void property(char *resultType, const char *type, const char *property)
{
	if( strcmp(type, "int") == 0 )
	{
		if(	strcmp(property, "max") == 0 ) strcpy(resultType, "int");
		else if( strcmp(property, "min") == 0 ) strcpy(resultType, "int");
		else if( strcmp(property, "sizeof") == 0 ) strcpy(resultType, "int");
		else if( strcmp(property, "init") == 0 ) strcpy(resultType, "int");
		else
		{
			char buffer[1000];
			sprintf(buffer, "unknown property \"%s\" for type \"%s\"", property, type);
			yyerror(buffer);
			strcpy(resultType, TYPE_ERROR);
		}
	}
	else if( strcmp(type, "float") == 0 )
	{
		if(	strcmp(property, "max") == 0 ) strcpy(resultType, "float");
		else if( strcmp(property, "min") == 0 ) strcpy(resultType, "float");
		else if( strcmp(property, "sizeof") == 0 ) strcpy(resultType, "int");
		else if( strcmp(property, "init") == 0 ) strcpy(resultType, "float");
		else
		{
			char buffer[1000];
			sprintf(buffer, "unknown property \"%s\" for type \"%s\"", property, type);
			yyerror(buffer);
			strcpy(resultType, TYPE_ERROR);
		}
	}
	else if( strcmp(type, "int[]") == 0 )
	{
		if(	strcmp(property, "length") == 0 ) strcpy(resultType, "int");
		else
		{
			char buffer[1000];
			sprintf(buffer, "unknown property \"%s\" for type \"%s\"", property, type);
			yyerror(buffer);
			strcpy(resultType, TYPE_ERROR);
		}
	}
	else if( strcmp(type, "float[]") == 0 )
	{
		if(	strcmp(property, "length") == 0 ) strcpy(resultType, "int");
		else
		{
			char buffer[1000];
			sprintf(buffer, "unknown property \"%s\" for type \"%s\"", property, type);
			yyerror(buffer);
			strcpy(resultType, TYPE_ERROR);
		}
	}
	else
		strcpy(resultType, TYPE_ERROR);
}

void returnStatement(const char *type)
{
	StrVec_insert(returnTypes, type);
	IntVec_insert(returnTypesLines, getLineNo());
	IntVec_insert(returnTypesDepths, SymbolTable_depth(symbolTable));
}

void checkFunctionReturns(const Symbol *func)
{
	uint32_t returnsAtFunctionScope = 0; // returns in the outer scope of the function
	uint32_t functionScopeDepth = SymbolTable_depth(symbolTable);
	
	uint32_t i;
	for(i = 0; i < returnTypes->length; ++i)
	{
		if( strcmp(func->type, returnTypes->t[i]) != 0 )
		{
			char buffer[1000], buffer2[1000];
			Symbol_toString(func, buffer2);
			sprintf(buffer, "function \"%s\" must return \"%s\", not \"%s\"", buffer2, func->type, returnTypes->t[i]);
			
			yyerror2(buffer, returnTypesLines->t[i]);
			
			// when a return type at function scope does not match the return type of the function,
			// don't complain that the function doesn't return a value. Complain only because the return type
			// doesn't match (show one error instead of two)
			if( returnTypesDepths->t[i] == functionScopeDepth )
				++returnsAtFunctionScope;
		}
		else if( returnTypesDepths->t[i] == functionScopeDepth )
		{
			// if a return was found earlier at function scope, report an error
			if( returnsAtFunctionScope != 0 )

				yyerror2("a return statement was found earlier", returnTypesLines->t[i]);
			
			++returnsAtFunctionScope;
		}
	}
	
	if( returnsAtFunctionScope == 0 && strcmp(func->type, "void") != 0 )
	{
		char buffer[1000], buffer2[1000];
		Symbol_toString(func, buffer2);
		sprintf(buffer, "function \"%s\" must return a value", buffer2);
		yyerror(buffer);
	}
}

void inferTypeOfIdentifier(char *result, const char *id)
{
	SymbolArray *s = SymbolTable_find(symbolTable, id, SEARCH_ALL_PARENTS);
	uint64_t i;
	char buffer[1000];
	
	if( s->length == 0 )
	{
		sprintf(buffer, "undeclared variable \"%s\"", id);
		yyerror(buffer);
	}
	else if( s->length == 1 )
	{
		strcpy(result, s->symbols[0]->type);
	}
	else
	{
		yyerror("symbol name in typeof() was declared multiple times");
		strcpy(result, TYPE_ERROR);
	}
	
	free(s);
}

void pragmaString(const char *pragmaType, const char *command)
{
	char *tmp = (char*)malloc(sizeof(char) * (strlen(command) + 1));
	strcpy(tmp, command);
	
	char *str = tmp;
	++str;							// skip " at the beginning
	str[strlen(str) - 1] = '\0';	// skip " at the end
	
	if( strcmp(pragmaType, "msg") == 0 )
	{
		puts(str);
	}
	else
	{
		yyerror("unknown pragma");
	}
	
	free(tmp);
}

/// generate assembly for x86
void genAssemlby_x86(const InstructionList *l, FILE *f)
{	
	// http://en.wikibooks.org/wiki/X86_Assembly
	
	fprintf(f, ".include \"cmc-util.s\" # include cmc utility assembly functions\n");
	fprintf(f, ".text\n");
	fprintf(f, "newline:\n.string \"\\n\"\n");
	
	int i;
	char buffer[1000];
	
	InstructionList *list = InstrList_create();
	InstrList_concat(list, l);
	
	// map temporaries to distance from %ebp
	int tLen = 0;
	int tCapacity = 1000;
	uint32_t *t = (uint32_t*)malloc(sizeof(uint32_t) * tCapacity);
	int *dist  = (int*)malloc(sizeof(int) * tCapacity);
	
	// we must know the stack usage for each function
	int funcLabelCapacity = 1000;
	int funcLabelSize = 0;
	char **funcLabel = (char**)malloc(sizeof(char*) * funcLabelCapacity);
	int *stackUsage = (int*)malloc(sizeof(int) * funcLabelCapacity);
	
	int distFromEbp = 0;
	
	uint32_t currentFuncNumArgs; // number of arguments for the current function
	
	InstructionNode *n = list->head;

	// this loop is run first to determine how much space is needed in the stack for each function
	while( n != NULL )
	{
		switch(n->instrType)
		{
		case INSTR_FUNC_LABEL:	// function
			distFromEbp = tLen = 0;
			
			funcLabel[funcLabelSize] = (char*)malloc(sizeof(char) * (strlen(n->value) + 1));
			strcpy(funcLabel[funcLabelSize], n->value);
			break;
			
		case INSTR_RET:			// return
			stackUsage[funcLabelSize++] = distFromEbp;
			break;
		
		case INSTR_LOAD_INT:	// load int
			for(i = 0; i < tLen; ++i)
				if( t[i] == n->destPlace )
					break;
			
			if( i == tLen ) // if not found
				distFromEbp -= 4;
			break;

		case INSTR_ADD:
		case INSTR_SUB:
		case INSTR_MUL:
		case INSTR_DIV:
		case INSTR_REM:
			distFromEbp -= 4;
			break;
		
		case INSTR_EQUAL:
			{
				uint32_t destPos = findUint32(t, tLen, n->destPlace);
				
				if( destPos == tLen ) // this place doesn't exist yet, so create it
					distFromEbp -= 4;
			}
			break;
			
			case INSTR_NOT_EQUAL:
			{
				uint32_t destPos = findUint32(t, tLen, n->destPlace);
				
				if( destPos == tLen ) // this place doesn't exist yet, so create it
					distFromEbp -= 4;
			}
			break;
			
			case INSTR_LESS:
			{
				uint32_t destPos = findUint32(t, tLen, n->destPlace);
				
				if( destPos == tLen ) // this place doesn't exist yet, so create it
					distFromEbp -= 4;
			}
			break;
			
			case INSTR_LESS_EQUAL:
			{
				uint32_t destPos = findUint32(t, tLen, n->destPlace);
				
				if( destPos == tLen ) // this place doesn't exist yet, so create it
					distFromEbp -= 4;
			}
			break;
			
			case INSTR_GREATER:
			{
				uint32_t destPos = findUint32(t, tLen, n->destPlace);
				
				if( destPos == tLen ) // this place doesn't exist yet, so create it
					distFromEbp -= 4;
			}
			break;
			
			case INSTR_GREATER_EQUAL:
			{
				uint32_t destPos = findUint32(t, tLen, n->destPlace);
				uint32_t inPos0 = findUint32(t, tLen, n->destPlace);
				
				if( destPos == tLen ) // this place doesn't exist yet, so create it
					distFromEbp -= 4;
			}
			break;
			
			case INSTR_FUNC_CALL:
			{
				uint32_t destPos = findUint32(t, tLen, n->destPlace);
				
				if( destPos == tLen ) // this place doesn't exist yet, so create it
					distFromEbp -= 4;
			}
			break;
			
			case INSTR_LOAD_FROM_OFFSET:
			{
				uint32_t destPos = findUint32(t, tLen, n->destPlace);
				
				if( destPos == tLen ) // this place doesn't exist yet, so create it
				{
					distFromEbp -= 4;
				}
			}
			break;
			
			case INSTR_READ_INT:
			if( findUint32(t, tLen, n->destPlace) == tLen ) // this place doesn't exist yet, so create it
				distFromEbp -= 4;
			break;
		}
		
		n = n->next;
	}

	uint32_t currentFunction = 0;
	
	n = list->head;
	while( n != NULL )
	{
		switch(n->instrType)
		{
		case INSTR_FUNC_LABEL:	// function
			distFromEbp = tLen = 0;
			sprintf(n->userData, "\n.globl %s\n%s:\npushl %%ebp\nmovl %%esp, %%ebp\n", n->value, n->value);
			
			currentFuncNumArgs = getNumOfArguments(n->value);
			
			break;
			
		case INSTR_RET:			// return
			{
				uint32_t inPos = findUint32(t, tLen, n->inPlace0);
				
				if( strcmp(n->type, "void") != 0 )
				{
					sprintf(n->userData,
					"movl %d(%%ebp), %%eax\n" \
					"leave\nret\n",
					dist[inPos]);
				}
				else
				{
					sprintf(n->userData, "leave\nret\n", dist[inPos]);
				}
			}
			break;
		
		case INSTR_LOAD_INT:	// load int
			for(i = 0; i < tLen; ++i)
				if( t[i] == n->destPlace )
					break;
			
			if( i != tLen ) // if found
			{
				if( n->destPlace < currentFuncNumArgs )
					dist[i] = 8 + n->destPlace * 4;
				
				sprintf(buffer, "movl $%d, %d(%%ebp)\n", atoi(n->value), dist[i]);
				strcpy(n->userData, buffer);	
			}
			else
			{
				distFromEbp -= 4;
				t[tLen] = n->destPlace;
				dist[tLen] = distFromEbp;
				++tLen;
				
				sprintf(n->userData, "movl $%d, %d(%%ebp)\n", atoi(n->value), dist[i]);
			}
			break;
			
		case INSTR_ASSIGN: // =
			{
				uint32_t inPlace0Pos = findUint32(t, tLen, n->inPlace0);
				uint32_t destPos = findUint32(t, tLen, n->destPlace);
				
				if( n->inPlace0 < currentFuncNumArgs )
					dist[inPlace0Pos] = 8 + n->inPlace0 * 4;
				
				if( n->destPlace < currentFuncNumArgs )
					dist[destPos] = 8 + n->destPlace * 4;
				
				sprintf(n->userData, "movl %d(%%ebp), %%eax\nmovl %%eax, %d(%%ebp)\n", dist[inPlace0Pos], dist[destPos]);
			}
			break;
			
		case INSTR_WRITELN:	// writeln
			{
				for(i = 0; i < tLen; ++i)
					if( n->inPlace0 == t[i] )
						break;
						
				// if this variable is an argument
				if( n->inPlace0 < currentFuncNumArgs )
					dist[i] = 8 + n->inPlace0 * 4;
				
				if( strcmp(n->type, "int") == 0 )
				{
					sprintf(n->userData, "\n# call a function to print\npush %d(%%ebp)\ncall __print_int\naddl $4, %%esp\n", dist[i]);
					strcat(n->userData, "\n# print a new line\nmovl $4, %eax\nmovl $1, %ebx\nmovl $newline, %ecx\nmovl $1, %edx\nint $0x80\n\n");
				}
				else
					assert(0 && "support for printing this type has not been implemented yet");
			}
			break;
		
		case INSTR_ADD:
			{
				uint32_t inPlace0Pos = findUint32(t, tLen, n->inPlace0);
				uint32_t inPlace1Pos = findUint32(t, tLen, n->inPlace1);
				
				distFromEbp -= 4;
				t[tLen] = n->destPlace;
				dist[tLen] = distFromEbp;
				++tLen;
				
				sprintf(n->userData, "movl %d(%%ebp), %%eax\naddl %d(%%ebp), %%eax\nmovl %%eax, %d(%%ebp)\n", dist[inPlace0Pos], dist[inPlace1Pos], dist[tLen - 1]);
			}
			break;
			
		case INSTR_SUB:
			{
				uint32_t inPlace0Pos = findUint32(t, tLen, n->inPlace0);
				uint32_t inPlace1Pos = findUint32(t, tLen, n->inPlace1);
				
				distFromEbp -= 4;
				t[tLen] = n->destPlace;
				dist[tLen] = distFromEbp;
				++tLen;
				
				sprintf(n->userData, "\nmovl %d(%%ebp), %%eax\nsubl %d(%%ebp), %%eax\nmovl %%eax, %d(%%ebp)\n", dist[inPlace0Pos], dist[inPlace1Pos], dist[tLen - 1]);
			}
			break;
			
		case INSTR_MUL:
			{
				uint32_t inPlace0Pos = findUint32(t, tLen, n->inPlace0);
				uint32_t inPlace1Pos = findUint32(t, tLen, n->inPlace1);
				
				distFromEbp -= 4;
				t[tLen] = n->destPlace;
				dist[tLen] = distFromEbp;
				++tLen;
				
				sprintf(n->userData, "\nmovl %d(%%ebp), %%eax\nimul %d(%%ebp), %%eax\nmovl %%eax, %d(%%ebp)\n", dist[inPlace0Pos], dist[inPlace1Pos], dist[tLen - 1]);
			}
			break;
			
		case INSTR_DIV:
			{
				uint32_t inPlace0Pos = findUint32(t, tLen, n->inPlace0);
				uint32_t inPlace1Pos = findUint32(t, tLen, n->inPlace1);
				
				distFromEbp -= 4;
				t[tLen] = n->destPlace;
				dist[tLen] = distFromEbp;
				++tLen;
				
				// the divident is composed of two registers(64+64 bits).
				// the edx contains the upper 64 bits and must not contain garbage
				// http://en.wikibooks.org/wiki/X86_Assembly/Arithmetic
				sprintf(n->userData, "\n"	\
				"movl $0, %%edx\n"			\
				"movl %d(%%ebp), %%eax\n"	\
				"movl %d(%%ebp), %%ebx\n"	\
				"idiv %%ebx\n"				\
				"movl %%eax, %d(%%ebp)\n"
				,dist[inPlace0Pos], dist[inPlace1Pos], dist[tLen - 1]);
			}
			break;
		
		case INSTR_REM:
			{
				uint32_t inPlace0Pos = findUint32(t, tLen, n->inPlace0);
				uint32_t inPlace1Pos = findUint32(t, tLen, n->inPlace1);
				
				distFromEbp -= 4;
				t[tLen] = n->destPlace;
				dist[tLen] = distFromEbp;
				++tLen;
				
				// the divident is composed of two registers(64+64 bits).
				// the edx contains the upper 64 bits and must not contain garbage
				// http://en.wikibooks.org/wiki/X86_Assembly/Arithmetic
				sprintf(n->userData, "\n"	\
				"movl $0, %%edx\n"			\
				"movl %d(%%ebp), %%eax\n"	\
				"movl %d(%%ebp), %%ebx\n"	\
				"idiv %%ebx\n"				\
				"movl %%edx, %d(%%ebp)\n"
				,dist[inPlace0Pos], dist[inPlace1Pos], dist[tLen - 1]);
			}
			break;
		
		case INSTR_EQUAL:
			{
				uint32_t inPlace0Pos = findUint32(t, tLen, n->inPlace0);
				uint32_t inPlace1Pos = findUint32(t, tLen, n->inPlace1);
				uint32_t destPos = findUint32(t, tLen, n->destPlace);
				
				if( destPos == tLen ) // this place doesn't exist yet, so create it
				{
					distFromEbp -= 4;
					t[tLen] = n->destPlace;
					dist[tLen] = distFromEbp;
					++tLen;
				}
				
				sprintf(n->userData,
				"movl %d(%%ebp), %%eax\n"		\
				"cmpl %%eax, %d(%%ebp)\n"		\
				"sete	%%al\n"					\
				"movzbl	%%al, %%eax\n"			\
				"movl	%%eax, %d(%%ebp)\n",
				dist[inPlace0Pos], dist[inPlace1Pos], dist[destPos]);
			}
			break;
			
			case INSTR_NOT_EQUAL:
			{
				uint32_t inPlace0Pos = findUint32(t, tLen, n->inPlace0);
				uint32_t inPlace1Pos = findUint32(t, tLen, n->inPlace1);
				uint32_t destPos = findUint32(t, tLen, n->destPlace);
				
				if( destPos == tLen ) // this place doesn't exist yet, so create it
				{
					distFromEbp -= 4;
					t[tLen] = n->destPlace;
					dist[tLen] = distFromEbp;
					++tLen;
				}
				
				sprintf(n->userData,
				"movl %d(%%ebp), %%eax\n"		\
				"cmpl %%eax, %d(%%ebp)\n"		\
				"setne	%%al\n"					\
				"movzbl	%%al, %%eax\n"			\
				"movl	%%eax, %d(%%ebp)\n",
				dist[inPlace0Pos], dist[inPlace1Pos], dist[destPos]);
			}
			break;
			
			case INSTR_LESS:
			{
				uint32_t inPlace0Pos = findUint32(t, tLen, n->inPlace0);
				uint32_t inPlace1Pos = findUint32(t, tLen, n->inPlace1);
				uint32_t destPos = findUint32(t, tLen, n->destPlace);
				
				if( destPos == tLen ) // this place doesn't exist yet, so create it
				{
					distFromEbp -= 4;
					t[tLen] = n->destPlace;
					dist[tLen] = distFromEbp;
					++tLen;
				}
				
				sprintf(n->userData,
				"movl %d(%%ebp), %%eax\n"		\
				"cmpl %%eax, %d(%%ebp)\n"		\
				"setl	%%al\n"					\
				"movzbl	%%al, %%eax\n"			\
				"movl	%%eax, %d(%%ebp)\n",
				dist[inPlace1Pos], dist[inPlace0Pos], dist[destPos]);
			}
			break;
			
			case INSTR_LESS_EQUAL:
			{
				uint32_t inPlace0Pos = findUint32(t, tLen, n->inPlace0);
				uint32_t inPlace1Pos = findUint32(t, tLen, n->inPlace1);
				uint32_t destPos = findUint32(t, tLen, n->destPlace);
				
				if( destPos == tLen ) // this place doesn't exist yet, so create it
				{
					distFromEbp -= 4;
					t[tLen] = n->destPlace;
					dist[tLen] = distFromEbp;
					++tLen;
				}
				
				sprintf(n->userData,
				"movl %d(%%ebp), %%eax\n"		\
				"cmpl %%eax, %d(%%ebp)\n"		\
				"setle	%%al\n"					\
				"movzbl	%%al, %%eax\n"			\
				"movl	%%eax, %d(%%ebp)\n",
				dist[inPlace1Pos], dist[inPlace0Pos], dist[destPos]);
			}
			break;
			
			case INSTR_GREATER:
			{
				uint32_t inPlace0Pos = findUint32(t, tLen, n->inPlace0);
				uint32_t inPlace1Pos = findUint32(t, tLen, n->inPlace1);
				uint32_t destPos = findUint32(t, tLen, n->destPlace);
				
				if( destPos == tLen ) // this place doesn't exist yet, so create it
				{
					distFromEbp -= 4;
					t[tLen] = n->destPlace;
					dist[tLen] = distFromEbp;
					++tLen;
				}
				
				sprintf(n->userData,
				"movl %d(%%ebp), %%eax\n"		\
				"cmpl %%eax, %d(%%ebp)\n"		\
				"setg	%%al\n"					\
				"movzbl	%%al, %%eax\n"			\
				"movl	%%eax, %d(%%ebp)\n",
				dist[inPlace1Pos], dist[inPlace0Pos], dist[destPos]);
			}
			break;
			
			case INSTR_GREATER_EQUAL:
			{
				uint32_t inPlace0Pos = findUint32(t, tLen, n->inPlace0);
				uint32_t inPlace1Pos = findUint32(t, tLen, n->inPlace1);
				uint32_t destPos = findUint32(t, tLen, n->destPlace);
				
				if( destPos == tLen ) // this place doesn't exist yet, so create it
				{
					distFromEbp -= 4;
					t[tLen] = n->destPlace;
					dist[tLen] = distFromEbp;
					++tLen;
				}
				
				sprintf(n->userData,
				"movl %d(%%ebp), %%eax\n"		\
				"cmpl %%eax, %d(%%ebp)\n"		\
				"setge	%%al\n"					\
				"movzbl	%%al, %%eax\n"			\
				"movl	%%eax, %d(%%ebp)\n",
				dist[inPlace1Pos], dist[inPlace0Pos], dist[destPos]);
			}
			break;
			
		case INSTR_IF_NOT:
			{
				uint32_t inPos = findUint32(t, tLen, n->inPlace0);
				
				if( n->inPlace0 < currentFuncNumArgs )
					dist[inPos] = 8 + n->inPlace0 * 4;
				
				sprintf(n->userData,
				"movl %d(%%ebp), %%eax\n"	\
				"cmpl $0, %%eax\n"			\
				"jz .L%u\n",
				dist[inPos], n->after);
			}
			break;
			
		case INSTR_WHILE_NOT:
			{
				uint32_t inPos = findUint32(t, tLen, n->inPlace0);
				
				if( n->inPlace0 < currentFuncNumArgs )
					dist[inPos] = 8 + n->inPlace0 * 4;
				
				sprintf(n->userData,
				"movl %d(%%ebp), %%eax\n"	\
				"cmpl $0, %%eax\n"			\
				"jz .L%u\n",
				dist[inPos], n->after);
			}
			break;
			
		case INSTR_LABEL:
			sprintf(n->userData, ".L%u:\n", n->after);
			break;
			
		case INSTR_UNCONDITIONAL_JUMP:
			sprintf(n->userData, "jmp .L%u\n", n->begin);
			break;
		
		case INSTR_FUNC_CALL:
		{
			if( strcmp(n->type, "void") == 0 )
			{
				sprintf(n->userData, "call %s\n", n->value);
			}
			else
			{
				uint32_t destPos = findUint32(t, tLen, n->destPlace);
				if( destPos == tLen )
				{
					distFromEbp -= 4;
					t[tLen] = n->destPlace;
					dist[tLen] = distFromEbp;
					++tLen;
				}
				
				sprintf(n->userData,
				"call %s\n" 	\
				"movl %%eax, %d(%%ebp)\n",
				n->value, dist[destPos]);
			}
			break;
		}
			
		case INSTR_FUNC_PARAM_PUSH:
			{
				uint32_t pos = findUint32(t, tLen, n->inPlace0);
				
				if( n->inPlace0 < currentFuncNumArgs )
					dist[pos] = 8 + n->inPlace0 * 4;
				
				sprintf(n->userData, "push %d(%%ebp)\n", dist[pos]);
			}
			break;
			
		case INSTR_FUNC_PARAMS_POP:
			{
				sprintf(n->userData, "add $%u, %%esp\n", (uint32_t)atol(n->value) * 4);
			}
			break;
			
		case INSTR_1ST_ARG_PLACE:
			{
				// this is needed to allocate slots for the function's arguments
				
				for(i = 0; i < currentFuncNumArgs; ++i)
				{
					t[tLen] = n->inPlace0 + i;
					dist[tLen] = 8 + i * 4;
					++tLen;
				}
			}
			break;
			
		case INSTR_LOAD_FROM_OFFSET:
			{
				uint32_t destPos = findUint32(t, tLen, n->destPlace);
				uint32_t offsetPos = findUint32(t, tLen, n->inPlace1); // offset
				uint32_t inPos = findUint32(t, tLen, n->inPlace0);
				
				if( destPos == tLen ) // this place doesn't exist yet, so create it
				{
					distFromEbp -= 4;
					t[tLen] = n->destPlace;
					dist[tLen] = distFromEbp;
					++tLen;
				}
				
				sprintf(n->userData,
				"\nmovl %d(%%ebp), %%eax\n"			\
				"imul $-1, %%eax\t# multiply by -1 because we want to go down on the stack, not up\n"\
				"movl %d(%%ebp, %%eax, 4), %%ebx\n"	\
				"movl %%ebx, %d(%%ebp)\n",
				dist[offsetPos], dist[inPos], dist[destPos]);
			}
			break;
			
		case INSTR_READ_INT:
			{
				uint32_t destPos = findUint32(t, tLen, n->destPlace);
				if( destPos == tLen )
				{
					distFromEbp -= 4;
					t[tLen] = n->destPlace;
					dist[tLen] = distFromEbp;
					++tLen;
				}
				sprintf(n->userData,
				"call __read_int\n"	\
				"movl %%eax, %d(%%ebp)\n",
				dist[destPos]);
			}
			break;
		
		//default:
		//	assert(0 && "n->instrType is not handled or has an invalid value");
		}
		
		//assert(n && "n is null");
		n = n->next;
	}
	
	i = 0;
	n = list->head;
	while( n != NULL )
	{
		if( n->instrType == INSTR_FUNC_LABEL )
		{
			int i;
			for(i = 0; i < funcLabelSize; ++i)
				if( strcmp(funcLabel[i], n->value) == 0 )
					break;
					
			fprintf(f, "%s", n->userData);
			fprintf(f, "subl $%d, %%esp\t# get some stack space\n\n", stackUsage[i] * -1);
		}
		else
		{
			fprintf(f, "%s", n->userData);
		}
		
		n = n->next;
	}
	
	InstrList_destroy(list);
	free(dist);
}

/**
 * TODO: for every read of variable from memory,
 * if it's place is < getNumOfArgs(), then
 * change its place to add to the %ebp
*/
