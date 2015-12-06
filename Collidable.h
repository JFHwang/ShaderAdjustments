/* 
 * File:   Collidable.h
 * Author: Evan
 *
 * Created on November 28, 2015, 5:47 PM
 */

#ifndef COLLIDABLE_H
#define	COLLIDABLE_H
#include "Ball.h"
#include "KeyTracker.h"

class Collidable {
public:

    enum Face {
        SIDE, FRONT, NONE
    };

    static Material hit, ok;

    Vector3 c_center;
    float c_w, c_h;
    bool isHit;

    Collidable(Vector3 position, float width, float height) : c_center(position),
    c_w(width), c_h(height), isHit(false) {

    }

    virtual bool isCollidingWith(Ball& b) {
        Vector3 bp = b.getTranslation();
        Vector3 distance = (bp - c_center);

        if (abs(distance.getX()) < c_w / 2 + b.width / 2)
            if (abs(distance.getZ()) < c_h / 2 + b.height / 2)
                return true;
        return false;
    }

    Face getSideOfCollision(Ball& b) {
        if (Collidable(c_center + Vector3(0, 0, c_h / 2), c_w, 0).isCollidingWith(b))
            return FRONT;
        if (Collidable(c_center - Vector3(0, 0, c_h / 2), c_w, 0).isCollidingWith(b))
            return FRONT;

        return SIDE;
    }

    virtual void handleCollisions(Ball& b) {
        if (isCollidingWith(b)) {
            onCollision(b, getSideOfCollision(b));
            isHit = true;
        } else
            isHit = false;
    }

    void render() {
        if (Globals::isBoundsOn) {
            if (isHit)
                Collidable::hit.apply();
            else
                Collidable::ok.apply();
            glutWireCube(1);
        }
    }

    virtual void onCollision(Ball& b, Face side) {
        if (side == FRONT)
            b.speed.set(2, -b.speed[2]);
        else
            b.speed.set(0, -b.speed[0]);
    }

    
    virtual int isColliding(Collidable& paddle){
        Vector3 bp = paddle.c_center;
        Vector3 distance = (bp - c_center);

        bool tTemp = isHit;
        bool oTemp = paddle.isHit;
        
        if (abs(distance.getX()) < c_w / 2 + paddle.c_w / 2)
            if (abs(distance.getZ()) < c_h / 2 + paddle.c_h / 2){
                isHit = true;
                paddle.isHit = true;
                return bp.getX() > c_center.getX()? 1 : -1;
            }
        
        isHit = tTemp;
        paddle.isHit = oTemp;
        return 0;
    }

};



#endif	/* COLLIDABLE_H */

