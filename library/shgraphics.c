#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <pthread.h>
#include <curses.h>
#include <wchar.h>
#include <locale.h>
#include "shgraphics.h"


// Global variables
char keyPressed = 0;
int width, height;
int pxSize, pySize;
bool stroke = true;
bool fill = true;

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

	while (keyPressed != 27) {
		draw(); // Calls draw function.
		//refresh();
	}

	pthread_join(pthread_id, NULL);
	endwin();

	return 0;
}

void *thread_input_listener() {
	while(keyPressed != 27) {
		keyPressed = getch();
	}

	return NULL;
}

void rect(int x, int y, int w, int h, wchar_t c) {
	for (int i = y; i < y + h; i++)
		for (int pi = 0; pi < pySize; pi++) {
			move(i * pySize + pi, x * pxSize);
			for (int j = 0; j < w * pxSize; j++) {
				printw("%lc", c);
			}
		}
}

void line(int x1, int y1, int x2, int y2) {
	x1 *= pxSize;
	y1 *= pySize;
	x2 *= pxSize;
	y2 *= pySize;
	double slope, increment;
	double steps = (double)(abs(x2 - x1) + abs(y2 - y1));
	if ((y2 - y1) > (x2 - x1)) {
		increment = (double)(y2 - y1) / steps;
		slope = (double)(x2 - x1) / (double)(y2 - y1);
	} else {
		increment = (double)(x2 - x1) / steps;
		slope = (double)(y2 - y1) / (double)(x2 - x1);
	}

	for (int i = 1; i <= steps; i++) {
		double p = (double)i * increment;
		double err = fabs(p - round(p)) + fabs((p * slope) - round(p * slope));
		wchar_t prt = L'\x2591';
		if (err > 0.6666) prt = L'\x2593';
		else if (err > 0.3333) prt = L'\x2592';

		double y, x;
		if ((y2 - y1) > (x2 - x1)) {
			y = (double)y1 + p;
			x = (double)x1 + p * slope;
		} else {
			y = (double)y1 + p * slope;
			x = (double)x1 + p;
		}

		mvprintw((int)round(y), (int)round(x), "%lc", L'\x2588');
		if (round(y) != y) {
			if (round(y) == floor(y)) mvprintw((int)ceil(y), (int)round(x), "%lc", prt);
			else if (round(y) == ceil(y)) mvprintw((int)floor(y), (int)round(x), "%lc", prt);
		}
	}
}

void triangle(int x1, int y1, int x2, int y2, int x3, int y3) {
	if (stroke) {
		line(x1, y1, x2, y2);
		line(x2, y2, x3, y3);
		line(x3, y3, x1, y1);
	}
}

void ellipse(int x, int y, int rx, int ry) {

}
