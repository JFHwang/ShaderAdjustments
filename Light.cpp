#include "Light.h"
#include "Window.h"
#include <iostream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

Light::Light(int id, Type t) {
    type = t;
    bindID = GL_LIGHT0 + id;

    ambientColor = Color::ambientDefault();
    diffuseColor = Color::diffuseDefault();
    specularColor = Color::specularDefault();
    angle = 30;
    exp = 4;

    constantAttenuation = .05;
    linearAttenuation = 0.01;
    quadraticAttenuation = 0.03;

    if (type == DIRECTIONAL_LIGHT) {
        linearAttenuation = 0;
        quadraticAttenuation = 0;
        toWorld.setTranslation(toWorld.getColumn(3).toVector3().normalize().scale(5000));
    }
}

void Light::scaleIntensity(float amount) {

    for (int i = 0; i < 3; ++i) {
        ambientColor[i] *= amount;
        diffuseColor[i] *= amount;
        specularColor[i] *= amount;
    }
}

Light::~Light() {
    //Delete any dynamically allocated memory/objects here
}

void Light::bind() {
    //Configure the light at the bindID
    glEnable(bindID);

    //Configure the color of the light
    glLightfv(bindID, GL_AMBIENT, ambientColor.ptr());
    glLightfv(bindID, GL_DIFFUSE, diffuseColor.ptr());
    glLightfv(bindID, GL_SPECULAR, specularColor.ptr());

    Vector4 translation = toWorld.getColumn(3);
    if (type == DIRECTIONAL_LIGHT)
        translation = translation.toVector3().toVector4(0);

    //Configure the attenuation properties of the light
    //Add support for Constant Attenuation
    //Add support for Linear Attenuation
    glLightf(bindID, GL_QUADRATIC_ATTENUATION, quadraticAttenuation);
    glLightf(bindID, GL_LINEAR_ATTENUATION, linearAttenuation);
    glLightf(bindID, GL_CONSTANT_ATTENUATION, constantAttenuation);

    //Position the light
    glLightfv(bindID, GL_POSITION, translation.ptr());

    //Setup spotlight direction, angle, and exponent here
    if (type == SPOT_LIGHT) {
        glLightf(bindID, GL_SPOT_CUTOFF, angle);
        glLightfv(bindID, GL_SPOT_DIRECTION, translation.scale(-1).ptr());
        glLightf(bindID, GL_SPOT_EXPONENT, exp);
    }
}

void Light::unbind(void) {
    glDisable(bindID);
}
