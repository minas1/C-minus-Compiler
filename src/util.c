#include "util.h"

#include <string.h>

char* removeChar(char *str, char c)
{
	size_t len = strlen(str);
	size_t i, j;
	
	for(i = 0; i < len; ++i)
	{
		if( str[i] == c )
		{
			for(j = i + 1; j <= len; ++j)
				str[j-1] = str[j];
			
			--i;
			--len;
		}
	}
	
	return str;
}

/// swaps the value of p and q
void swapInt(int *p, int *q)
{
	int temp = *p;
	*p = *q;
	*q = temp;
}

/// returns the position of "val" in numbers. if not found, returns length
uint32_t findUint32(const uint32_t *numbers, uint32_t length, uint32_t val)
{
	uint32_t i;
	for(i = 0; i < length; ++i)
	{
		if( numbers[i] == val )
			return i;
	}
			
	return length;
}
