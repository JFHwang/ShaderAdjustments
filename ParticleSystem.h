/* 
 * File:   ParticleSystem.h
 * Author: Evan
 *
 * Created on November 28, 2015, 1:32 PM
 */

#ifndef PARTICLESYSTEM_H
#define	PARTICLESYSTEM_H

#include "Particle.h"
#include "SmartGeode.h"
#include "ParticleSource.h"
#include <omp.h>

class ParticleSystem : public SmartGeode {
public:

    std::vector<Particle> parts;
    const bool isInfinite;
    const ParticleSource* source;
    bool isFinished;

    ParticleSystem(int size, ParticleSource* src, bool refresh = true, Vector3 pos = Vector3(0, 0, 0)) : SmartGeode(pos, 1, 1), parts(0), isInfinite(refresh) {
        isFinished = false;
        source = src;
        transform.identify();
        reset(size);
    }

    ParticleSystem(const ParticleSystem& orig) : SmartGeode(orig), isInfinite(orig.isInfinite) {

    }

    virtual ~ParticleSystem() {

    }

    void reset(int size) {
        parts.clear();
        parts.resize(size);
        for (auto& par : parts) {
            reset(par);
        }
    }

    virtual void render() override {
        if (isInfinite || !isFinished) {
            //  glDisable(GL_LIGHTING);
            glEnable(GL_COLOR_MATERIAL);

            for (auto& part : parts) {
                part.draw();
            }
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Color::black().ptr());

            glDisable(GL_COLOR_MATERIAL);
            //  glEnable(GL_LIGHTING);
        }
    }

    void update2(Particle& part) {
        if (part.isAlive)
            isFinished = false;

        source->update(part);
        if (!part.update(source->survivalRate) && isInfinite) {
            reset(part);
        }
    }

    virtual void update(int tick) override {
        if (isInfinite || !isFinished) {
            __gnu_parallel::for_each(parts.begin(), parts.end(), [this](Particle & p) {
                this->update2(p);
            });

            if (!isInfinite)
                parts.erase(std::remove_if(parts.begin(), parts.end(), toDelete), parts.end());
        }
    }

    static bool toDelete(Particle& p) {
        return !p.isAlive;
    }




private:

    void reset(Particle& part) {
        part.reset(source->randOffset());
        part.speed = source->speedGenerator(part.point);
        part.color = source->colorGenerator();
        isFinished = false;
    }
};

#endif	/* PARTICLESYSTEM_H */

