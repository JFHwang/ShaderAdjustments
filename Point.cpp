/* 
 * File:   Point.cpp
 * Author: Evan
 * 
 * Created on October 12, 2015, 6:28 PM
 */

#include "Point.h"
#include <cmath>

Point::Point(int xx, int yy): x(xx), y(yy) {
}

Point::Point(const Point& orig): x(orig.x), y(orig.y) {
    
}

float Point::distance(const Point& other){
    return sqrt( pow(x - other.x, 2) + pow(y - other.y, 2) );
}

Point::~Point() {
}

