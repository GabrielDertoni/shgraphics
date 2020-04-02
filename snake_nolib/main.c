#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <wchar.h>
#include <locale.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h> 
#include <termios.h>
#include <unistd.h>

int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

void reset() {
	printf("\x1b[0m"); // Resets colors
	printf("\x1b[1;1H"); // Move cursor to top
}

typedef struct {
	int width;
	int height;
	int pWidth;
	int pHeight;
	wchar_t *buff;
} Screen;

void clearScreen(Screen screen) {
	for (int y = 0; y < screen.height; y++)
		for (int x = 0; x < screen.width; x++)
			screen.buff[y * screen.width +  x] = L'\x2588';
}

void drawScreen(Screen screen) {
	for (int y = 0; y < screen.height; y++)
		for (int py = 0; py < screen.pHeight; py++) {
			printf("\x1b[%d;1H", y + 1);
			for (int x = 0; x < screen.width; x++) {
/*				if (screen.buff[y * screen.width + x] == '\0') {
					printf("\x1b[%dC", screen.pWidth);
					continue;
				}*/
				for (int px = 0; px < screen.pWidth; px++)
					wprintf(L"%lc", screen.buff[y * screen.width + x]);
		}
	}
}

Screen createWindow(int width, int height, int pWidth, int pHeight) {
	Screen screen;
	screen.width = width / pWidth;
	screen.height = height / pHeight;
	screen.pWidth = pWidth;
	screen.pHeight = pHeight;
	screen.buff = malloc(height * width * sizeof(char));
	clearScreen(screen);
	return screen;
}

void screenWrite(Screen screen, int posX, int posY, char *str) {
	int i = 0;
	while (str[i] != '\0' && posY * screen.width + posX < screen.width * screen.height) {
		screen.buff[posY * screen.width + posX] = str[i];
		i++;
		if (posX + 1 >= screen.width) {
			posX = 0;
			posY++;
		} else
			posX++;
	}
}

void fillRect(Screen screen, int x, int y, int w, int h, wchar_t chr) {
	for (int i = y; i < y + h; i++)
		for (int j = x; j < x + w; j++)
			screen.buff[i * screen.width + j] = chr;
}

struct PosArrayList {
	int posX;
	int posY;
	struct PosArrayList *next;
	struct PosArrayList *prev;
}; 

struct PosArrayList createPosArrayList(int posX, int posY) {
	struct PosArrayList *pal = (struct PosArrayList*)malloc(sizeof(struct PosArrayList));
	pal->posX = posX;
	pal->posY = posY;
	pal->next = NULL;
	pal->prev = NULL;
	return *pal;
}

void *draw(void *keyPressedpt) {
	char *keyPressed = (char *)keyPressedpt;
	Screen screen = createWindow(200, 65, 2, 1);

	float posX = 0, posY = 0;
	float dirX = 1, dirY = 0;
	float speed = 15;
	int tailSize = 1;
	struct PosArrayList tail = createPosArrayList(0, 0);
	bool moved = true;
	bool gameOver = false;

	int foodPosX = rand() % screen.width, foodPosY = rand() % screen.height;

	clock_t t;
	float fps = 0;
	while(!gameOver && *keyPressed != 27) {
		t = clock();
		switch (*keyPressed) {
			case 'w':
			if (dirY == 0) {
				dirX = 0;
				dirY = -1;
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
				dirX = 0;
				dirY = 1;
			}
			break;
			case 'd':
			if (dirX == 0) {
				dirX = 1;
				dirY = 0;
			}
			break;
		}
		clearScreen(screen);

		struct PosArrayList *point = &tail;
		do {
			// fillRect(screen, point->posX, point->posY, 1, 1, L' ');
			screen.buff[point->posY * screen.width + point->posX] = L' ';
			point = point->next;
		} while (point != NULL);

		fillRect(screen, foodPosX, foodPosY, 1, 1, L' ');
		
		if (tail.posX == foodPosX && tail.posY == foodPosY && moved) {
			foodPosX = rand() % screen.width;
			foodPosY = rand() % screen.height;
			point = &tail;
			while (point->next != NULL)
				point = point->next;

			point->next = (struct PosArrayList*)malloc(sizeof(struct PosArrayList));
			point->next->prev = point;
			point->next->posX = point->posX;
			point->next->posY = point->posY;
			point->next->next = NULL;
			moved = false;
			tailSize++;
		}

		char str[8];
		sprintf(str, "%5.2f", fps);
		fillRect(screen, 0, 0, 40 / screen.pWidth, 2, '\0');
		
		drawScreen(screen);
		reset();

		printf("\x1b[1;1HFramerate: %s", str);
		printf(" (%d, %d)", foodPosX, foodPosY);
		printf(" %d", tailSize);
		printf("\x1b[2;1H (%d) (%d)", (int)screen.buff[40 * 200 + 100], (int)screen.buff[700]);
		fflush(stdout);

		t = clock() - t;

		posX += dirX * speed * (float)t / (float)CLOCKS_PER_SEC;
		posY += dirY * speed * (float)t / (float)CLOCKS_PER_SEC;

		if (tail.posX != (int)posX || tail.posY != (int)posY) {
			moved = true;
			point = &tail;
			while (point->next != NULL)
				point = point->next;

			while(point->prev != NULL) {
				if ((int)posX == point->posX && (int)posY == point->posY && point->next != NULL)
					gameOver = true;

				point->posX = point->prev->posX;
				point->posY = point->prev->posY;

				point = point->prev;
			}
			tail.posX = (int)posX;
			tail.posY = (int)posY;
			if (tail.posX < 0 || tail.posX >= screen.width || tail.posY < 0 || tail.posY >= screen.height)
				gameOver = true;
		}

		fps = (float)CLOCKS_PER_SEC / (float)t;
	}
	
	printf("\x1b[%d;1HGAME OVER\n", screen.height);
	
	return NULL;
}
int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "en_US.UTF-8");

	pthread_t thread_id;
	char keyPressed = 0;
	pthread_create(&thread_id, NULL, draw, (void *)&keyPressed);
	
	while (keyPressed != 27) {
		keyPressed = getch();
	}

	pthread_join(thread_id, NULL);
	return 0;
}
