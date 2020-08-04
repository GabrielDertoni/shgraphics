#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>
#include <stdbool.h>
#include <locale.h>
#include "../library/printchar.h"

#define CHUNK 50

char *getLine(char *str);
int readFile(char **write, FILE *file);

FILE *fp;
WINDOW *win;
int width;
int height;

char *text;
char *typed;
int length;
int words;
int curr_i;
char keyPressed;
bool hasStarted = false;
bool hasEnded = false;
int line_start = 0;
time_t start, end;


bool endWord(char c) {
	char wordEndingChar[] = "\n .,?!()[]{}<>:;\"'|@#%^&`+-*/=";
	for (int i = 0; wordEndingChar[i] != '\0'; i++)
		if (wordEndingChar[i] == c) return true;

	return false;
}

void setup() {
	curr_i = 0;
	keyPressed = 0;

	length = readFile(&text, fp);
	words = 0;
	for (int i = 0; i < length; i++) {
		if (endWord(text[i])) {
			words++;
			while (endWord(text[i + 1])) i++;
		}
	}
	mvprintw(1, 4, "Words: %d", words);
	typed = (char *)malloc(length * sizeof(char));
}

void draw() {
	if (curr_i > 0 && curr_i < length)
		if (text[curr_i - 1] == '\n' && keyPressed == text[curr_i - 1]) {
			line_start++;
			clear();
		}

	int line = height / 2 - line_start;
	int line_length = 0;
	move(line, 4);
	for (int i = 0; i < length && line < 35 && !hasEnded; i++) {
		for (; line < 0; i++)
			if (text[i] == '\n') line++;

		if (i == curr_i) attron(COLOR_PAIR(2));
		else if (text[i] != typed[i] && curr_i > i) attron(COLOR_PAIR(3));

		if (line_length + 10 > width) {
			move(++line, 4);
			line_length = 0;
		}

		if (text[i] == '\n') {
			if (i != curr_i && (text[i] == typed[i] || curr_i < i)) attron(COLOR_PAIR(1));
			printw("%lc", L'\x21b2'); // ↲
			if (i != curr_i && (text[i] == typed[i] || curr_i < i)) attroff(COLOR_PAIR(1));
			move(++line, 4);
			line_length = 0;
		} else {
			addch(text[i]);
			line_length++;
		}

		if (i == curr_i) attroff(COLOR_PAIR(2));
		else if (text[i] != typed[i] && curr_i > i) attroff(COLOR_PAIR(3));
	}
	refresh();

	if (curr_i == length && !hasEnded) {
		int wrong;
		for (int i = 0; i < length; i++)
			if (text[i] != typed[i]) wrong++;

		double accuracy = (1 - (double)wrong / (double)length) * 100;

		time(&end);
		double time_taken = difftime(end, start);
		double wpm = (double)words / (time_taken / 60);
		char str[7];
		sprintf(str, "%3.2lf", wpm);
		attron(COLOR_PAIR(4));
		//mvprintw(height / 2 - 7, width / 2 - 5, "%s wpm", str);
		printstr(width / 2 - 31, height / 2 - 6, str, L'\x2592');
		printstr(width / 2 - 30, height / 2 - 6, str, FULL_BLOCK);
		printstr(width / 2 - 16, height / 2, "WPM", L'\x2592');
		printstr(width / 2 - 15, height / 2, "WPM", FULL_BLOCK);
		attroff(COLOR_PAIR(4));

		attron(COLOR_PAIR(5));
		char acc[10];
		sprintf(acc, "%3.2lf%%", accuracy);
		printstr(width / 2 - 31, height / 2 + 6, acc, L'\x2592');
		printstr(width / 2 - 30, height / 2 + 6, acc, FULL_BLOCK);
		attroff(COLOR_PAIR(5));

		hasEnded = true;
	}

	keyPressed = getch();
	if (keyPressed == 127) {
		if (text[--curr_i] == '\n') {
			line_start--;
			clear();
		}
	} else if (curr_i < length) {
		typed[curr_i++] = keyPressed;
	}

	if (!hasStarted) {
		time(&start);
		hasStarted = true;
	}
}

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "en_US.UTF-8");
	if (argc > 1)
		fp = fopen(argv[1], "r");
	else
		fp = fopen("/Users/gabrieldertoni/Desktop/Projetos em Programa/shgraphics/typing/main.c", "r");

	win = initscr();
	getmaxyx(win, height, width);
	noecho();
	curs_set(0);
	start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, COLOR_WHITE);
	init_pair(3, COLOR_BLACK, COLOR_RED);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(5, COLOR_YELLOW, COLOR_BLACK);

	setup();
	while (keyPressed != 27 && length >= curr_i)
		draw();

	endwin();
	fclose(fp);

	return 0;
}
int readFile(char **write, FILE *file) {
	// Registra a quantidade de memória alocada ( + 1 para '\0').
	int allocated = CHUNK + 1;
	char *string = (char *)malloc(allocated); // Aloca chunk de memória.
	char c = getc(file);

	int len;
	for (len = 0; c != EOF; len++) {
		// Caso a memória alocada tenha terminado, aloca outro chunk.
		if (len >= allocated - 1) {
			allocated += CHUNK;
			char *temp = (char *)realloc(string, allocated);
			string = temp;
		}
		string[len] = c; // Escreve a entrada na memória.
		c = getc(file);

		if (c == EOF)
			string[len + 1] = '\0'; // Adiciona '\0' ao final.
	}
	*write = string;
	return len;
}
