#ifndef __STRING_VECTOR_H__
#define __STRING_VECTOR_H__

#include <stdlib.h>
#include <assert.h>
#include <stdint.h>

typedef struct
{
	char **t;
	uint32_t length, capacity;

} StrVec;

/// creates and returns dynamically allocated StringVector. If allocation failed, return NULL
StrVec* StrVec_create();

/// inserts a string at the end of the string vector
void StrVec_insert(StrVec *strVec, const char *str);

/// inserts a string at the beginning of the string vector. Takes O(length) time.
void StrVec_insertFront(StrVec *strVec, const char *str);

/// removes all strings from the vector
void StrVec_clear(StrVec *strVec);

/// frees all memory allocated for strvec
void StrVec_destroy(StrVec *strVec);

#endif
