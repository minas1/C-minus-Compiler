#ifndef __INT_VECTOR_H__
#define __INT_VECTOR_H__

#include <stdlib.h>
#include <assert.h>

typedef struct
{
	long *t;
	size_t length, capacity;

} IntVec;

/// creates and returns dynamically allocated IntVec. If allocation failed, return NULL
IntVec* IntVec_create();

/// inserts an int into the int vector
void IntVec_insert(IntVec *intVec, long val);

/// removes all strings from the vector
void IntVec_clear(IntVec *intVec);

/// frees all memory allocated for intvec
void IntVec_destroy(IntVec *intVec);

#endif
