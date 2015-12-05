#ifndef CSE167_RenderData_h
#define CSE167_RenderData_h

#include <iostream>
#include "Matrix4.h"


class MatrixStack {
public:

    int count;
    
    //Payload
    //Place any objects here that you want to pass to a draw() call

    Matrix4 convert;
    MatrixStack(Matrix4 trans) : count(0), convert(trans) {
        
    }
    
    
    MatrixStack push(Matrix4 nextTransform){
        return MatrixStack(*this, nextTransform);
    }
    
    MatrixStack(const MatrixStack& other, Matrix4 next) : count(0), convert(other.convert * next){
        
    }
    
    ~MatrixStack(void){
        
    }

};

#endif
