#ifndef CSE167_Window_h
#define CSE167_Window_h

#include "Mouse.h"

#include <cmath>

class Window // OpenGL output window related routines
{
public:

    static int width, height; // window size

    static float spinDelta;

    static void initialize(void);
    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
    static bool handleKeypress(unsigned char key);
    static void specialKeys(int key, int x, int y);
    static void mouseClick(int butt, int state, int x, int y);
    static void mouseMove(int x, int y);
	static void setupGBuffer();
	static void renderQuad();
};

#endif

