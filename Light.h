#ifndef CSE167_Light_h
#define CSE167_Light_h

#include "Matrix4.h"
#include "Vector4.h"
#include "Color.h"
#include "Drawable.h"
#include <vector>
#include "Vector3.h"

class Light : public Drawable {
protected:

    int bindID;


public:

    enum Type {
        POINT_LIGHT, SPOT_LIGHT, DIRECTIONAL_LIGHT
    };

    Type type;

    Color ambientColor;
    Color diffuseColor;
    Color specularColor;

    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;
    float exp;
    float angle;

public:

    Light(int id, Type t);
    virtual ~Light(void);

    void bind();
    void unbind(void);

    void setPosition(Vector4 pos) {
        toWorld.setTranslation(pos.toVector3());
         if (type == DIRECTIONAL_LIGHT) {
            toWorld.setTranslation(toWorld.getColumn(3).toVector3().normalize().scale(5000));
        }
    }

    void setPosition(Vector3 pos) {
        toWorld.setTranslation(pos);
        if (type == DIRECTIONAL_LIGHT) {
            toWorld.setTranslation(toWorld.getColumn(3).toVector3().normalize().scale(5000));
        }
    }
    
    void scaleIntensity(float amount);

    void draw(MatrixStack& data) {
        material.apply();

        glMatrixMode(GL_MODELVIEW);

        glPushMatrix();
        glMultMatrixf(toWorld.ptr());


        if (type == POINT_LIGHT)
            glutSolidSphere(.5f, 15, 15);
        else {
            GLUquadricObj *quadObj = gluNewQuadric();
            gluCylinder(quadObj, .33f, 0, .5f, 25, 25);
        }

        glPopMatrix();
    }
};

#endif
