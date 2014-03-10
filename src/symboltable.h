#ifndef __SYMBOL_TABLE_H__
#define __SYMBOL_TABLE_H__

#include <stdint.h>
#include "symbol.h"

typedef struct _SymbolTable
{
	struct _SymbolTable *parent;
	Symbol **symbols; // array of symbol pointers (1D array)
	
	size_t numSymbols;
	size_t capacity;
	
} SymbolTable;

/// creates a heap allocated symbol table and returns it
SymbolTable* SymbolTable_create();

/// frees the memory allocated by the st
void SymbolTable_destroy(SymbolTable *st);

/// inserts symbol "s" into "st"
void SymbolTable_insert(SymbolTable *st, Symbol *s);

/// prints the symbols of st into FILE f
void SymbolTable_print(const SymbolTable *st, FILE *f);

typedef struct
{
	Symbol* symbols[4096];
	uint64_t length;
	
} SymbolArray;

/**
 * enum that descripes how bind() will execute. If search type is SEARCH_LOCAL_ONLY,
 * the name is looked up only in the active symbol table - not in its parents.
 * If it is SEARCH_ALL_PARENTS, a recursive search will take place and "name"
 * will be searched in all symbol tables that are parent of the current.
 */
typedef enum
{
	SEARCH_LOCAL_ONLY,
	SEARCH_ALL_PARENTS
	
} SearchType;

/**
 * performs a recursive search and returns a SymbolArray that
 * contains the symbols that match ('cause mutliple versions of that function may exist)
 * Note: the comparison is made using the name of the symbol
 * The array must be freed.
 * @param st The symbol table to look into
 * @param name The identifier's/function's name
 * 
 */
SymbolArray* SymbolTable_find(SymbolTable *st, const char *name, SearchType searchType);


/// @return The depth of the current symbol table (which is the depth of the current scope)
int SymbolTable_depth(const SymbolTable *st);

#endif
