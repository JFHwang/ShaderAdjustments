/* 
 * File:   MatrixNode.h
 * Author: Evan
 *
 * Created on November 1, 2015, 8:24 PM
 */

#ifndef MATRIXNODE_H
#define	MATRIXNODE_H
#include "Node.h"
#include "Group.h"
#include "Globals.h"

class MatrixNode : public Group {
public:
    Matrix4 transform;

    MatrixNode(Matrix4 tranny = Matrix4::identity()) {
        transform = tranny;
    }

    void draw(MatrixStack& old) override {
        MatrixStack cur(old, transform);

        for (auto& child : children) {
            child->draw(cur);
        }

        old.count += cur.count;
    }


    Node* front(){
        return children.front();
    }


    MatrixNode(const MatrixNode& orig);
    virtual ~MatrixNode();
private:

};

#endif	/* MATRIXNODE_H */

