#ifndef PRINTCHAR
#define PRINTCHAR
#include <wchar.h>

#define FULL_BLOCK L'\x2588'
void printchar(int x, int y, char c, wchar_t scr);
void printstr(int x, int y, char *str, wchar_t scr);
#endif
