#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <wchar.h>
#include <curses.h>
#include "shgraphics.h"

int frameCount;
int rows, columns;
bool *cells;

void update_state(int s_row, int e_row);
void *update_state_wrapper(void *index);

void delay(int millis) {
	clock_t t = clock();
	int cicles = millis * CLOCKS_PER_SEC / 1000;
	while(clock() < t + cicles); 
}
void setup() {
	frameCount = 0;
	rows = height / pySize;
	columns = width / pxSize;

	cells = (bool *)malloc(rows * columns * sizeof(bool));
	// Initialize all cells as random values.
	for (int r = 0; r < rows; r++) 
		for (int c = 0; c < columns; c++)
			cells[r*columns+c] = rand() % 2;

}
void draw() {
	frameCount++;
	clock_t t = clock();
	
	int nthreads = 4;
	pthread_t tid[nthreads];
	for (int i = 0; i < nthreads; i++) {
		int *j = (int *)malloc(sizeof(int));
		*j = i;
		pthread_create(tid + i, NULL, update_state_wrapper, j);
	}

	for (int r = 0; r < rows; r++) 
		for (int c = 0; c < columns; c++) {
			if (cells[r * columns + c])
				rect(c, r, 1, 1, L'\x2588');
			else
				rect(c, r, 1, 1, ' ');
		}

	mvprintw(1, 1, "%.2lf", CLOCKS_PER_SEC / (double)(clock() - t));
	refresh();

	for (int i = 0; i < nthreads; i++)
		pthread_join(tid[i], NULL);

	delay(100);
}

void *update_state_wrapper(void *index) {
	int s_row = (*((int *)index)) * rows / 4;
	int e_row = ((*((int *)index)) + 1) * rows / 4;
	update_state(s_row, e_row);
	free(index);

	return NULL;
}

void update_state(int s_row, int e_row) {
	int _rows = e_row - s_row;
	bool *temp = (bool *)malloc(_rows * columns * sizeof(bool));

	for (int r = 0; r < _rows; r++) 
		for (int c = 0; c < columns; c++) {
			int count = 0;
			for (int x = -1; x <= 1; x++)
				for (int y = -1; y <= 1; y++) {
					if (c + x > 0 && c + x < columns &&
						r + y + s_row    > 0 && r + y  + s_row    < rows)
						if (cells[(r + y + s_row) * columns + c + x]) count++;
				}

			if (cells[(r + s_row) * columns + c]) {
				if (count - 1 < 2) temp[r * columns + c] = false;
				else if (count - 1 > 3) temp[r * columns + c] = false;
				else temp[r * columns + c] = true;
			} else {
				if (count == 3) temp[r * columns + c] = true;
				else temp[r * columns + c] = false;
			}
		}

	memcpy(cells + s_row * columns, temp, _rows * columns * sizeof(bool));
	free(temp);
}

void parse_args(int argc, char *argv[], int *w, int *h, int *px, int *py) {
	*w = 200;
	*h = 45;
	*px = 2;
	*py = 1;
	if (argc > 1) {
		for (int i = 1; i < argc; i++) {
			if (strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--width") == 0) {
				if (argc > i + 1) {
					*w = atoi(argv[i + 1]);
					i++;
				} else {
					printf("--width, -w requires a number.");
					return;
				}
			} else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--width") == 0) {
				if (argc > i + 1) {
					*h = atoi(argv[i + 1]);
					i++;
				} else {
					printf("--height, -h requires a number.");
					return;
				}
			} else if (strcmp(argv[i], "-px") == 0 || strcmp(argv[i], "--pixelWidth") == 0) {
				if (argc > i + 1) {
					*px = atoi(argv[i + 1]);
					i++;
				} else {
					printf("--pixelWidth, -px requires a number.");
				}
			} else if (strcmp(argv[i], "-py") == 0 || strcmp(argv[i], "--pixelHeight") == 0) {
				if (argc > i + 1) {
					*py = atoi(argv[i + 1]);
					i++;
				} else {
					printf("--pixelHeight, -py requires a number.");
				}
			}
		}
	}
}

int main(int argc, char *argv[]) {
	srand(time(0));
	int w, h, px, py;
	parse_args(argc, argv, &w, &h, &px, &py);

	start_shgraphics(w, h, px, py);

	return 0;
}
