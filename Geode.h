/* 
 * File:   Geode.h
 * Author: Evan
 *
 * Created on November 1, 2015, 8:27 PM
 */

#ifndef GEODE_H
#define	GEODE_H

#include "Globals.h"

#include "Node.h"
#include <GL/freeglut.h>

class Geode : public Node {
public:
    Geode();
    Geode(const Geode& orig);
    virtual ~Geode();

    virtual void draw(MatrixStack& d) override {
        ++d.count;
        
        renderWithMatrix(d.convert,{
            render();
        });

    }

    virtual void update(int tick) override {

    }

    virtual void render() = 0;
private:

};

#endif	/* GEODE_H */

