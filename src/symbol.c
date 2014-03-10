#include "three-code-helper.h"

#include "symbol.h"

#include <assert.h>
#include <stdlib.h>
#include <stddef.h> // contains the definition of NULL
#include <string.h>

/// returns a heap allocated Symbol
Symbol* Symbol_create(SymbolType symbolType)
{
	Symbol *s = (Symbol*)malloc(sizeof(Symbol));
	
	assert(s != NULL && "Symbol_create(): memory allocation failed");
	
	s->symbolType = symbolType;
	
	s->name = NULL;
	s->type = NULL;
	s->numParams = 0;
	s->len = 0;
	s->params = NULL;
	
	return s;
}

/// constructs a copy of s and returns it
Symbol* Symbol_createFromExisting(const Symbol *s)
{
	assert(s && "s is null");
	
	Symbol *ss = (Symbol*)malloc(sizeof(Symbol));
	
	ss->symbolType = s->symbolType;
	ss->numParams = 0;
	ss->place = s->place;
	ss->len = s->len;
	
	Symbol_setName(ss, s->name);
	Symbol_setType(ss, s->type);
	
	unsigned short i;
	for(i = 0; i < s->numParams; ++i)
		Symbol_addParam(ss, s->params[i]);
		
	return ss;
}

void Symbol_destroy(Symbol *s)
{
	unsigned short i;
	
	assert(s != NULL && "s is NULL");
	
	free(s->name);
	free(s->type);
	
	for(i = 0; i < s->numParams; ++i)
		free(s->params[i]);
	free(s->params);
}

void Symbol_setName(Symbol *s, const char *str)
{
	assert(s != NULL && "Symbol_setName(Symbol *s, const char *str): s is null");
	assert(str != NULL && "Symbol_setName(Symbol *s, const char *str): str is null");
	
	size_t len = strlen(str);
	
	if( s->name != NULL )
		free(s->name);
		
	s->name = (char*)malloc(sizeof(char) * (len + 1));
	strcpy(s->name, str);
}

void Symbol_setType(Symbol *s, const char *str)
{
	assert(s != NULL && "Symbol_setType(Symbol *s, const char *str): s is null");
	assert(str != NULL && "Symbol_setType(Symbol *s, const char *str): str is null");
	
	size_t len = strlen(str);
	
	if( s->type != NULL )
		free(s->type);
	
	s->type = (char*)malloc(sizeof(char) * (len + 1));
	strcpy(s->type, str);
}

void Symbol_addParam(Symbol *s, const char *type)
{
	assert(s != NULL && "Symbol_addParameter(Symbol *s, const char *type): s is null");
	assert(type != NULL && "Symbol_addParameter(Symbol *s, const char *type): type is null");
	
	char **newParams = (char**)malloc(sizeof(char*) * (s->numParams + 1));
	int i;
	for(i = 0; i < s->numParams; ++i)
		newParams[i] = s->params[i];
	
	free(s->params);
	
	newParams[s->numParams] = (char*)malloc(sizeof(char) * (strlen(type) + 1));
	strcpy(newParams[s->numParams], type);
	
	s->params = newParams;
	++s->numParams;
}

void Symbol_print(const Symbol *s, FILE *f)
{
	assert(s != NULL && "Symbol_addParam(Symbol *s, FILE *f): s is null");
	assert(f != NULL && "Symbol_addParam(Symbol *s, FILE *f): f is null");
	
	if( s->symbolType == SYMBOL_VARIABLE )
	{
		fprintf(f, "%s", s->type);
		if( s->len != 0 ) fprintf(f, "[%lu]", s->len);
		fprintf(f, " %s\n", s->name);
	}
	else
	{
		int i;
		fprintf(f, "%s", s->type);						// print type
		if( s->len != 0 ) fprintf(f, "[%lu]", s->len);	// returns an array?
		fprintf(f, " %s (", s->name);
		for(i = 0; i < s->numParams; ++i)
			fprintf(f, "%s%s", s->params[i], (i < s->numParams - 1 ? ", " : ""));
		fprintf(f, ")\n");
	}
}

void Symbol_toString(const Symbol *s, char *buffer)
{
	assert(s && "s is null");
	assert(buffer && "buffer is null");
	
	if( s->symbolType == SYMBOL_VARIABLE )
	{
		sprintf(buffer, "%s", s->type);
		strcat(buffer, " ");
		strcat(buffer, s->name);
	}
	else
	{
		size_t i;
		
		// TODO: implement for functions
		
		sprintf(buffer, "%s %s(", s->type, s->name);
		
		// TODO: if the return value is an array, write [size] in buffer.
		// Right now it is not implemented because it is not supported by the grammer
		
		for(i = 0; i < s->numParams; ++i)
		{
			strcat(buffer, s->params[i]);
			
			if( i < s->numParams - 1)
				strcat(buffer, ", ");
		}
		strcat(buffer, ")");
	}
}
