#include <stdio.h>
#include <curses.h>
#include "library/helpers.h"
#include "library/shgraphics.h"
#include "library/printchar.h"

#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3

#define TOP_LEFT L'\x250F' // ┏
#define TOP_RIGHT L'\x2513' // ┓
#define BOTTOM_LEFT L'\x2517' // ┗
#define BOTTOM_RIGHT L'\x251B' // ┛
#define HORIZONTAL L'\x2501' // ━
#define VERTICAL L'\x2503' // ┃

#define BOOL short int
#define FALSE 0
#define TRUE 1

typedef struct vec {
	int x;
	int y;
	int dx;
	int dy;
} vec;

typedef struct vecList {
	vec *v;
	struct vecList *next;
	struct vecList *prev;
} vecList;

vec p1;
vecList *p1tail;
vec p2;
vecList *p2tail;

BOOL gameOver = FALSE;
short int winner = 0;

vecList *createVecList(vec *vector);
vecList *appendVecList(vecList *list, int x, int y, int dx, int dy);
vecList *insertVecList(vecList *list, int index, int x, int y, int dx, int dy);
void setDirection(vec *vector, int dir);
short int getDirection(vec *vector);
wchar_t getTurn(vec *prev, vec *next);
int sign(int val);
void checkPlayers();
void updatePlayer(vecList *ptail, int id);

void setup() {
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);

	p1.x = 1;
	p1.y = height / (2 * pySize);
	setDirection(&p1, RIGHT);
	p1tail = createVecList(&p1);

	p2.x = 1;
	p2.y = height / (2 * pySize) + 4;
	setDirection(&p2, RIGHT);
	p2tail = createVecList(&p2);

}

void draw() {
	if (!gameOver) {
		clear();

		attron(COLOR_PAIR(2));
		for (vecList *p = p1tail; p != NULL; p = p->next)
			if (p->prev != NULL)
				rect(p->v->x, p->v->y, 1, 1, getTurn(p->v, p->prev->v));
			else
				rect(p->v->x, p->v->y, 1, 1, getTurn(p->v, p->v));
		
		attroff(COLOR_PAIR(2));
		attron(COLOR_PAIR(3));
		for (vecList *p = p2tail; p != NULL; p = p->next)
			if (p->prev != NULL)
				rect(p->v->x, p->v->y, 1, 1, getTurn(p->v, p->prev->v));
			else
				rect(p->v->x, p->v->y, 1, 1, getTurn(p->v, p->v));
		
		attroff(COLOR_PAIR(3));

		updatePlayer(p1tail, 1);
		updatePlayer(p2tail, 2);

		if (p1.x < 0 || p1.x > width / pxSize || p1.y < 0 || p1.y > height / pySize) {
			gameOver = TRUE;
			winner = 2;
		}
		if (p2.x < 0 || p2.x > width / pxSize || p2.y < 0 || p2.y > height / pySize) {
			gameOver = TRUE;
			winner = 1;
		}

		refresh();

		delay(100);
	} else {
		//mvprintw(height / 2, width / 2 - 5, "GAME OVER!");
		//mvprintw(height / 2 + 2, width / 2 - 8, "Winner is: %s", winner == 1 ? "RED" : "BLUE");
		printstr(width / 2 - 61, height / 2 - 5, "GAME OVER", L'\x2592');
		printstr(width / 2 - 60, height / 2 - 5, "GAME OVER", L'\x2588');
		if (winner == 1) {
			attron(COLOR_PAIR(2));
			printstr(width / 2 - 51, height / 2 + 1, "RED WINS", L'\x2592');
			printstr(width / 2 - 50, height / 2 + 1, "RED WINS", L'\x2588');
			attroff(COLOR_PAIR(2));
		} else {
			attron(COLOR_PAIR(3));
			printstr(width / 2 - 61, height / 2 + 1, "BLUE WINS", L'\x2592');
			printstr(width / 2 - 60, height / 2 + 1, "BLUE WINS", L'\x2588');
			attroff(COLOR_PAIR(3));
		}

		refresh();
		delay(500);
	}
}

int main(int argc, char *argv[]) {
	int w, h, px, py;
	parse_args(argc, argv, &w, &h, &px, &py);
	start_shgraphics(w, h, 1, 1);

	return 0;
}

