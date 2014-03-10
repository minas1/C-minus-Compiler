#include "symboltable.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

SymbolTable* SymbolTable_create()
{
	SymbolTable *st = (SymbolTable*)malloc(sizeof(SymbolTable));
	
	assert(st && "memory allocation for symbol table failed");
	
	st->parent = NULL;
	st->capacity = 10;
	st->numSymbols = 0;
	
	st->symbols = (Symbol**)malloc(sizeof(Symbol*) * st->capacity);
	assert(st->symbols && "memory allocation for symbol table symbol array failed");
	
	return st;
}

void SymbolTable_destroy(SymbolTable *st)
{
	assert(st && "st is null");
	
	uint64_t i;
	
	for(i = 0; i < st->numSymbols; ++i)
		Symbol_destroy(st->symbols[i]);
		
	free(st->symbols);
	free(st);
}


void SymbolTable_insert(SymbolTable *st, Symbol *s)
{
	assert(st && "st is null");
	assert(s && "s is null");
	
	if( st->numSymbols == st->capacity )
	{
		st->capacity *= 2;
		st->symbols = (Symbol**)realloc(st->symbols, sizeof(Symbol*) * st->capacity);
	}
	
	st->symbols[st->numSymbols++] = s;
}

void SymbolTable_print(const SymbolTable *st, FILE *f)
{
	assert(st && "st is null");
	assert(f && "f is null");
	
	size_t i;
	
	while( st != NULL )
	{
		for(i = 0; i < st->numSymbols; ++i)
			Symbol_print(st->symbols[i], f);
		
		st = st->parent;
	}
}


SymbolArray* SymbolTable_find(SymbolTable *st, const char *name, SearchType searchType)
{
	assert(st && "st is null");
	assert(name && "name is null");
	
	SymbolArray *sa = (SymbolArray*)malloc(sizeof(SymbolArray));
	assert(sa && "memory allocation for SymbolArray failed");
	
	sa->length = 0;
	
	SymbolTable *p = st;
	
	if( searchType == SEARCH_LOCAL_ONLY )
	{
		uint64_t i;
		for(i = 0; i < p->numSymbols; ++i)
			if( strcmp(p->symbols[i]->name, name) == 0 )
				sa->symbols[sa->length++] = p->symbols[i];
	}
	else
	{
		while( p != NULL )
		{
			uint64_t i;
			for(i = 0; i < p->numSymbols; ++i)
				if( strcmp(p->symbols[i]->name, name) == 0 )
					sa->symbols[sa->length++] = p->symbols[i];
			
			p = p->parent;
		}
	}
	
	return sa;
}

int SymbolTable_depth(const SymbolTable *st)
{
	assert(st && "st is null");
	
	int depth = -1; // must return 0 for the global scope, so start it from -1
	while( st != NULL )
	{
		++depth;
		st = st->parent;
	}
	
	return depth;
}
