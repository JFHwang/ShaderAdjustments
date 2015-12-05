#include <cmath>
#include <iostream>
#include <iomanip>
#include <cstring>
#include "Matrix4.h"
#include "Vector4.h"
#include "Vector3.h"

Matrix4::Matrix4() {
    identify();
}

Matrix4::Matrix4(float arr[16]){
    for(int r = 0; r < 16; ++r){
        m[r%4][r/4] = arr[r];
    }
}

Matrix4::Matrix4(const Matrix4& other){
    std::memcpy(m, other.m, sizeof (m));
}

Matrix4::Matrix4(
        float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33) {
    this->set(m00, m01, m02, m03,
            m10, m11, m12, m13,
            m20, m21, m22, m23,
            m30, m31, m32, m33);
}

Vector4 Matrix4::getColumn(int index) const {
    return Vector4(get(0, index), get(1, index), get(2, index), get(3, index));
}

void Matrix4::set(float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33) {
    m[0][0] = m00;
    m[0][1] = m01;
    m[0][2] = m02;
    m[0][3] = m03;
    m[1][0] = m10;
    m[1][1] = m11;
    m[1][2] = m12;
    m[1][3] = m13;
    m[2][0] = m20;
    m[2][1] = m21;
    m[2][2] = m22;
    m[2][3] = m23;
    m[3][0] = m30;
    m[3][1] = m31;
    m[3][2] = m32;
    m[3][3] = m33;
}

Matrix4& Matrix4::operator=(Matrix4 a) {
    std::memcpy(m, a.m, sizeof (m));
    return *this;
}

float* Matrix4::ptr() {
    return &m[0][0];
}

Vector3 Matrix4::getTranslation() const {
    return getColumn(3).toVector3();
}


void Matrix4::setTranslation(Vector3 position){
    set(0, 3, position.getX());
    set(1, 3, position.getY());
    set(2, 3, position.getZ());
}

static const float ident[4][4] = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

void Matrix4::identify() {
    std::memcpy(m, ident, sizeof (m));
}

Matrix4 Matrix4::identity() {
    Matrix4 id(false);
    std::memcpy(id.m, ident, sizeof (id.m));
    return id;
}


Matrix4 Matrix4::multiply(const Matrix4 other) const {
    Matrix4 b(false);

    for (int c = 0; c < 4; ++c)
        for (int r = 0; r < 4; ++r) {
            const float product = get(r, 0) * other.get(0, c) + get(r, 1) * other.get(1, c) + get(r, 2) * other.get(2, c) + get(r, 3) * other.get(3, c);

            b.set(r, c, product);
        }

    return b;
}

Matrix4 Matrix4::operator*(const Matrix4 a) const {
    return multiply(a);
}

float rowDot(const Matrix4& m, const int r, const Vector4& a) {
    float sum = 0;
    for (int i = 0; i < 4; ++i)
        sum += m.get(r, i) * a.get(i);
    return sum;
}

Vector4 Matrix4::multiply(const Vector4 a) const {
    const float i = rowDot(*this, 0, a);
    const float j = rowDot(*this, 1, a);
    const float k = rowDot(*this, 2, a);
    const float l = rowDot(*this, 3, a);

    return Vector4(i, j, k, l);
}

Vector4 Matrix4::operator*(const Vector4 a) const {
    return multiply(a);
}

Vector3 Matrix4::multiply(const Vector3 a) const {
    return multiply(a.toVector4(0)).toVector3();
}

Vector3 Matrix4::operator*(const Vector3 a) const {
    return multiply(a);
}

Matrix4 Matrix4::makeRotateX(float angle) {
    Matrix4 r = identity();

    r.set(1, 1, cos(angle));
    r.set(1, 2, -sin(angle));
    r.set(2, 1, sin(angle));
    r.set(2, 2, cos(angle));

    //Configure this matrix to be a rotation about the X-Axis by 'angle' radians
    return r;
}

Matrix4 Matrix4::makeRotateY(float angle) {
    Matrix4 r = identity();

    r.set(0,0, cos(angle));
    r.set(2,0, -sin(angle));
    r.set(0, 2, sin(angle));
    r.set(2,2,cos(angle));

    return r;
}

Matrix4 Matrix4::makeRotateZ(float angle) {
    Matrix4 r = identity();
    r.set(0, 0, cos(angle));
    r.set(0, 1, -sin(angle));
    r.set(1, 0, sin(angle));
    r.set(1, 1, cos(angle));

    //Configure this matrix to be a rotation about the Z-Axis by 'angle' radians

    return r;
}

Matrix4 Matrix4::makeRotateArbitrary(Vector3& a, float angle) {
    Matrix4 r = identity();
    const float sinx = sin(angle);
    const float cosx = cos(angle);

    const float x = a[0], y = a[1], z = a[2];

    r.set(0, 0, cosx + x * x * (1 - cosx));
    r.set(1, 0, x * y * (1 - cosx) + z * sinx);
    r.set(2, 0, z * x * (1 - cosx) - y * sinx);
    r.set(3, 0, 0);

    r.set(0, 1, x * y * (1 - cosx) - z * sinx);
    r.set(1, 1, cosx + y * y * (1 - cosx));
    r.set(2, 1, y * z * (1 - cosx) + x * sinx);
    r.set(3, 1, 0);

    r.set(0, 2, x * z * (1 - cosx) + y * sinx);
    r.set(1, 2, y * z * (1 - cosx) - x * sinx);
    r.set(2, 2, cosx + z * z * (1 - cosx));
    r.set(3, 2, 0);

    r.set(0, 3, 0);
    r.set(1, 3, 0);
    r.set(2, 3, 0);
    r.set(3, 3, 1);

    return r;
}