void updatePlayer(vecList *ptail, int id) {
	for (int i = 0; i < abs(ptail->v->dx) || i < abs(ptail->v->dy); i++) {
		insertVecList(ptail, 1, ptail->v->x, ptail->v->y, ptail->v->dx, ptail->v->dy);
		if (ptail->v->dx == 0) {
			if ((keyPressed == 'd' && id == 1) || (keyPressed == 'l' && id == 2)) {
				setDirection(ptail->v, RIGHT);
			} else if ((keyPressed == 'a' && id == 1) || (keyPressed == 'j' && id == 2)) {
				setDirection(ptail->v, LEFT);
			}
		} else if (ptail->v->dy == 0) {
			if ((keyPressed == 'w' && id == 1) || (keyPressed == 'i' && id == 2)) {
				setDirection(ptail->v, UP);
			} else if ((keyPressed == 's' && id == 1) || (keyPressed == 'k' && id == 2)) {
				setDirection(ptail->v, DOWN);
			}
		}

		ptail->v->x += sign(ptail->v->dx);
		ptail->v->y += sign(ptail->v->dy);

		checkPlayers();
	}
}

void setDirection(vec *vector, int dir) {
	vector->dx = 0;
	vector->dy = 0;
	switch (dir) {
		case 0:
			vector->dy = -1;
			return;
		case 1:
			vector->dx = -2;
			return;
		case 2:
			vector->dy = 1;
			return;
		case 3:
			vector->dx = 2;
			return;
	}
}

short int getDirection(vec *vector) {
	if (vector->dx == 0) {
		if (vector->dy > 0) return DOWN;
		else return UP;
	} else if (vector->dx < 0) return LEFT;
	else return RIGHT;
}

wchar_t getTurn(vec *prev, vec *next) {
	if (prev->dx > 0) { // Prev going right
		if (next->dy > 0) return TOP_RIGHT;
		else if (next->dy < 0) return BOTTOM_RIGHT;
		else if (next->dx != 0) return HORIZONTAL;
		else return ' ';
	} else if (prev->dx < 0) { // Prev going left
		if (next->dy > 0) return TOP_LEFT;
		else if (next->dy < 0) return BOTTOM_LEFT;
		else if (next->dx != 0) return HORIZONTAL;
		else return ' ';
	} else if (prev->dy > 0) {
		if (next->dx > 0) return BOTTOM_LEFT;
		else if (next->dx < 0) return BOTTOM_RIGHT;
		else if (next->dy != 0) return VERTICAL;
		else return ' ';
	} else if (prev-> dy < 0) {
		if (next->dx > 0) return TOP_LEFT;
		else if (next->dx < 0) return TOP_RIGHT;
		else if (next->dy != 0) return VERTICAL;
		else return ' ';
	} else {
		return ' ';
	}
}

int sign(int val) {
	if (val > 0) return 1;
	if (val < 0) return -1;
	return 0;
}

void checkPlayers() {
		for (vecList *p = p1tail; p != NULL; p = p->next)
			if (p != p1tail && p1.x == p->v->x && p1.y == p->v->y) {
				gameOver = TRUE;
				winner = 2;
			} else if (p != p1tail && p2.x == p->v->x && p2.y == p->v->y) {
				gameOver = TRUE;
				winner = 1;
			}

		for (vecList *p = p2tail; p != NULL; p = p->next)
			if (p != p2tail && p2.x == p->v->x && p2.y == p->v->y) {
				gameOver = TRUE;
				winner = 1;
			} else if (p != p2tail && p1.x == p->v->x && p1.y == p->v->y) {
				gameOver = TRUE;
				winner = 2;
			}
}

vecList *createVecList(vec *vector) {
	vecList *list = (vecList *)malloc(sizeof(vecList));
	list->v = vector;
	list->next = NULL;
	list->prev = NULL;

	return list;
}

vecList *appendVecList(vecList *list, int x, int y, int dx, int dy) {
	vec *temp = (vec *)malloc(sizeof(vec));
	temp->x = x;
	temp->y = y;
	temp->dx = dx;
	temp->dy = dy;
	
	vecList *newlist = (vecList *)malloc(sizeof(vecList));
	newlist->v = temp;
	newlist->next = NULL;

	vecList *last = list;
	while (last->next != NULL) last = last->next;
	last->next = newlist;
	newlist->prev = last;

	return newlist;
}

vecList *insertVecList(vecList *list, int index, int x, int y, int dx, int dy) {
	vec *temp = (vec *)malloc(sizeof(vec));
	temp->x = x;
	temp->y = y;
	temp->dx = dx;
	temp->dy = dy;

	vecList *newlist = (vecList *)malloc(sizeof(vecList));
	newlist->v = temp;

	vecList *last = list;
	int i;
	for(i = 0; i < index && last->next != NULL; i++, last = last->next);

	// If the loop has exited without i < index false, it means that it wants to append
	// the newlist at the end of list.
	if (i < index) {
		newlist->next = NULL;
		newlist->prev = last;
		last->next = newlist;
	} else {
		// Else, it means newlist should be inserted in the middle of the list.
		newlist->next = last;
		newlist->prev = last->prev;
		if (last->prev != NULL)
			last->prev->next = newlist;

		last->prev = newlist;
	}
	if (index == 0) return newlist;
	return list;
}
