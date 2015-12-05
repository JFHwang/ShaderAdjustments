#ifndef CSE167_Vector3_h
#define CSE167_Vector3_h

#include <string>

class Vector4;

class Vector3 {
protected:

    float m[3];

public:

    Vector3();
    Vector3(float, float, float);
    virtual ~Vector3(void);

    float* ptr();

    void set(float, float, float);
    void set(int index, float value);
    float& operator[](int);

    Vector3 add(const Vector3) const ;
    Vector3 operator+(const Vector3) const;
    
    Vector3 operator=(const Vector3 other) {
        for(int i = 0; i < 3; ++i)
            m[i] = other.m[i];
        return *this;
    }
    
    
    Vector3 subtract(const Vector3) const;
    Vector3 operator-(const Vector3) const;

    Vector3 negate(void) const;
    Vector3 scale(float) const;
    Vector3 multiply(float) const;
    Vector3 operator*(float) const ;
    Vector3 multiply(Vector3) const;
    Vector3 operator*(Vector3) const;

    float dot(const Vector3) const;
    Vector3 cross(Vector3) const;

    float angle(Vector3);

    float magnitude(void) const;

    Vector3 normalize(void) const;

    Vector4 toVector4(float) const;

    void print(std::string) const;
    
    Vector3 proj(const Vector3 onto) const;
    

    float getX() const;
    float getY() const;
    float getZ() const;
    float getW() const;
    float get(int i) const;
};

#endif
