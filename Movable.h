/* 
 * File:   Movable.h
 * Author: Evan
 *
 * Created on September 30, 2015, 11:01 AM
 */

#ifndef MOVABLE_H
#define	MOVABLE_H
#include "Drawable.h"
#include "Vector3.h"

class Movable : public Drawable {
public:
    static const Vector3 gravity;


    Movable();
    Movable(const Movable& orig);
    virtual ~Movable();

private:

protected:
    Vector3 position = Vector3(0, 0, 0);
    Vector3 speed = Vector3(0, 0, 0);

};

#endif	/* MOVABLE_H */

