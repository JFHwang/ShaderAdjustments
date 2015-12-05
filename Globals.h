#ifndef CSE167_Globals_h
#define CSE167_Globals_h

using namespace std;

#include <set>
#include <list>
#include <cmath>
#include <algorithm>

#include "Camera.h"
#include "Light.h"
#include "DrawData.h"
#include "UpdateData.h"
#include "OBJObject.h"
#include "Shader.h"

#define clampf(min,max,num) (num < min ? min : num > max ? max : num)
#define PI (3.14159265)
#define renderWithMatrix(transform, DRAW_CALL) ({glPushMatrix(); glMultMatrixf(transform.ptr()); DRAW_CALL glPopMatrix(); })


int fact(int n);
int choose(int n, int k);

inline float RAD(float degrees) {
    return degrees * PI / 180.0;
}

template<typename T> inline void print(T output) {
    cout << output << endl;
}

float frand(float a, float b);

inline void cube() {
   // Shader& s = *new Shader("VShader.c", "LShader.c");
    // White side - BACK
    //s.bind();
    glBegin(GL_QUADS);
    glNormal3f(0, 0, -1);
    glVertex3f(0.5, -0.5, -0.5); // P1 is red
    glNormal3f(0, 0, -1);
    glVertex3f(0.5, 0.5, -0.5); // P2 is green
    glNormal3f(0, 0, -1);
    glVertex3f(-0.5, 0.5, -0.5); // P3 is blue
    glNormal3f(0, 0, -1);
    glVertex3f(-0.5, -0.5, -0.5); // P4 is purple



    glNormal3f(0, 0, 1);
    glVertex3f(0.5, -0.5, 0.5);
    glNormal3f(0, 0, 1);
    glVertex3f(0.5, 0.5, 0.5);
    glNormal3f(0, 0, 1);
    glVertex3f(-0.5, 0.5, 0.5);
    glNormal3f(0, 0, 1);
    glVertex3f(-0.5, -0.5, 0.5);

    // Purple side - RIGHT
    glNormal3f(1, 0, 0);
    glVertex3f(0.5, -0.5, -0.5);
    glNormal3f(1, 0, 0);
    glVertex3f(0.5, 0.5, -0.5);
    glNormal3f(1, 0, 0);
    glVertex3f(0.5, 0.5, 0.5);
    glNormal3f(1, 0, 0);
    glVertex3f(0.5, -0.5, 0.5);

    // Green side - LEFT
    glNormal3f(-1, 0, 0);
    glVertex3f(-0.5, -0.5, 0.5);
    glNormal3f(-1, 0, 0);
    glVertex3f(-0.5, 0.5, 0.5);
    glNormal3f(-1, 0, 0);
    glVertex3f(-0.5, 0.5, -0.5);
    glNormal3f(-1, 0, 0);
    glVertex3f(-0.5, -0.5, -0.5);

    // Blue side - TOP
    glNormal3f(0, 1, 0);
    glVertex3f(0.5, 0.5, 0.5);
    glNormal3f(0, 1, 0);
    glVertex3f(0.5, 0.5, -0.5);
    glNormal3f(0, 1, 0);
    glVertex3f(-0.5, 0.5, -0.5);
    glNormal3f(0, 1, 0);
    glVertex3f(-0.5, 0.5, 0.5);

    // Red side - BOTTOM
    glNormal3f(0, -1, 0);
    glVertex3f(0.5, -0.5, -0.5);
    glNormal3f(0, -1, 0);
    glVertex3f(0.5, -0.5, 0.5);
    glNormal3f(0, -1, 0);
    glVertex3f(-0.5, -0.5, 0.5);
    glNormal3f(0, -1, 0);
    glVertex3f(-0.5, -0.5, -0.5);

    glEnd();
   // s.unbind();
}

class Globals {
public:
    static bool isBoundsOn, isAnimated;

    static Camera camera;
    static Light light;
    static MatrixStack drawData;
    static UpdateData updateData;
    //   static OBJObject dragon, bunny, bear;
    static Light point, spotLight, directional;

    //Feel free to add more member variables as needed

    static std::list<OBJObject*> drawables;

    static void add(OBJObject& d) {
        drawables.push_back(&d);
    }

    static bool remove(OBJObject& d) {
        const bool found = std::find(drawables.begin(), drawables.end(), &d) != drawables.end();
        if (found)
            drawables.remove(&d);
        return found;
    }

};

#endif
