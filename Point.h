/* 
 * File:   Point.h
 * Author: Evan
 *
 * Created on October 12, 2015, 6:28 PM
 */

#ifndef POINT_H
#define	POINT_H
#include "Vector3.h"

class Point {
public:
    Point(int x, int y);
    Point(const Point& orig);
    virtual ~Point();
    
    
    const float x, y;
    
    float distance(const Point& other);
    
    Point minus(const Point& other){
        return Point(x - other.x, y - other.y);
    }
    
    Vector3 scale(float factor){
        return Vector3( x*factor, y * factor, 0);
    }
    
    Vector3 toV(){
        return Vector3(x, y, 0);
    }
private:

};

#endif	/* POINT_H */

