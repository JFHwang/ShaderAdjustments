/* 
 * File:   SkyBox.h
 * Author: Evan
 *
 * Created on November 10, 2015, 10:35 PM
 */

#ifndef SKYBOX_H
#define	SKYBOX_H
#include "Texture.h"
#include "Material.h"
#include <GL/freeglut.h>
#include <iostream>

#include <string>
#include <limits.h>
#include <unistd.h>

class SkyBox {
public:
    static const int size = 600;

    Texture top, down, front, left, right, back;
    Material m;

    SkyBox() : top("up2.ppm"),
    down("down.ppm"),
    front("front.ppm"),
    left("left.ppm"),
    right("right.ppm"),
    back("back.ppm"), m(Material::getDefault()) {
        perror("Loaded textures:");


        char result[ PATH_MAX ];
        ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
        std::cout << "PWD: " << std::string(result, (count > 0) ? count : 0) << std::endl;
    }

    SkyBox(const SkyBox& orig);
    virtual ~SkyBox();

    void draw() {
        glColor3f(1, 1, 1);
        front.bind();
        m.apply();
        m.emissionColor = Color(1,1,1);
        m.ambientColor = Color(1,1,1);
        // Make sure no bytes are padded:
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        // Select GL_MODULATE to mix texture with polygon color for shading:
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        // Use bilinear interpolation:
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        /* draw quad, takes 4 vertices */
        glBegin(GL_QUADS);
        // note that textures are stored "upside down"
        glTexCoord2f(1, 1);
        glVertex3f(-size, -size, -size);
        glTexCoord2f(0, 1);
        glVertex3f(size, -size, -size);
        glTexCoord2f(0, 0);
        glVertex3f(size, size, -size);
        glTexCoord2f(1, 0);
        glVertex3f(-size, size, -size);
        glEnd();
        front.unbind();

        left.bind();
        glBegin(GL_QUADS);
        glTexCoord2f(1, 1);
        glVertex3f(-size, -size, size);
        glTexCoord2f(0, 1);
        glVertex3f(-size, -size, -size);
        glTexCoord2f(0, 0);
        glVertex3f(-size, size, -size);
        glTexCoord2f(1, 0);
        glVertex3f(-size, size, size);
        glEnd();
        left.unbind();



        right.bind();
        glBegin(GL_QUADS);
        glTexCoord2f(1, 1);
        glVertex3f(size, -size, -size);
        glTexCoord2f(0, 1);
        glVertex3f(size, -size, size);
        glTexCoord2f(0, 0);
        glVertex3f(size, size, size);
        glTexCoord2f(1, 0);
        glVertex3f(size, size, -size);
        glEnd();
        right.unbind();

        back.bind();
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex3f(-size, size, size);
        glTexCoord2f(1, 0);
        glVertex3f(size, size, size);
        glTexCoord2f(1, 1);
        glVertex3f(size, -size, size);
        glTexCoord2f(0, 1);
        glVertex3f(-size, -size, size);
        glEnd();
        back.unbind();


        down.bind();
        glBegin(GL_QUADS);

        glTexCoord2f(0, 1);
        glVertex3f(-size, -size, size);
        glTexCoord2f(1, 1);
        glVertex3f(size, -size, size);
        glTexCoord2f(1, 0);
        glVertex3f(size, -size, -size);
        glTexCoord2f(0, 0);
        glVertex3f(-size, -size, -size);
        glEnd();
        down.unbind();


        top.bind();
        glBegin(GL_QUADS);
        glTexCoord2f(1, 1);
        glVertex3f(-size, size, -size);
        glTexCoord2f(0, 1);
        glVertex3f(size, size, -size);
        glTexCoord2f(0, 0);
        glVertex3f(size, size, size);
        glTexCoord2f(1, 0);
        glVertex3f(-size, size, size);
        glEnd();
        top.unbind();
    }
private:

};

#endif	/* SKYBOX_H */

