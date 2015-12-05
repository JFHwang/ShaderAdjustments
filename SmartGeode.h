/* 
 * File:   SmartGeode.h
 * Author: Evan
 *
 * Created on November 27, 2015, 11:55 PM
 */

#ifndef SMARTGEODE_H
#define	SMARTGEODE_H

#include "Matrix4.h"
#include "Geode.h"

class SmartGeode : public Geode {
public:


    const float width, height;

    Matrix4 transform;
    Material mat;

    SmartGeode(Vector3 pos, float w, float h) : width(w), height(h), mat() {
        transform = Matrix4::makeTranslate(pos) * Matrix4::makeScale(width, 1, height);
        mat.shininess = 16;
        mat.ambientColor = Color::blue();
        mat.diffuseColor = Color::blue();
        mat.specularColor = Color::white();
        mat.emissionColor = Color::white();
        
        
    }

    SmartGeode(const SmartGeode& orig) : width(orig.width), height(orig.height) {

    }

    virtual ~SmartGeode() {

    }

    virtual void draw(MatrixStack& d) override {
        ++d.count;

        MatrixStack stack = d.push(transform);

        renderWithMatrix(stack.convert,{
            mat.apply();
            render();
        });

    }

    virtual void update(int tick) override {

    }


    Vector3 getTranslation() const {
        return transform.getTranslation();
    }

private:

   

};

#endif	/* SMARTGEODE_H */

