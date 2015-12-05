#include "Drawable.h"
#include "Window.h"
#include "Globals.h"

//const float Drawable::PI = 3.141592653589;

    
Drawable::Drawable() {
    this->toWorld.identify();
    this->material = Material();
}

Drawable::~Drawable() {
    //
}

void Drawable::draw(MatrixStack& data) {
    std::cout << "Warning: draw() is not implemented" << std::endl;
}

void Drawable::update(UpdateData& data) {
    std::cout << "Warning: update() is not implemented" << std::endl;
}

bool Drawable::operator==(const Drawable& other) const {
    return this == &other;
}


void Drawable::spin(float radians) {
    Matrix4 rotation;
    rotation.makeRotateY(radians);

    toWorld = toWorld * rotation;
}

