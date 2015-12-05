#include "Camera.h"

Camera::Camera() {
    c.identify();
    e.set(0.0, 0.0, 20.0);
    d.set(0.0, 0.0, 0.0);
    up.set(0.0, 1.0, 0.0);

    //Pre-define a camera matrix (and its inverse) that are shifted 'e' from the origin
    //This is used as a default camera position for Project 1
    c.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, e[0], e[1], e[2], 1);
    ci.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -e[0], -e[1], -e[2], 1);
}

Camera::~Camera() {
    //Delete and dynamically allocated memory/objects here
}

Matrix4& Camera::getMatrix() {
    return c;
}

Matrix4& Camera::getInverseMatrix() {
    return ci;
}

void Camera::update() {

    Vector3 z = (e - d).normalize();
    Vector3 x = up.cross(z).normalize();
    Vector3 y = z.cross(x);

    c = Matrix4::from(x, y, z, e);
    ci = c.rigidInverse();
    //Update the Camera Matrix using d, e, and up
    //Solve for the z, x, and y axes of the camera matrix
    //Use these axes and the e vector to create a camera matrix c
    //Use c to solve for an inverse camera matrix ci
}

void Camera::set(Vector3& e, Vector3& d, Vector3& up) {
    this->e = e;
    this->d = d;
    this->up = up;
    update();
}

void Camera::translate(Vector3 t) {
    Vector3 n = t.negate();
    ci.applyOther(Matrix4().makeTranslate(n));
}

void Camera::rotateX(float theta) {
     ci.applyOther(Matrix4().makeRotateX(-theta));   
}

void Camera::rotateY(float theta) {
     ci.applyOther(Matrix4().makeRotateY(-theta));   
}