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

    Paddle(Vector3 pos) : SmartGeode(pos, 7, 1.5), Collidable(pos, 7, 1.5) {
        mat.setAll(Color::randomBrightPastel());
    }

    Paddle(const Paddle& orig) : SmartGeode(orig), Collidable(orig) {

    }

    virtual ~Paddle() {

    }

    virtual void render() override {
        Collidable::render();
        mat.apply();
        glutSolidSphere(.5, 50, 50);
    }

    virtual void update(int tick) override {
        if (Keys::isPressed('a'))
            move(-1);
        else if (Keys::isPressed('d'))
            move(1);

        SmartGeode::update(tick);
    }

    void move(int dir) {
        if (dir == 0)
            return;
        else if (dir < 0)
            transform.applyOther(Matrix4::makeTranslate(-SPEED, 0, 0));
        else
            transform.applyOther(Matrix4::makeTranslate(SPEED, 0, 0));

        c_center = getTranslation();
    }

    virtual void onCollision(Ball& b, Face side) override {
        if (side != FRONT) {
            Collidable::onCollision(b, side);
        } else {
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

