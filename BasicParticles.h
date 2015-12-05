/* 
 * File:   BasicParticles.h
 * Author: Evan
 *
 * Created on November 28, 2015, 11:09 PM
 */

#ifndef BASICPARTICLES_H
#define	BASICPARTICLES_H

#include "ParticleSource.h"
#include "Vector3.h"
#include "Globals.h"
#include <cstdlib>

class StaryBackground : public ParticleSource {
public:

    StaryBackground() {
        survivalRate = 99.99;
    }

    virtual Vector3 speedGenerator(Vector3 position) const override {
        return position.multiply(Vector3(1, 1, -1)).subtract(Vector3(6, 0, 0)).normalize().scale(1.0f / 10);
    }

    virtual Color colorGenerator() const override {
        return Color::random();
    }

    virtual void update(Particle& p) const override {
        p.color[3] = clampf(0, 1, p.color[3]*1.005);
    }

    virtual Vector3 randOffset() const override {
        static const float delta = .333;
        return Vector3(6 + frand(-delta, delta), frand(-delta, delta), frand(-1, -2));
    }

    virtual ~StaryBackground() {
    }

private:

};


#endif	/* BASICPARTICLES_H */

