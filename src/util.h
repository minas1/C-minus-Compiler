#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdint.h>
#include <ctype.h>

#define COLOR_RED_NORMAL		"\x1b[31m"
#define COLOR_GREEN_NORMAL		"\x1b[32m"
#define COLOR_YELLOW_NORMAL		"\x1b[33m"
#define COLOR_BLUE_NORMAL		"\x1b[34m"
#define COLOR_MAGENTA_NORMAL	"\x1b[35m"
#define COLOR_CYAN_NORMAL		"\x1b[36m"

#define COLOR_RED_BOLD			"\x1b[31;1m"
#define COLOR_GREEN_BOLD		"\x1b[32;1m"
#define COLOR_YELLOW_BOLD		"\x1b[33;1m"
#define COLOR_BLUE_BOLD			"\x1b[34;1m"
#define COLOR_MAGENTA_BOLD		"\x1b[35;1m"
#define COLOR_CYAN_BOLD			"\x1b[36;1m"

#define COLOR_RESET				"\x1b[0m"

/// sets the color to one of the above
#define SET_COLOR(x) printf(x)

/// removes all occurences of a given character in str
char* removeChar(char *str, char c);

/// swaps the value of p and q
void swapInt(int *p, int *q);

/// returns the position of "val" in numbers. if not found, returns length
uint32_t findUint32(const uint32_t *numbers, uint32_t length, uint32_t val);

#endif
