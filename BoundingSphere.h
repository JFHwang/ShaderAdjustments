/* 
 * File:   BoundingSphere.h
 * Author: Evan
 *
 * Created on November 3, 2015, 5:22 PM
 */

#ifndef BOUNDINGSPHERE_H
#define	BOUNDINGSPHERE_H
#include "Node.h"

#include "Matrix4.h"
#include "Vector3.h"
#include "Frustum.h"
#include <GL/freeglut.h>
#include <cmath>

class BoundingSphere : public Node {
public:
    Node* child;
    Vector3 center;
    float radius;
    bool isColliding;

    BoundingSphere(Node* c, float r = 1, Vector3 pos = Vector3(0, 0, 0)) : child(c), center(pos), radius(r), isColliding(false) {

    }

    BoundingSphere(const BoundingSphere& orig) : center(orig.center) {

    }

    virtual void draw(MatrixStack& cum) {
        Vector3 cspace = cum.convert.multiply(center.toVector4(1)).toVector3();


        if (Frustum::isInView(cspace, radius)) {
            if (Globals::isBoundsOn)
                render(cum.convert);
            child->draw(cum);
        }
    }

    virtual void update(int tick) {
        child->update(tick);
    }

    //    BoundingSphere operator=(const BoundingSphere& other) {
    //        radius = other.radius;
    //        center = other.center;
    //        return *this;
    //    }

    virtual ~BoundingSphere() {

    }

    void render(Matrix4 trans) {
        if(isColliding){
            glColor3f(1, 0, 0);
        }
        
        renderWithMatrix(trans,{
            glTranslatef(center.getX(), center.getY(), center.getZ());
            glutWireSphere(radius, 10, 10);
            glTranslatef(-center.getX(), -center.getY(), -center.getZ());
        });
        
        glColor3f(1, 1, 1);
    }


    void collisions(BoundingSphere* other, Matrix4 mine, Matrix4 yours){
        if((mine.multiply(center.toVector4(1)) - yours.multiply(other->center.toVector4(1))).toVector3().magnitude() < radius + other->radius){
            isColliding = true;
            other->isColliding = true;
        } 
    }


private:

};

#endif	/* BOUNDINGSPHERE_H */

