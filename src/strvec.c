#include "strvec.h"

#include <string.h>

StrVec* StrVec_create()
{
	StrVec *p = (StrVec*)malloc(sizeof(StrVec));
	p->length = 0;
	p->capacity = 10;
	p->t = (char**)malloc(sizeof(char*) * p->capacity);
	
	assert(p && "memory allocation for StrVec failed");
	assert(p->t && "memory allocation for string vector's array failed");
	
	return p;
}

void StrVec_insert(StrVec *strVec, const char *str)
{
	assert(strVec && "strVec is null");
	assert(str && "str is null");
	
	StrVec *p = strVec;
	
	if( p->length == p->capacity )
	{
		p->t = (char**)realloc(p->t, p->capacity * 2 * sizeof(const char*));
		p->capacity *= 2;
	}
	
	char *temp = (char*)malloc(sizeof(char) * (strlen(str) + 1));
	strcpy(temp, str);
	
	p->t[p->length++] = temp;
}

/// inserts a string at the beginning of the string vector. Takes O(length) time.
void StrVec_insertFront(StrVec *strVec, const char *str)
{
	assert(strVec && "strVec is null");
	assert(str && "str is null");
	
	StrVec *p = strVec;
	
	if( p->length == p->capacity )
	{
		p->t = (char**)realloc(p->t, p->capacity * 2 * sizeof(const char*));
		p->capacity *= 2;
	}
	
	char *temp = (char*)malloc(sizeof(char) * (strlen(str) + 1));
	strcpy(temp, str);
	
	uint32_t i;
	for(i = p->length; i > 0; --i)
		p->t[i] = p->t[i-1];
		
	p->t[0] = temp;
	++p->length;
}

void StrVec_clear(StrVec *strVec)
{
	assert(strVec && "strVec is null");
	
	size_t i;
	
	for(i = 0; i < strVec->length; ++i)
		free(strVec->t[i]);
		
	strVec->length = 0;
}

void StrVec_destroy(StrVec *strVec)
{
	assert(strVec && "strVec is null");
	
	StrVec_clear(strVec);
	free(strVec->t);
	free(strVec);
}
