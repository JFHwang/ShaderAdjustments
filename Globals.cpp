#include "Globals.h"
#include "Sphere.h"


Camera Globals::camera;


//OBJObject Globals::bear("bear.obj", 1), Globals::bunny("bunny.obj", 32), Globals::dragon("dragon.obj", 255);
Light Globals::point(0, Light::POINT_LIGHT), Globals::spotLight(2, Light::SPOT_LIGHT), Globals::directional(6, Light::DIRECTIONAL_LIGHT);

bool Globals::isBoundsOn = false, Globals::isAnimated = true;

list<OBJObject*> Globals::drawables = list<OBJObject*>();

//Light Globals::light(7);

MatrixStack Globals::drawData(Matrix4::identity());
UpdateData Globals::updateData;


int fact(int n){
    int total = 1;
    for(int i = 2; i <= n; ++i)
        total *= i;
    return total;
}


int choose(int n, int k){
    int top = fact(n);
    int left = fact(n-k);
    int right = fact(k);
    
    return top/(left*right);
}



float frand(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}
