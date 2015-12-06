#include "OBJObject.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Window.h"
#include "math.h"
#include <sstream>
#include <fstream>
#include <unordered_map>

#define deleteVector(__type__, __vect__) do {\
                                   std::vector<__type__>::iterator iter; \
                                   std::vector<__type__>::iterator end; \
                                   iter = __vect__->begin();\
                                   end = __vect__->end();\
                                   while(iter != end) delete (*(iter++));\
                                   delete __vect__;\
                               } while(false)

OBJObject::OBJObject(std::string filename, float shiny) : Drawable() {
    this->verticesTmp = new std::vector<Vector3*>();
    this->normalsTmp = new std::vector<Vector3*>();
    ///  this->faces = new std::vector<Face*>();
    this->flatNormals = new std::vector<Vector3>();
    this->flatVectors = new std::vector<Vector3>();

    material.shininess = shiny;
    parse(filename);
}

OBJObject::OBJObject() : Drawable() {
    this->verticesTmp = new std::vector<Vector3*>();
    this->normalsTmp = new std::vector<Vector3*>();
    ///  this->faces = new std::vector<Face*>();
    this->flatNormals = new std::vector<Vector3>();
    this->flatVectors = new std::vector<Vector3>();

}

OBJObject::OBJObject(const OBJObject& other) {
    this->toWorld = Matrix4::identity();
    this->material = other.material;
    this->verticesTmp = other.verticesTmp;
    this->normalsTmp = other.normalsTmp;
    //   this->faces = other.faces;
    this->flatNormals = other.flatNormals;
    this->flatVectors = other.flatVectors;
}

#include <limits>
#include <cstdio>

void OBJObject::normalize(float factor) {
    toWorld.identify();

    float miny = std::numeric_limits<float>::infinity(), maxy = -std::numeric_limits<float>::infinity();
    float minx = miny, maxx = maxy;
    float maxz = maxy;
    float minz = miny;

    for (auto& v : *flatVectors) {
        maxx = std::max(maxx, v.getX());
        maxy = std::max(maxy, v.getY());

        minx = std::min(minx, v.getX());
        miny = std::min(miny, v.getY());

        maxz = std::max(maxz, v.getZ());
        minz = std::min(minz, v.getZ());

    }

    std::printf("X(%f, %f); Y(%f,%f) @z=%f\n", minx, maxx, miny, maxy, maxz);

    const float cx = (minx + maxx) / 2.0f;
    const float cy = (miny + maxy) / 2.0f;
    const float cz = (minz + maxz) / 2.0f;


    
    const float tan = factor*.577;
    
    
    const float sx = tan/(maxx - cx);//width / (maxx - minx);
    const float sy = tan/(maxy - cy); //height / (maxy - miny);

    std::cout << "Normalizing by S(" << sx << ", " << sy << ") T(" << -cx << ", " << -cy << ")" << std::endl;


    const float scale = sx < 1 && sy < 1 ? std::max(sx, sy) : std::min(sx, sy);


    toWorld.setTranslation(Vector3(-cx, -cy, -cz));
    toWorld = Matrix4().makeScale(scale, scale, scale) * toWorld;

}

OBJObject::~OBJObject() {
    //Delete any dynamically allocated memory/objects here

    deleteVector(Vector3*, verticesTmp);
    deleteVector(Vector3*, normalsTmp);
    //    deleteVector(Face*, faces);
}

void OBJObject::draw(MatrixStack& data) {
    material.apply();

    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glMultMatrixf(toWorld.ptr());

    glBegin(GL_TRIANGLES);


    for (unsigned i = 0; i < flatVectors->size(); ++i) {
        glNormal3fv(flatNormals->at(i).ptr());
        glVertex3fv(flatVectors->at(i).ptr());
    }

    glEnd();

    glPopMatrix();
}

void OBJObject::update(UpdateData& data) {
    //
}

void OBJObject::parse(std::string& filename) {
    std::ifstream infile(filename);



    std::string line;
    std::vector<std::string> tokens;

    int lineNum = 0;
    std::string prefix;
    float x, y, z;


    std::cout << "Starting parse..." << std::endl;

    //While all your lines are belong to us
    while (getline(infile, line)) {

        std::istringstream iss(line);
        iss >> prefix;


        //Progress
        if (++lineNum % 100000 == 0)
            std::cout << "At line " << lineNum << std::endl;



        //If first token is a v then it gots to be a vertex
        if (prefix.compare("v") == 0) {
            //Parse the vertex line

            iss >> x >> y >> z;

            verticesTmp->push_back(new Vector3(x, y, z));
        } else if (prefix.compare("vn") == 0) {

            iss >> x >> y >> z;

            //Parse the normal line
            Vector3* norm = new Vector3(Vector3(x, y, z).normalize());

            normalsTmp->push_back(norm);
        } else if (prefix.compare("f") == 0) {



            for (int i = 1; i < 4; ++i) {

                float* norms = new float[3];
                float* verts = new float[3];

                char c;



                int vi;
                int ni;

                iss >> vi >> c >> c >> ni;

                --vi;
                --ni;

                for (int x = 0; x < 3; ++x) {
                    norms[x] = normalsTmp->at(ni)->get(x);
                    verts[x] = verticesTmp->at(vi)->get(x);
                }

                flatVectors->push_back(Vector3(verts[0], verts[1], verts[2]));
                flatNormals->push_back(Vector3(norms[0], norms[1], norms[2]));
            }

            //face->setVertices(vertices, normals);

            //faces->push_back(face);
        } else if (prefix.compare("How does I are C++?!?!!") == 0) {
            //Parse as appropriate
            //There are more line types than just the above listed
            //See the Wavefront Object format specification for details
        }

    }

    std::cout << "Done parsing." << std::endl;
}

//Split functions from the interwebs
//http://stackoverflow.com/questions/236129/split-a-string-in-c

std::vector<std::string>& OBJObject::split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> OBJObject::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}