Matrix4 Matrix4::makeScale(float s) {
    return makeScale(s, s, s);
}

Matrix4 Matrix4::makeScale(float sx, float sy, float sz) {
    Matrix4 s = identity();
    s.set(0, 0, sx);
    s.set(1, 1, sy);
    s.set(2, 2, sz);

    //Configure this matrix to be a sclaing by sx, sy, sz

    return s;
}

Matrix4 Matrix4::makeTranslate(float x, float y, float z) {
    Matrix4 t = identity();
    t.setTranslation(Vector3(x,y,z));
    return t;
}

Matrix4& Matrix4::applyMe(const Matrix4& right) {
    return *this = *this * right;
}

Matrix4& Matrix4::applyOther(const Matrix4& left) {
    return *this = left * * this;
}

Matrix4 Matrix4::makeTranslate(Vector3 a) {
    return makeTranslate(a[0], a[1], a[2]);
}

Matrix4::Matrix4(bool DO_NOT_MEM_COPY_ID){
    
}


Matrix4 Matrix4::transpose(void) const {
    Matrix4 b(false);
    for (int x = 0; x < 4; ++x) {
        for (int y = x; y < 4; ++y) {
            b.m[y][x] = m[x][y];
            b.m[x][y] = m[y][x];
        }
    }
    return b;
}

Matrix4 Matrix4::getTranslation(const Matrix4& other) {
    Matrix4 t = Matrix4::identity();
    const float x = -other.get(0, 3);
    const float y = -other.get(1, 3);
    const float z = -other.get(2, 3);

    t.set(0, 3, x);
    t.set(1, 3, y);
    t.set(2, 3, z);
    return t;
}


//Hint: Try basing this on code by cool people on the internet
//In this class it is okay to use code from the internet
//So long as you fully understand the code and can clearly explain it if asked to
// http://stackoverflow.com/questions/2624422/efficient-4x4-matrix-inverse-affine-transform

Matrix4 Matrix4::inverse(void) const {
    return *this;
}

Matrix4 Matrix4::rigidInverse(void) const {
    Matrix4 tInv = getTranslation(*this);

    Matrix4 r = transpose();
    r.set(3, 0, 0);
    r.set(3, 1, 0);
    r.set(3, 2, 0);
    r.set(3, 3, 1);

    return r*tInv;
}

Matrix4 Matrix4::makePerspectiveProjection(float deg, float width, float height, float near, float far) { 
    identify();
    const float fov = deg * 3.14159/180;
    const float FOV = tan(fov/2);
    
    set(0,0, 1.0/(width/height * FOV));
    set(1,1, 1.0/FOV);
    set(2,2, (near+far)/(near-far));
    set(3,3,0);
    set(2,3, 2*near*far/(near-far));
    set(3,2, -1);
    
    return *this;
}

Matrix4 Matrix4::makeViewport(float xmin, float xmax, float ymin, float ymax) {
    
    
    identify();
    set(0,0, (xmax-xmin)/2);
    set(1,1, (ymax- ymin)/2);
    set(2,2,.5);
    set(2,3, .5);
    set(0,3, (xmin+xmax)/2);
    set(1,3, (ymin+ymax)/2);
    set(2,3, .5);
    //Project 3
    //Make this matrix a viewport matrix using xmin, xmax, ymin, and ymax
    //See the lecture slides for details

    return *this;
}

Matrix4 Matrix4::from(const Vector3& x, const Vector3& y, const Vector3& z, const Vector3& e) {
    Matrix4 result;
    for (int i = 0; i < 3; ++i)
        result.set(i, 0, x.get(i));
    for (int i = 0; i < 3; ++i)
        result.set(i, 1, y.get(i));
    for (int i = 0; i < 3; ++i)
        result.set(i, 2, z.get(i));
    for (int i = 0; i < 3; ++i)
        result.set(i, 3, e.get(i));
    result.set(3, 3, 1);
    return result;
}

void Matrix4::print(std::string comment) const {
    //Width constants and variables
    static const int pointWidth = 1;
    static const int precisionWidth = 4;
    int integerWidth = 1;

    //Determine the necessary width to the left of the decimal point
    float* elementPtr = (float*) m;

    float maxValue = fabsf(*(elementPtr++));
    while (elementPtr++ < ((float*) m + 16)) if (fabsf(*elementPtr) > maxValue) maxValue = fabsf(*elementPtr);
    while (maxValue >= 10.0) {
        ++integerWidth;
        maxValue /= 10.0;
    }

    //Sum up the widths to determine the cell width needed
    int cellWidth = integerWidth + pointWidth + precisionWidth;

    //Set the stream parameters for fixed number of digits after the decimal point
    //and a set number of precision digits
    std::cout << std::fixed;
    std::cout << std::setprecision(precisionWidth);

    //Print the comment
    std::cout << comment << std::endl;

    //Loop through the matrix elements, format each, and print them to screen
    float cellValue;
    for (int element = 0; element < 4; element++) {
        std::cout << std::setw(1) << (element == 0 ? "[" : " ");
        for (int vector = 0; vector < 4; vector++) {
            cellValue = m[vector][element];
            std::cout << std::setw(cellWidth + (cellValue >= 0.0 ? 1 : 0)) << cellValue;
            std::cout << std::setw(0) << (vector < 3 ? " " : "");
        }
        std::cout << std::setw(1) << (element == 3 ? "]" : " ") << std::endl;
    }
}
