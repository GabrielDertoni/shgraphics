#ifndef SHGRAPHICS
#define SHGRAPHICS
void setup();
void draw();
int start_shgraphics(int w, int h, int px, int py);
void *thread_input_listener(void *keyPressed);
void rect(int x, int y, int w, int h);
#endif
