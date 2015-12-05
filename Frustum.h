/* 
 * File:   Frustum.h
 * Author: Evan
 *
 * Created on November 4, 2015, 8:01 PM
 */

#ifndef FRUSTUM_H
#define	FRUSTUM_H

#include "Vector3.h"
#include "Window.h"
#include "Matrix4.h"

class Frustum {
public:
    static Vector3 origin, topL, topR, bottomL, bottomR, topN, bottomN, leftN, rightN, frontN;

    static void update(float width, float height) {
        const float z = 1;
        const float top = tan(PI / 6);
        const float right = top * width / height;
        const float left = -right;
        const float bottom = -top;



        topL = Vector3(left, top, z);
        topR = Vector3(right, top, z);
        bottomL = Vector3(left, bottom, z);
        bottomR = Vector3(right, bottom, z);

        topN = topR.cross(topL).normalize();
        bottomN = bottomL.cross(bottomR).normalize();
        leftN = topL.cross(bottomL).normalize();
        rightN = bottomR.cross(topR).normalize();


        leftN.print("Left Normal");
    }

    static bool isInView(Vector3 cspace, float radius) {
        if (cspace.getZ() + radius < -1000)
            return false;

        if (cspace.getZ() - radius > -1)
            return false;

        //return true;
        // return isInBound(leftN, cspace, radius);
        return isInBound(topN, cspace, radius) && isInBound(bottomN, cspace, radius) && isInBound(leftN, cspace, radius) && isInBound(rightN, cspace, radius);
    }

    static bool isInBound(Vector3 norm, Vector3 cpos, float radius) {
        return cpos.dot(norm) <= radius;
    }

    Frustum(const Frustum& orig) {

    }

    virtual ~Frustum() {

    }
private:

};

#endif	/* FRUSTUM_H */

