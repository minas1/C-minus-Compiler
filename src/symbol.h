#ifndef __SYMBOL_H__
#define __SYMBOL_H__

#include <stdio.h>
#include <stdint.h>

#define TYPE_ERROR "type_error"

typedef enum
{
	SYMBOL_VARIABLE,
	SYMBOL_FUNCTION
	
} SymbolType;

typedef struct _Symbol
{
	char *name;					// identifier name
	char *type;					// type for variables, return type for functions
	
	uint32_t len;				// length for arrays. also used for functions that returns arrays
	
	SymbolType symbolType;
	
	unsigned short numParams;	// number of parameters
	char **params;				// array with the parameter types
	
	uint32_t place;

} Symbol;

typedef struct
{
	char type[1000]; // type (int, float, etc)
	
	struct _InstructionList *code; // the code
	uint32_t place; // which "virtual" register is the result stored into?
	uint32_t begin, after; // begin/after labels. used for "if", "while" etc
	
} SymbolInfo;

/// returns a heap allocated Symbol
Symbol* Symbol_create(SymbolType symbolType);

/// constructs a copy of s and returns it
Symbol* Symbol_createFromExisting(const Symbol *s);

/// frees the memory allocated by s
void Symbol_destroy(Symbol *s);

/// sets the name of the symbol
void Symbol_setName(Symbol *s, const char *str);

/// sets the return type
void Symbol_setType(Symbol *s, const char *str);

/// adds a parameter to the symbol
void Symbol_addParam(Symbol *s, const char *type);

void Symbol_print(const Symbol *s, FILE *f);

/// writes symbol s to buffer
void Symbol_toString(const Symbol *s, char *buffer);

#endif
