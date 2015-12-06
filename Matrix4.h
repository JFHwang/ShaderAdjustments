#ifndef CSE167_Matrix4_h
#define CSE167_Matrix4_h

#include <string>
#include <cmath>

class Vector3;
class Vector4;

class Matrix4 {
protected:
    Matrix4(bool DONTMEMCOPY);
    //These are in column-major
    //The first index is for the column, and the second is for the row
    //Ex: m[2][1] is the 3rd column (index 2) and second element in that column (index 1)
    //This is the matrix format used by OpenGL internally.
    float m[4][4];

public:
    static Matrix4 from(const Vector3&, const Vector3&, const Vector3&, const Vector3&);
    static Matrix4 identity();
   


    static Matrix4 makeRotateX(float);
    static Matrix4 makeRotateY(float);
    static Matrix4 makeRotateZ(float);
    static Matrix4 makeRotateArbitrary(Vector3&, float);

    static Matrix4 makeScale(float, float, float);
    static Matrix4 makeScale(float);

    static Matrix4 makeTranslate(float, float, float);
    static Matrix4 makeTranslate(Vector3);


    Matrix4();
    Matrix4(const Matrix4&);
    Matrix4(float arr[16]);
    Matrix4(float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float);
    void set(float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float);

    __always_inline void set(int r, int c, float value) {
        m[c][r] = value;
    }

    __always_inline float get(int row, int col) const {
        return m[col][row];
    }

    __always_inline float cm(int col, int row) const {
        return m[col][row];
    }

    static Matrix4 getTranslation(const Matrix4& other);


    Vector4 getColumn(int index) const;
    Vector3 getTranslation() const;

    Matrix4& operator=(Matrix4);

    float* ptr();

    void identify();

    Matrix4 multiply(const Matrix4) const;
    Matrix4 operator*(const Matrix4) const;
    Vector4 multiply(const Vector4) const;
    Vector4 operator*(const Vector4) const;
    Vector3 multiply(const Vector3) const;
    Vector3 operator*(const Vector3) const;


    Matrix4& applyMe(const Matrix4&);
    Matrix4& applyOther(const Matrix4&);

    void setTranslation(Vector3 position);


    Matrix4 transpose(void) const;
    Matrix4 inverse(void) const;
    Matrix4 rigidInverse(void) const;

    Matrix4 makePerspectiveProjection(float, float, float, float, float);
    Matrix4 makeViewport(float, float, float, float);

    void print(std::string) const;

};

#endif
