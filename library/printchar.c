#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include <curses.h>
#include "printchar.h"

void printchar(int x, int y, char c, wchar_t scr) {
	if (c > 90) c -= 32;

	char str[51];
	switch(c) {
		case 'A':
			strcpy(str,
			"  ######  " 
			"##      ##"
			"##########"
			"##      ##"
			"##      ##");
			break;
		case 'B':
			strcpy(str,
			"########  "
			"##      ##"
			"##########"
			"##      ##"
			"########  ");
			break;
		case 'C':
			strcpy(str,
			"  ######  "
			"##      ##"
			"##        "
			"##      ##"
			"  ######  ");
			break;
		case 'D':
			strcpy(str,
			"########  "
			"##      ##"
			"##      ##"
			"##      ##"
			"########  ");
			
			break;
		case 'E':
			strcpy(str,
			"##########"
			"##        "
			"########  "
			"##        "
			"##########");
			break;
		case 'F':
			strcpy(str,
			"##########"
			"##        "
			"########  "
			"##        "
			"##        ");
			break;
		case 'G':
			strcpy(str,
			"  ########"
			"##        "
			"##  ######"
			"##      ##"
			"  ######  ");
			break;
		case 'H':
			strcpy(str,
			"##      ##"
			"##      ##"
			"##########"
			"##      ##"
			"##      ##");
			break;
		case 'I':
			strcpy(str,
			"##########"
			"    ##    "
			"    ##    "
			"    ##    "
			"##########");
			break;
		case 'J':
			strcpy(str,
			"      ####"
			"        ##"
			"        ##"
			"##      ##"
			"  ######  ");
			break;
		case 'K':
			strcpy(str,
			"##      ##"
			"##    ##  "
			"######    "
			"##    ##  "
			"##      ##");
			break;
		case 'L':
			strcpy(str,
			"##        "
			"##        "
			"##        "
			"##        "
			"##########");
			break;
		case 'M':
			strcpy(str,
			"##      ##"
			"####  ####"
			"##  ##  ##"
			"##      ##"
			"##      ##");
			
			break;
		case 'N':
			strcpy(str,
			"##      ##"
			"####    ##"
			"##  ##  ##"
			"##    ####"
			"##      ##");
			break;
		case 'O':
			strcpy(str,
			"  ######  "
			"##      ##"
			"##      ##"
			"##      ##"
			"  ######  ");
			break;
		case 'P':
			strcpy(str,
			"########  "
			"##      ##"
			"########  "
			"##        "
			"##        ");
			break;
		case 'Q':
			strcpy(str,
			"  ######  "
			"##      ##"
			"##      ##"
			"##    ##  "
			"  ####  ##");
			break;
		case 'R':
			strcpy(str,
			"########  "
			"##      ##"
			"########  "
			"##      ##"
			"##      ##");
			break;
		case 'S':
			strcpy(str,
			"  ########"
			"##        "
			"  ######  "
			"        ##"
			"########  ");
			break;
		case 'T':
			strcpy(str,
			"##########"
			"    ##    "
			"    ##    "
			"    ##    "
			"    ##    ");
			break;
		case 'U':
			strcpy(str,
			"##      ##"
			"##      ##"
			"##      ##"
			"##      ##"
			"  ######  ");
			break;
		case 'V':
			strcpy(str,
			"##      ##"
			"##      ##"
			"##      ##"
			"  ##  ##  "
			"    ##    ");
			
			break;
		case 'W':
			strcpy(str,
			"##      ##"
			"##      ##"
			"##  ##  ##"
			"####  ####"
			"##      ##");
			
			break;
		case 'X':
			strcpy(str,
			"##      ##"
			"  ##  ##  "
			"    ##    "
			"  ##  ##  "
			"##      ##");
			
			break;
		case 'Y':
			strcpy(str,
			"##     ##"
			"  ##  ## "
			"    ##   "
			"    ##   "
			"    ##   ");
			break;
		case 'Z':
			strcpy(str,
			"##########"
			"      ##  "
			"    ##    "
			"  ##      "
			"##########");
			break;
		defalut:
			strcpy(str,
			"##########"
			"##      ##"
			"    ######"
			"          "
			"    ##    ");
	}
	
	for (int i = 0; i < 5; i++) {
		move(y + i, x);
		for (int j = 0; j < 10; j++)
			if (str[10 * i + j] == '#')
				printw("%lc", scr);
			else
				move(y + i, x + j + 1);
	}
}
void printstr(int x, int y, char *str, wchar_t scr) {
	while (*str != '\0') {
		if (*str != ' ')
			printchar(x, y, *str, scr);

		str++;
		x += 11;
	}
}
