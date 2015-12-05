#include "Material.h"
#include "Globals.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

Material::Material() {
    //Material setup goes hurr
    ambientColor = Color(frand(0, 1), frand(0, 1), frand(0, 1));
    diffuseColor = Color(frand(0, 1), frand(0, 1), frand(0, 1));
    specularColor = Color(frand(0, 1), frand(0, 1), frand(0, 1));
    emissionColor = Color::emissionMaterialDefault();
    shininess = frand(1, 255);

    //Set the initial color to a random pastel color
    //Can be removed once materials are implemented
    color = Color::randomPastel();
}

Material::~Material() {
    //Delete any dynamically allocated memory/objects here
}

void Material::apply(void) {
    //Set the material properties for ambient, diffuse, specular, emission, and shininess
    //Hint: Lookup how glMaterialfv works

    //Set the color property (can be removed once materials are implemented)
    //Used for projects 1, 2, and 3
    // glColor3fv(color.ptr());


    glMaterialfv(GL_FRONT, GL_SPECULAR, specularColor.ptr());
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambientColor.ptr());
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor.ptr());
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Color::black().ptr());

}



