/* 
 * File:   Particle.h
 * Author: Evan
 *
 * Created on November 28, 2015, 1:10 PM
 */

#ifndef PARTICLE_H
#define	PARTICLE_H

#include "Color.h"
#include "Vector3.h"
#include "Globals.h"

class Particle {
public:

    Color color;
    Vector3 point;
    Vector3 speed;
    bool isAlive;

    Particle(Vector3 p = Vector3(0, 0, 0)) : point(p), isAlive(true) {
        color = Color::random();

        point = point;
    }

    Particle(const Particle& orig) {

    }

    void draw() {
        if (isAlive) {
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color.ptr());
            glColor4fv(color.ptr());

            glBegin(GL_POINTS);

            glVertex3fv(point.ptr());
            glEnd();
        }
    }

    bool update(float chance) {
        if (isAlive) {
            point = point + speed;
            isAlive = frand(0, 100) < chance;
        }
        return isAlive;
    }

    void reset(Vector3 p = Vector3(0, 0, 0)) {
        point = p;
        isAlive = true;
    }

    virtual ~Particle() {

    }

private:

};

#endif	/* PARTICLE_H */

