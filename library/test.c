#include <stdio.h>
#include <curses.h>
#include "shgraphics.h"

void setup() {
	mvprintw(10, 10, "Hello world");
	rect(10, 11, 10, 5);
}

void draw() {
}

int main() {
	start_shgraphics(200, 65, 2, 1);

	return 0;
}

