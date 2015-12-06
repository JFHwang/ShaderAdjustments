#include "Vector3.h"
#include <math.h>
#include <iostream>
#include <cstring>
#include "Vector4.h"
#include "Camera.h"

Vector3::Vector3() {
    std::memset(m, 0, sizeof (m));
}

Vector3::Vector3(float m0, float m1, float m2) {
    m[0] = m0;
    m[1] = m1;
    m[2] = m2;
}

Vector3::~Vector3() {
    //
}

float* Vector3::ptr() {
    return &m[0];
}

Vector3 Vector3::proj(const Vector3 onto) const{
    Vector3 unit = onto.normalize();
    
    return unit.scale(dot(unit));
}



void Vector3::set(float x, float y, float z) {
    m[0] = x;
    m[1] = y;
    m[2] = z;
}

void Vector3::set(int index, float value) {
    m[index] = value;
}

float& Vector3::operator[](int loc) {
    return m[loc];
}

Vector3 Vector3::add(const Vector3 a) const {
    return Vector3(m[0] + a.m[0], m[1] + a.m[1], m[2] + a.m[2]);
}

Vector3 Vector3::operator+(const Vector3 a) const {
    return add(a);
}

Vector3 Vector3::subtract(const Vector3 a) const {
    return add(a.negate());
}

Vector3 Vector3::operator-(const Vector3 a) const {
    return subtract(a);
}

Vector3 Vector3::negate(void) const {
    return scale(-1);
}

Vector3 Vector3::scale(float s) const {
    return Vector3(s * m[0], s * m[1], s * m[2]);
}

Vector3 Vector3::multiply(float a) const {
    return scale(a);
}

Vector3 Vector3::operator*(float a) const {
    return multiply(a);
}

Vector3 Vector3::multiply(const Vector3 a) const {
    return Vector3(a.m[0] * m[0], a.m[1] * m[1], a.m[2] * m[2]);
}

Vector3 Vector3::operator*(const Vector3 a) const {
    return multiply(a);
}

float Vector3::dot(const Vector3 a) const {
    float sum = 0;
    for (int i = 0; i < 3; ++i)
        sum += a.m[i] * m[i];
    return sum;
}

Vector3 Vector3::cross(const Vector3 a) const {
    const float i = m[1] * a.m[2] - m[2] * a.m[1];
    const float j = m[2] * a.m[0] - m[0] * a.m[2];
    const float k = m[0] * a.m[1] - m[1] * a.m[0];
    return Vector3(i, j, k);
}

float Vector3::angle(Vector3 a) {
    return acos(dot(a) / (magnitude() * a.magnitude()));
}

float Vector3::magnitude(void) const {
    float sum = 0;
    for (auto comp : m)
        sum += comp * comp;
    return sqrt(sum);
}

Vector3 Vector3::normalize(void) const {
    float norm = magnitude();

    if (norm == 0)
        norm = 1;

    const float i = m[0] / norm;
    const float j = m[1] / norm;
    const float k = m[2] / norm;

    return Vector3(i, j, k);
}

Vector4 Vector3::toVector4(float w) const {
    return Vector4(getX(), getY(), getZ(), w);
}

void Vector3::print(std::string comment) const {
    std::cout << comment << std::endl;
    std::cout << "<x:" << m[0] << ", y:" << m[1] << ", z:" << m[2] << ">" << std::endl;
}

float Vector3::getX() const {
    return get(0);
}

float Vector3::getY() const {
    return get(1);
}

float Vector3::getZ() const {
    return get(2);
}

float Vector3::getW() const {
    return get(3);
}

float Vector3::get(int i) const {
    return m[i];
}