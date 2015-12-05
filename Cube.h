#ifndef CSE167_Cube_h
#define CSE167_Cube_h

#include "Drawable.h"
#include "Geode.h"

class Cube : public Geode {
public:

    float size;

    Cube(float s = 1) : size(s) {

    }

    virtual ~Cube(void) {

    }

    void render() override {
        glutSolidCube(1);
    }
};

#endif

