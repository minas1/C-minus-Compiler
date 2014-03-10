#include "intvec.h"

/// creates and returns dynamically allocated IntVec. If allocation failed, return NULL
IntVec* IntVec_create()
{
	IntVec *p = (IntVec*)malloc(sizeof(IntVec));
	p->length = 0;
	p->capacity = 10;
	p->t = (long*)malloc(sizeof(long) * p->capacity);
	
	assert(p && "memory allocation for IntVec failed");
	assert(p->t && "memory allocation for int vector's array failed");
	
	return p;
}

/// inserts an int into the int vector
void IntVec_insert(IntVec *intVec, long val)
{
	assert(intVec && "intVec is null");
	
	IntVec *p = intVec;
	
	if( p->length == p->capacity )
	{
		p->t = (long*)realloc(p->t, p->capacity * 2 * sizeof(long));
		p->capacity *= 2;
	}
	
	p->t[p->length++] = val;
}

/// removes all strings from the vector
void IntVec_clear(IntVec *intVec)
{
	assert(intVec && "intVec is null");
	
	intVec->length = 0;
}

/// frees all memory allocated for intvec
void IntVec_destroy(IntVec *intVec)
{
	assert(intVec && "intVec is null");
	
	IntVec_clear(intVec);
	free(intVec->t);
	free(intVec);
}
