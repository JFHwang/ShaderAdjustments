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

    Brick(Vector3 pos) : SmartGeode(pos, WIDTH, HEIGHT), Collidable(pos, WIDTH, HEIGHT), particles(0, this, false), isVisible(true) {
        survivalRate = 96;
        mat.setAll(Color::red());
        mat.shininess = 8;
        
    }

    Brick(const Brick& orig) : SmartGeode(orig), Collidable(orig), particles(orig.particles) {

    }

    virtual ~Brick() {

    }

    virtual void draw(MatrixStack& old) {
        ++old.count;


        MatrixStack stack = old.push(transform);
        renderWithMatrix(stack.convert,{
            render();
        });

        if (!isVisible)
            particles.draw(stack);

    }

    virtual void update(int tick) override {
        particles.update(tick);
    }

    void render() override {
        Collidable::render();
        if (isVisible) {
            mat.apply();
            cube();
        }
    }

    virtual Vector3 speedGenerator(Vector3 position) const {
        return (position).normalize().scale(1.0f / 10);
    }

    virtual void update(Particle& p) const {
        p.speed = p.speed.scale(.965);
    }
    
    virtual Color colorGenerator() const {
        return mat.ambientColor;
    }

    virtual Vector3 randOffset() const {
        return Vector3(frand(-WIDTH / 2, WIDTH / 2), frand(-.5, .5), frand(-HEIGHT / 2, HEIGHT / 2));
    }

    virtual void onCollision(Ball& b, Face side) override {
        Collidable::onCollision(b, side);
        isVisible = false;
        particles.reset(20000);

    }

    virtual void handleCollisions(Ball& b) override {
        if (isVisible)
            Collidable::handleCollisions(b);
    }



private:
    bool isVisible;

};

#endif	/* BRICK_H */

