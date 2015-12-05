#ifndef CSE167_Drawable_h
#define CSE167_Drawable_h

#include <iostream>
#include "Matrix4.h"
#include "DrawData.h"
#include "UpdateData.h"
#include "Material.h"
#include <float.h>
#include <math.h>
#include <vector>


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Drawable {
public:
   // static const float PI;

    Matrix4 toWorld;
    Material material;

    Drawable(void);
    virtual ~Drawable(void);

    virtual void draw(MatrixStack&);
    virtual void update(UpdateData&);
    bool operator==(const Drawable&) const;

    void spin(float radians);


};

#endif
