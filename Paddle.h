/* 
 * File:   Paddle.h
 * Author: Evan
 *
 * Created on November 28, 2015, 10:13 AM
 */

#ifndef PADDLE_H
#define	PADDLE_H

#include "SmartGeode.h"
#include "Collidable.h"
#include "KeyTracker.h"

class Paddle : public SmartGeode, public Collidable {
public:
    static constexpr float SPEED = .5f;

    Paddle(Vector3 pos) : SmartGeode(pos, 6, 1), Collidable(pos, 6, 1) {
        mat.setAll(Color::randomBrightPastel());
    }

    Paddle(const Paddle& orig) : SmartGeode(orig), Collidable(orig) {

    }

    virtual ~Paddle() {

    }

    virtual void render() override {
        cube();
    }

    virtual void handleCollisions(Ball& b) {
        c_center = getTranslation();
        Collidable::handleCollisions(b);
    }

    virtual void update(int tick) override {

        if (Keys::isPressed('a'))
            transform.applyOther(Matrix4::makeTranslate(-SPEED, 0, 0));
        else if (Keys::isPressed('d'))
            transform.applyOther(Matrix4::makeTranslate(SPEED, 0, 0));

        SmartGeode::update(tick);
    }

    virtual void onCollision(Ball& b, Face side) override {
        if (side != FRONT)
            Collidable::onCollision(b, side);
        else {
            const float ADJUSTMENT = .66;

            float adj = 0;
            if (Keys::isPressed('a'))
                adj = -ADJUSTMENT;
            else if (Keys::isPressed('d'))
                adj = ADJUSTMENT;



            b.speed.set(2, -b.speed.getZ());
            b.speed.set(0, b.speed.getX() + adj);

            b.speed = b.speed.normalize() * Ball::SPEED;
        }
    }


private:

};

#endif	/* PADDLE_H */

