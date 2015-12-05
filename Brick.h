/* 
 * File:   Brick.h
 * Author: Evan
 *
 * Created on November 27, 2015, 7:30 PM
 */

#ifndef BRICK_H
#define	BRICK_H

#include "Cube.h"
#include "SmartGeode.h"
#include "Collidable.h"
#include "ParticleSystem.h"

class Brick : public SmartGeode, public Collidable, public ParticleSource {
public:

    static constexpr float WIDTH = 1, HEIGHT = .5;

    ParticleSystem particles;

    Brick(Vector3 pos) : SmartGeode(pos, 1, .5), Collidable(pos, WIDTH, HEIGHT), particles(0, this, false), isVisible(true) {
        survivalRate = 96;
    }

    Brick(const Brick& orig) : SmartGeode(orig), Collidable(orig), particles(orig.particles) {

    }

    virtual ~Brick() {

    }

    virtual void draw(MatrixStack& old) {
        ++old.count;


        MatrixStack stack = old.push(transform);
        if (isVisible) {
            renderWithMatrix(stack.convert,{
                render();
            });
        } else
            particles.draw(stack);
    }
    
    

    virtual void update(int tick) override {
        particles.update(tick);
    }


    void render() override {
        Collidable::render();
        glutSolidCube(1);
    }

    virtual Vector3 speedGenerator(Vector3 position) const {
        return (position).normalize().scale(1.0f/30);
    }

    virtual Color colorGenerator() const {
        return Color::green();
    }

    virtual Vector3 randOffset() const {
        return Vector3(frand(-WIDTH / 2, WIDTH / 2), frand(0, .5), frand(-HEIGHT / 2, HEIGHT / 2));
    }

    virtual void onCollision(Ball& b, Face side) override {
        Collidable::onCollision(b, side);
        isVisible = false;
        particles.reset(200000);

    }

    virtual void handleCollisions(Ball& b) override {
        if (isVisible)
            Collidable::handleCollisions(b);
    }



private:
    bool isVisible;

};

#endif	/* BRICK_H */

