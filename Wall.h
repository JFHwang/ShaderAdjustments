/* 
 * File:   Wall.h
 * Author: Evan
 *
 * Created on November 27, 2015, 11:32 PM
 */

#ifndef WALL_H
#define	WALL_H

#include "Geode.h"
#include "Matrix4.h"
#include "SmartGeode.h"
#include "Collidable.h"
#include "Globals.h"
#include "Texture.h"

class Wall : public SmartGeode, public Collidable {
public:

    Wall(Vector3 pos, float w, float h) : SmartGeode(pos, w, h), Collidable(pos, w, h) {

    }

    Wall(const Wall& orig) : SmartGeode(orig), Collidable(orig) {

    }

    virtual ~Wall() {

    }

    virtual void render() {
        Collidable::render();
        Texture::getBackground()->bind();
        cube();
        Texture::getBackground()->unbind();
    }
    
    
private:

};

#endif	/* WALL_H */

