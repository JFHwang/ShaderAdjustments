#ifndef CSE167_Sphere_h
#define CSE167_Sphere_h

#include <iostream>
#include "OBJObject.h"
#include "Geode.h"

class Sphere : public Geode {
public:

    int slices, stacks;

    Sphere(int slice = 50, int stack = 50) : slices(slice), stacks(stack){
        
    }

    virtual void render() override{
        glutSolidSphere(1, slices, stacks);
    }
};

#endif
