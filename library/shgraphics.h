#ifndef SHGRAPHICS
#define SHGRAPHICS
#include <wchar.h>

int width, height, pxSize, pySize;
char keyPressed;

void setup();
void draw();
int start_shgraphics(int w, int h, int px, int py);
void *thread_input_listener(void *keyPressed);
void rect(int x, int y, int w, int h, wchar_t c);
void line(int x1, int y1, int x2, int y2);
void triangle(int x1, int y1, int x2, int y2, int x3, int y3);
#endif
