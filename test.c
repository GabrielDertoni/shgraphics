#include <stdio.h>
#include <ncurses.h>
#include <pthread.h>


void *inpt(void *keyPressed) {
	char *charPressed = (char *)keyPressed;

	while (*charPressed != 27)
		*charPressed = getch();

	return NULL;
}
int main() {
	initscr();

	char keyPressed = 0;
	pthread_t pthread_id;
	pthread_create(&pthread_id, NULL, inpt, (void *)&keyPressed);
	pthread_join(pthread_id, NULL);

	endwin();
	
	return 0;
}
