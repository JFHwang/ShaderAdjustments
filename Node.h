/* 
 * File:   Node.h
 * Author: Evan
 *
 * Created on November 1, 2015, 8:18 PM
 */

#ifndef NODE_H
#define	NODE_H
#include "Matrix4.h"
#include <GL/freeglut.h>
#include "DrawData.h"

using namespace std;


class Node {
public:    
    
    Node(){

    }

    Node(const Node& orig){
        
    }
    
 
    
    virtual ~Node(){
        
    }
    virtual void draw(MatrixStack& cum) = 0;
    virtual void update(int tick) = 0;
private:

};

#endif	/* NODE_H */

