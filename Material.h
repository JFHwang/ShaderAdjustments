#ifndef CSE167_Material_h
#define CSE167_Material_h

#include <iostream>
#include "Color.h"


class Material {
public:

    Color ambientColor;
    Color diffuseColor;
    Color specularColor;
    Color emissionColor;

    float shininess;

    //A color variable used in Projects 1, 2, and 3
    //This can be removed once materials are implemented
    Color color;

public:

    


    Material(void);
    ~Material(void);

    Material(Color c, float shine = 0){
        ambientColor = c;
        diffuseColor = c;
        specularColor = Color::white();
        emissionColor = c;
        shininess = shine;
    }


    
    void setAll(Color c){
        *this = Material(c, shininess);
    }
    
    virtual void apply(void);

    static Material random() {
        Material m;
        m.ambientColor = Color::random();
        m.diffuseColor = Color::random();
        m.specularColor = Color::random();
        m.emissionColor = Color::random();
        m.shininess = 32;
        return m;
    }

    static Material getDefault() {
        Material m;
        m.ambientColor = Color::ambientDefault();
        m.diffuseColor = Color::diffuseDefault();
        m.specularColor = Color::specularDefault();
        m.emissionColor = Color::emissionMaterialDefault();
        m.shininess = 0;
        return m;
    }

};

#endif
