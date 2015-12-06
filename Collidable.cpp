#include "Collidable.h"



static Material hitM(){
    Material m;
    m.ambientColor = Color::red();
    m.diffuseColor = Color::red();
    m.emissionColor = Color::red();
    m.specularColor = Color::red();
    return m;
}



static Material hitOK(){
    Material m;
    m.ambientColor = Color::white();
    m.diffuseColor = Color::white();
    m.emissionColor = Color::white();
    m.specularColor = Color::white();
    return m;
}



Material Collidable::hit = hitM(), Collidable::ok = hitOK();
