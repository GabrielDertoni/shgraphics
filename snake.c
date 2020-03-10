#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <curses.h>
#include <pthread.h>
#include <locale.h>
#include <wchar.h>
#include <time.h>

void delay(int millis) {
	clock_t t = clock();
	int cicles = millis * CLOCKS_PER_SEC / 1000;
	while(clock() < t + cicles); 
}

struct Vec2Arr {
	int x, y;
	struct Vec2Arr *next;
	struct Vec2Arr *prev;
};
struct Vec2Arr createVec2Arr(int x, int y) {
	struct Vec2Arr vecarr;
	vecarr.x = x;
	vecarr.y = y;
	vecarr.next = NULL;
	vecarr.prev = NULL;
	return vecarr;
}
/*
void printchar(int x, int y, char c) {
	char str[50];
	switch(c) {
		case 'A':
		{
			char *str =
			"  ██████  " 
			"██      ██"
			"██████████"
			"██      ██"
			"██      ██";
			for (int i = 0; i < 5; i++) {
				mvprintw(y + i, x, "%s", &str[11 * i]);	
			}
			break;
		}
		case 'B':
		{
			char *str =
			"████████  "
			"██      ██"
			"██████████"
			"██      ██"
			"████████  ";
			for (int i = 0; i < 5; i++) {
				mvprintw(y + i, x, "%s", &str[11 * i]);	
			}
			break;
		}
		case 'C':
		{
			wchar_t *str =
			"  ██████  "
			"██      ██"
			"██        "
			"██      ██"
			"  ██████  ";
			for (int i = 0; i < 5; i++) {
				mvprintw(y + i, x, "%.5ls", &str[11 * i]);	
			}
			refresh();
			break;
		}
		case 'D':
		{
			char *str =
			"████████  "
			"██      ██"
			"██      ██"
			"██      ██"
			"████████  ";
			for (int i = 0; i < 5; i++) {
				mvprintw(y + i, x, "%s", &str[11 * i]);	
			}
			break;
		}
		case 'E':
		{
			char *str =
			"██████████"
			"██        "
			"████████  "
			"██        "
			"██████████";
			for (int i = 0; i < 5; i++) {
				mvprintw(y + i, x, "%s", &str[11 * i]);	
			}
			break;
		}
		case 'F':
		{
			char *str =
			"██████████"
			"██        "
			"████████  "
			"██        "
			"██        ";
			for (int i = 0; i < 5; i++) {
				mvprintw(y + i, x, "%s", &str[11 * i]);	
			}
			break;
		}
		case 'G':
		{
			char *str =
			"  ████████"
			"██        "
			"██  ██████"
			"██      ██"
			"  ██████  ";
			for (int i = 0; i < 5; i++) {
				mvprintw(y + i, x, "%s", &str[11 * i]);	
			}
			break;
		}
		case 'H':
		{
			char *str =
			"██      ██"
			"██      ██"
			"██████████"
			"██      ██"
			"██      ██";
			for (int i = 0; i < 5; i++) {
				mvprintw(y + i, x, "%s", &str[11 * i]);	
			}
			break;
		}
		case 'I':
		{
			char *str =
			"██████████"
			"    ██    "
			"    ██    "
			"    ██    "
			"██████████";
			for (int i = 0; i < 5; i++) {
				mvprintw(y + i, x, "%s", &str[11 * i]);	
			}
			break;
		}
		case 'J':
		{
			char *str =
			"      ████"
			"        ██"
			"        ██"
			"██      ██"
			"  ██████  ";
			for (int i = 0; i < 5; i++) {
				mvprintw(y + i, x, "%s", &str[11 * i]);	
			}
			break;
		}
		case 'K':
		{
			char *str =
			"██      ██"
			"██    ██  "
			"██████    "
			"██    ██  "
			"██      ██";
			for (int i = 0; i < 5; i++) {
				mvprintw(y + i, x, "%s", &str[11 * i]);	
			}
			break;
		}
		case 'L':
		{
			char *str =
			"██        "
			"██        "
			"██        "
			"██        "
			"██████████";
			for (int i = 0; i < 5; i++) {
				mvprintw(y + i, x, "%s", &str[11 * i]);	
			}
			break;
		}
		case 'M':
		{
			char *str =
			"██      ██"
			"████  ████"
			"██  ██  ██"
			"██      ██"
			"██      ██";
			for (int i = 0; i < 5; i++) {
				mvprintw(y + i, x, "%s", &str[11 * i]);	
			}
			break;
		}
		case 'N':
		{
			char *str =
			"██      ██"
			"████    ██"
			"██  ██  ██"
			"██    ████"
			"██      ██";
			for (int i = 0; i < 5; i++) {
				mvprintw(y + i, x, "%s", &str[11 * i]);	
			}
			break;
		}
		case 'O':
		{
			char *str =
			"  ██████  "
			"██      ██"
			"██      ██"
			"██      ██"
			"  ██████  ";
			for (int i = 0; i < 5; i++) {
				mvprintw(y + i, x, "%s", &str[11 * i]);	
			}
			break;
		}
		case 'P':
		{
			char *str =
			"████████  "
			"██      ██"
			"████████  "
			"██        "
			"██        ";
			for (int i = 0; i < 5; i++) {
				mvprintw(y + i, x, "%s", &str[11 * i]);	
			}
			break;
		}
		case 'Q':
		{
			char *str =
			"  ██████  "
			"██      ██"
			"██      ██"
			"██    ██  "
			"  ████  ██";
			for (int i = 0; i < 5; i++) {
				mvprintw(y + i, x, "%s", &str[11 * i]);	
			}
			break;
		}
		case 'R':
		{
			char *str =
			"████████  "
			"██      ██"
			"████████  "
			"██      ██"
			"██      ██";
			for (int i = 0; i < 5; i++) {
				mvprintw(y + i, x, "%s", &str[11 * i]);	
			}
			break;
		}
		case 'S':
		{
			char *str =
			"  ████████"
			"██        "
			"  ██████  "
			"        ██"
			"████████  ";
			for (int i = 0; i < 5; i++) {
				mvprintw(y + i, x, "%s", &str[11 * i]);	
			}
			break;
		}
		case 'T':
		{
			char *str =
			"██████████"
			"    ██    "
			"    ██    "
			"    ██    "
			"    ██    ";
			for (int i = 0; i < 5; i++) {
				mvprintw(y + i, x, "%s", &str[11 * i]);	
			}
			break;
		}
		case 'U':
		{
			char *str =
			"██      ██"
			"██      ██"
			"██      ██"
			"██      ██"
			"  ██████  ";
			for (int i = 0; i < 5; i++) {
				mvprintw(y + i, x, "%s", &str[11 * i]);	
			}
			break;
		}
		case 'V':
		{
			char *str =
			"██      ██"
			"██      ██"
			"██      ██"
			"  ██  ██  "
			"    ██    ";
			for (int i = 0; i < 5; i++) {
				mvprintw(y + i, x, "%s", &str[11 * i]);	
			}
			break;
		}
		case 'W':
		{
			char *str =
			"██      ██"
			"██      ██"
			"██  ██  ██"
			"████  ████"
			"██      ██";
			for (int i = 0; i < 5; i++) {
				mvprintw(y + i, x, "%s", &str[11 * i]);	
			}
			break;
		}
		case 'X':
		{
			char *str =
			"██      ██"
			"  ██  ██  "
			"    ██    "
			"  ██  ██  "
			"██      ██";
			for (int i = 0; i < 5; i++) {
				mvprintw(y + i, x, "%s", &str[11 * i]);	
			}
			break;
		}
		case 'Y':
		{
			char *str =
			"██     ██"
			"  ██  ██ "
			"    ██   "
			"    ██   "
			"    ██   ";
			for (int i = 0; i < 5; i++) {
				mvprintw(y + i, x, "%s", &str[11 * i]);	
			}
			break;
		}
		case 'Z':
		{
			char *str =
			"██████████"
			"      ██  "
			"    ██    "
			"  ██      "
			"██████████";
			for (int i = 0; i < 5; i++) {
				mvprintw(y + i, x, "%s", &str[11 * i]);	
			}
			break;
		}
		defalut:
		{
			char *str =
			"██████████"
			"██      ██"
			"    ██████"
			"          "
			"    ██    ";
			for (int i = 0; i < 5; i++) {
				mvprintw(y + i, x, "%s", &str[11 * i]);	
			}
		}
	}
}
void printstr(int x, int y, char *str) {
	while (str != '\0') {
		printchar(x, y, *str);
		str++;
		x += 11;
	}
}
*/
// Thread functions that implements the game loop.
void *draw(void *keyPressedpt) {
	char *keyPressed = (char *)keyPressedpt;

	int sWidth = 200, sHeight = 65;
	/*int pxSize = 2, pySize = 1;*/
	int pxSize = 4, pySize = 2;
	float pRatio = (float)pxSize / (float)pySize;

	bool gameOver = false;
	float speed = 15; // Speed in characters per second.
	int posX = 1, posY = 1, dirX = 1, dirY = 0;
	struct Vec2Arr tail = createVec2Arr(posX, posY);

	int foodPosX = rand() % (sWidth / pxSize), foodPosY = rand() % (sHeight / pySize);
	
	while(*keyPressed != 27 && !gameOver) {
		clear(); // Clears the screen every frame.
		for (int px = 0; px < pxSize; px++)
			for (int py = 0; py < pySize; py++) {
				// Draws the "pixel" wich has a width and height of characters.
				mvprintw(pySize * posY + py, pxSize * posX + px, "%lc", L'\x2588');

				// Draws all the tail "pixels" with a pointer that goes through all
				// elements of the array list.
				struct Vec2Arr *ptr = &tail;
				while (ptr != NULL) {
					mvprintw(pySize * ptr->y + py, pxSize * ptr->x + px, "%lc", L'\x2588');
					ptr = ptr->next;
				}
				
				// Draws the food in red
				attron(COLOR_PAIR(1));
				mvprintw(pySize * foodPosY + py, pxSize * foodPosX + px, "%lc", L'\x2588');
				attroff(COLOR_PAIR(1));
			}

		refresh(); // Refreshes the screen so all of the "pixels" are drawn.
		// Checks the last key press and changes the direction based on that.
		switch (*keyPressed) {
			case 'w':
			if (dirY == 0) {
				dirY = -1;
				dirX = 0;
			}
			break;
			case 'a':
			if (dirX == 0) {
				dirX = -1;
				dirY = 0;
			}
			break;
			case 's':
			if (dirY == 0) {
				dirY = 1;
				dirX = 0;
			}
			break;
			case 'd':
			if (dirX == 0) {
				dirX = 1;
				dirY = 0;
			}
			break;
		}

		if (posX == foodPosX && posY == foodPosY) {
			// Adds a new food in a different random location.
			foodPosX = rand() % (sWidth / pxSize);
			foodPosY = rand() % (sHeight / pySize);

			// Creates a pointer of the array list "tail" and points it
			// to the leaf (tip) of the array list.
			struct Vec2Arr *ptr = &tail;
			while (ptr->next != NULL)
				ptr = ptr->next;

			// Appends a new element in the tail array list 
			// The new element has the same position as the last tail.
			ptr->next = (struct Vec2Arr *)malloc(sizeof(struct Vec2Arr));
			ptr->next->x = ptr->x;
			ptr->next->y = ptr->y;
			ptr->next->prev = ptr;
			ptr->next->next = NULL;
		}
		// Updates the position of the entire tail.
		struct Vec2Arr *ptr = &tail;
		while (ptr->next != NULL)
			ptr = ptr->next;

		while (ptr->prev != NULL) {
			ptr->x = ptr->prev->x;
			ptr->y = ptr->prev->y;
			// If the snake hits itself, game over.
			if (ptr->x == posX && ptr->y == posY)
				gameOver = true;

			ptr = ptr->prev;
		}
		tail.x = posX;
		tail.y = posY;

		posX += dirX;
		posY += dirY;

		// If the snake hits the boundaries, game over.
		if (posX < 0 || posX >= (sWidth / pxSize) || posY < 0 || posY >= (sHeight / pySize))
			gameOver = true;

		// Adds a delay between iterations so everithing moves at the correct speed.
		delay((int)(1000 / speed));
	}

	if (gameOver) {
		mvprintw(sHeight/2, sWidth/2 - 14, "GAME OVER - Pess ESC to exit");
		//printstr(sHeight / 2, sWidth / 2 - 4, "GAME OVER");
		refresh();
	}

	return NULL;
}
/*
void *testfunc(void *keypressed) {
	printchar(10, 10, 'C');
	return NULL;
}
*/
int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "en_US.UTF-8");
	srand(time(0)); // Use current time as seed for random numbers.

	char keyPressed = 0;
	initscr();
	noecho();
	curs_set(0);
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	
	// Creates the thread for the game loop.
	pthread_t pthread_id;
	pthread_create(&pthread_id, NULL, draw, (void *)&keyPressed);
	//pthread_create(&pthread_id, NULL, testfunc, (void *)&keyPressed);
	// Listens for key presses at every point. If it is an ESC, quit the program.
	while (keyPressed != 27)
		keyPressed = getch();

	// Waits for thread to finish (automatically done when ESC is pressed)
	pthread_join(pthread_id, NULL);
	endwin();

	return 0;
}
