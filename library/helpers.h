#include <stdlib.h>
#include <string.h>
#include <time.h>

void delay(int millis) {
	clock_t t = clock();
	int cicles = millis * CLOCKS_PER_SEC / 1000;
	while(clock() < t + cicles); 
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
