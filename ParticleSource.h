/* 
 * File:   ParticleSource.h
 * Author: Evan
 *
 * Created on November 28, 2015, 2:54 PM
 */

#ifndef PARTICLESOURCE_H
#define	PARTICLESOURCE_H

#include "Vector3.h"
#include "Color.h"
#include "Globals.h"
#include "Particle.h"

class ParticleSource {
public:
    float survivalRate = 99.0f;

    virtual Vector3 speedGenerator(Vector3 position) const {
        return Vector3(frand(-1, 1), frand(-1, 1), frand(-1, 1)).normalize();
    }

    virtual Color colorGenerator() const {
        return Color::random();
    }

    virtual Vector3 randOffset() const {
        static const float delta = .333;
        return Vector3(frand(-delta, delta), frand(-delta, delta), frand(-delta, delta));
    }

    virtual void update(Particle& p) const {
        p.color[3] *= .995;
    }

};

#endif	/* PARTICLESOURCE_H */

