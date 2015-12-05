/* 
 * File:   Group.h
 * Author: Evan
 *
 * Created on November 1, 2015, 8:20 PM
 */

#ifndef GROUP_H
#define	GROUP_H

#include "Node.h"
#include <list>
#include <iostream>

class Group : public Node {
protected:
    std::list<Node*> children;

public:

    Group() : children() {

    }

    void add(Node* child) { 
        children.push_back(child);
    }

    void remove(Node* child) {
        children.remove(child);
    }

    virtual void draw(MatrixStack& cum) override {
        for (auto& child : children) {
            child->draw(cum);
        }
    }


    virtual void update(int tick) override {
        for (auto& child : children) {
            child->update(tick);
        }
    }

    Group(const Group& orig);

    virtual ~Group();

private:


};

#endif	/* GROUP_H */

