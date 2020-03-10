#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <curses.h>
#include <wchar.h>
#include <locale.h>
#include "shgraphics.h"


// Global variables
char keyPressed = 0;
int width, height;
int pxSize, pySize;

int start_shgraphics(int w, int h, int px, int py) {
	width = w;
	height = h;
	pxSize = px;
	pySize = py;

	setlocale(LC_ALL, "en_US.UTF-8");
	initscr();
	noecho();
	curs_set(0);
	start_color();
	
	setup(); // Calls setup function.
	
	pthread_t pthread_id;
	pthread_create(&pthread_id, NULL, thread_input_listener, NULL);

	while (keyPressed != 27)
		draw(); // Calls draw function.

	pthread_join(pthread_id, NULL);
	endwin();

	return 0;
}

void *thread_input_listener() {
	while(keyPressed != 27)
		keyPressed = getch();

	return NULL;
}

void rect(int x, int y, int w, int h) {
	for (int i = y; i < y + h; i++)
		for (int pi = 0; pi < pySize; pi++) {
			move(i * pySize + pi, x);
			for (int j = x; j < (x + w) * pxSize; j++) {
				printw("%lc", L'\x2588');
			}
		}
}

void line(int x1, int y1, int x2, int y2) {
	int penX = x1, penY = y1;
	mvprintw(penY, penX, "%ls", L'\x2588');
}

void triangle(int x1, int y1, int x2, int y2, int x3, int y3) {

}

void ellipse(int x, int y, int rx, int ry) {

}
