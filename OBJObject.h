#ifndef CSE167_OBJObject_h
#define CSE167_OBJObject_h

#include <iostream>
#include <vector>
#include <string>
#include "Vector3.h"
#include "Drawable.h"

struct Face {
    int vertexIndices[3];
    int normalIndices[3];
    
    float vertices[3][3];
    float norms[3][3];
    
    //Add more members as necessary
};

class OBJObject : public Drawable {
protected:

    //Storage vectors
    std::vector<Vector3*>* verticesTmp;
    std::vector<Vector3*>* normalsTmp;
    std::vector<Face*>* faces;
    

    //Helper functions
    std::vector<std::string>& split(const std::string&, char, std::vector<std::string>&);
    std::vector<std::string> split(const std::string&, char);

    //Parse
    void parse(std::string&);

public:

    
    std::vector<Vector3>* flatNormals;
    std::vector<Vector3>* flatVectors;

    OBJObject();
    OBJObject(std::string, float);
    OBJObject(const OBJObject& other);
    virtual ~OBJObject(void);

    virtual void draw(MatrixStack&);
    virtual void update(UpdateData&);

    
   
    virtual void normalize(float factor);
};

#endif
