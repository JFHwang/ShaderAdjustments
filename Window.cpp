#include <iostream>
#include <GL/glew.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Window.h"
#include "Cube.h"
#include "Matrix4.h"
#include "Globals.h"
#include "Sphere.h"
#include "Group.h"
#include "Frustum.h"
#include "SkyBox.h"
#include "Game.h"

int Window::width = 900; //Set window width in pixels here
int Window::height = 900; //Set window height in pixels here
float Window::spinDelta = .005;


enum Control {
    OBJ = 0, POINT = 1, SPOT = 2, DIRECT = 3, CAMERA = 4
};

static Control keyState = CAMERA;
static Game* game = new Game();
static Shader* phongShader= NULL;
static Shader* geometryPassShader = NULL;
static Shader* deferredPassShader = NULL;
GLuint positionID;
GLuint normalID;
GLuint specID;
GLuint gPositionTexture;
GLuint gNormalTexture;
GLuint gSpecTexture;
GLuint gPosition;
GLuint gNormal; 
GLuint gSpec;
GLuint depthBuffer;
GLuint gBuffer;

void Window::initialize(void) {
    glewInit();
    //Setup the light
    Globals::point.setPosition(Vector4(-66, -100, -66.5, 500));
    Globals::point.quadraticAttenuation = 1.15;
    Globals::point.constantAttenuation = 5.85;
    Globals::point.linearAttenuation = 5.85;
    
    Globals::spotLight.setPosition(Vector4(-2.5, -2.5, 7.5, 0));
    Globals::directional.setPosition(Vector4(0, 0, 5555, 0));
    Globals::directional.scaleIntensity(.25f);
    phongShader = new Shader("VShader.c", "LShader.c");
	geometryPassShader = new Shader("gPass.vert", "gPass.frag");
	deferredPassShader = new Shader("deferredPass.vert", "deferredPass.frag");
 
    glEnable(GL_NORMALIZE);
	
	positionID = glGetUniformLocationARB(deferredPassShader->getPid(),"gPosition");
	normalID = glGetUniformLocationARB(deferredPassShader->getPid(),"gNormal");
	specID = glGetUniformLocationARB(deferredPassShader->getPid(),"gSpec");

	
	setupGBuffer();	
}


void Window::idleCallback() {
    static int frameCount = 0;
    static int currentTime = 0, previousTime = 0;
    static int lastFrame = 0;

    ++frameCount;

    //  Get the number of milliseconds since glutInit called
    //  (or first call to glutGet(GLUT ELAPSED TIME)).
    currentTime = glutGet(GLUT_ELAPSED_TIME);

    //  Calculate time passed
    int timeInterval = currentTime - previousTime;

    if (timeInterval > 1000) {
        //  calculate the number of frames per second
        float fps = frameCount / (timeInterval / 1000.0f);
        std::cout << "FPS: " << fps << std::endl;

        //  Set time
        previousTime = currentTime;

        //  Reset frame count
        frameCount = 0;
    }



    //Set up a static time delta for update calls
    Globals::updateData.dt = (currentTime - lastFrame) / 1000.0; // 60 fps
    lastFrame = currentTime;

    static int tick = 0;

    game->update(++tick);


    displayCallback();
}


void Window::reshapeCallback(int w, int h) {
    width = w; //Set the window width
    height = h; //Set the window height
    glViewport(0, 0, w, h); //Set new viewport size
    glMatrixMode(GL_PROJECTION); //Set the OpenGL matrix mode to Projection
    glLoadIdentity(); //Clear the projection matrix by loading the identity
    gluPerspective(60.0, double(width) / (double) height, .5, 256.0); //Set perspective projection viewing frustum
    Frustum::update(width, height);
}


void Window::displayCallback() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(Globals::camera.getInverseMatrix().ptr());
    glPushMatrix();

    //Replace the current top of the matrix stack with the inverse camera matrix
    //This will convert all world coordiantes into camera coordiantes
    glLoadMatrixf(Globals::camera.getInverseMatrix().ptr());

	Globals::directional.bind();
/*  Globals::spotLight.bind();
    Globals::point.setPosition(game->ball->getTranslation());
    Globals::point.bind();

    game->ball->ballLight.setPosition(game->ball->getTranslation());
    game->ball->ballLight.bind();
*/  
    MatrixStack stack(Matrix4::identity());
//    MatrixStack s2 = stack;

	//phongShader->bind();

	
	
////////////////////////////////////////////////////////////////	
///////This section is taken directly from the example code///////
///////////Gets the textures??///////////////////////////
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, gBuffer);
	glPushAttrib(GL_VIEWPORT_BIT);
	glViewport(0,0,Window::width, Window::height);

	// Clear the render targets
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);

	// Specify what to render an start acquiring
	GLenum buffers[] = { GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT, GL_COLOR_ATTACHMENT2_EXT };
	glDrawBuffers(3, buffers);
/////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
	game->draw(stack);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glPopAttrib();  /////////Not sure about this line either
	
	
	
	//render using 2nd pass shader
////////////////////////////////////////////////////////////////
//////Code taken directly from source code//////////////////////
	//Projection setup
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0,Window::width,0,Window::height,0.1f,2);	
	
	//Model setup
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	
	glUseProgramObjectARB(deferredPassShader->getPid());
	
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, gPositionTexture);
	glUniform1iARB ( positionID, 0 );
	
	glActiveTextureARB(GL_TEXTURE1_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, gNormalTexture);
	glUniform1iARB ( normalID, 1 );
	
	glActiveTextureARB(GL_TEXTURE2_ARB);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, gSpecTexture);
	glUniform1iARB ( specID, 2 );

	// Render the quad
	glLoadIdentity();
	glColor3f(1,1,1);
	glTranslatef(0,0,-1.0);
	
	glBegin(GL_QUADS);
	glTexCoord2f( 0, 0 );
	glVertex3f(    0.0f, 0.0f, 0.0f);
	glTexCoord2f( 1, 0 );
	glVertex3f(   (float) Window::width, 0.0f, 0.0f);
	glTexCoord2f( 1, 1 );
	glVertex3f(   (float) Window::width, (float) Window::height, 0.0f);
	glTexCoord2f( 0, 1 );
	glVertex3f(    0.0f,  (float) Window::height, 0.0f);
	glEnd();
	
	// Reset OpenGL state
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	glActiveTextureARB(GL_TEXTURE1_ARB);
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	glActiveTextureARB(GL_TEXTURE2_ARB);
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	glUseProgramObjectARB(0);
	
	//Reset to the matrices	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
/////////////////////////////////////////////////////////////
	
    //phongShader->unbind();
    
    //Globals::point.draw(s2);
    
   // Globals::point.draw(Globals::drawData);
   // Globals::spotLight.draw(Globals::drawData);
game->draw(stack);
    //Pop off the changes we made to the matrix stack this frame
    glPopMatrix();


    glFlush();
    glutSwapBuffers();

}



/*
 * Helper Function
 * Sets up the GBuffer
 */
void Window::setupGBuffer() {
	//Setting up G-buffer
	//Buffer is necessary so that shader can access data from all pixels when evaluating a certain pixel
	
	glGenFramebuffersEXT(1, &gBuffer);
	glGenRenderbuffersEXT(1, &gSpec);
	glGenRenderbuffersEXT(1, &gPosition);
	glGenRenderbuffersEXT(1, &gNormal);
	glGenRenderbuffersEXT(1, &depthBuffer);

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, gBuffer);
	
	//Binding to render buffers is necessary in older versions of GLSL
	
	// Bind the diffuse render target
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, gSpec);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_RGBA, Window::width, Window::height);
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_RENDERBUFFER_EXT, gSpec);
	// Bind the position render target
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, gPosition);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_RGBA32F_ARB, Window::width, Window::height);
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT1_EXT, GL_RENDERBUFFER_EXT, gPosition);
	// Bind the normal render target
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, gNormal);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_RGBA16F_ARB, Window::width, Window::height);
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT2_EXT, GL_RENDERBUFFER_EXT, gNormal);
	// Bind the depth buffer
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depthBuffer);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, Window::width, Window::height);
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, depthBuffer);
	
//Set up the 3 textures that go in the buffer 
	// Generate and bind the OGL texture for diffuse
	glGenTextures(1, &gSpecTexture);
	glBindTexture(GL_TEXTURE_2D, gSpecTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Window::width, Window::height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, gSpecTexture, 0);

	// Generate and bind the OGL texture for positions
	glGenTextures(1, &gPositionTexture);
	glBindTexture(GL_TEXTURE_2D, gPositionTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F_ARB, Window::width, Window::height, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT1_EXT, GL_TEXTURE_2D, gPositionTexture, 0);

	// Generate and bind the OGL texture for normals
	glGenTextures(1, &gNormalTexture);
	glBindTexture(GL_TEXTURE_2D, gNormalTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F_ARB, Window::width, Window::height, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT2_EXT, GL_TEXTURE_2D, gNormalTexture, 0);

	GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if( status != GL_FRAMEBUFFER_COMPLETE_EXT)
            std::cout << "Error with framebuffer or something" << std::endl;

    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}




const float scaleFactor = .95;
const float orbitDelta = 3.14159265 / 180 * 5; // 3.141592 / 180  == 1 degree;   
const float moveDelta = .1;

const Matrix4 xt = Matrix4().makeTranslate(moveDelta, 0, 0);
const Matrix4 nxt = Matrix4().makeTranslate(-moveDelta, 0, 0);

const Matrix4 yt = Matrix4().makeTranslate(0, moveDelta, 0);
const Matrix4 nyt = Matrix4().makeTranslate(0, -moveDelta, 0);

const Matrix4 zt = Matrix4().makeTranslate(0, 0, moveDelta);
const Matrix4 nzt = Matrix4().makeTranslate(0, 0, -moveDelta);

const Matrix4 scalaUp = Matrix4().makeScale(1 / scaleFactor, 1 / scaleFactor, 1 / scaleFactor);
const Matrix4 scalaDown = Matrix4().makeScale(scaleFactor, scaleFactor, scaleFactor);

const Matrix4 orbit = Matrix4().makeRotateZ(orbitDelta);
const Matrix4 reverseOrbit = Matrix4().makeRotateZ(-orbitDelta);


bool Window::handleKeypress(unsigned char key) {

    if (key >= '0' && key <= '4'){
        keyState = (Control) (key - '0');
        return true;
    }
    
    
    switch (key) {
        case 'b': Globals::isBoundsOn = !Globals::isBoundsOn;
            break;
        case 'A': Globals::isAnimated = !Globals::isAnimated;
            break;
        default: return false;
    }
    
    return true;
}

void Window::specialKeys(int key, int x, int y) {
    if (keyState == CAMERA) {
        switch (key) {
            case GLUT_KEY_UP:
                Globals::camera.rotateX(10 * spinDelta);
                return;
            case GLUT_KEY_DOWN:
                Globals::camera.rotateX(10 * -spinDelta);
                return;
            case GLUT_KEY_LEFT:
                Globals::camera.rotateY(10 * spinDelta);
                return;
            case GLUT_KEY_RIGHT:
                Globals::camera.rotateY(-10 * spinDelta);
                return;
        }
    }
}

class Listener : public Mouse {
    Vector3 lastTrack;

public:

    Listener() {
        lastTrack = Vector3(0, 0, 0);
    }

    Vector3 trackBallMapping(Point point) {
        Vector3 v((2.0 * point.x - Window::width) / Window::width, (Window::height - 2.0 * point.y) / Window::height, 0);
        double d = v.magnitude(); // this is the distance from the trackball's origin to the mouse location, without considering depth (=in the plane of the trackball's origin)
        d = (d < 1.0) ? d : 1.0; // this limits d to values of 1.0 or less to avoid square roots of negative values in the following line

        v.set(2, sqrt(1.001 - d * d));
        return v.normalize();
    }

    void onLeftClick() override {
    }

    void onRightClick() override {
    }

    void onMiddleClick() override {
    }

    void onLeftDrag(Point prev, Point next) override {
        Vector3 mapped = trackBallMapping(next);
        Vector3 cross = lastTrack.cross(mapped);

        cross = cross.normalize();
        lastTrack = mapped;

        Matrix4 r = Matrix4().makeRotateArbitrary(cross, .05);

        switch (keyState) {
            case OBJ:
                break;
            case POINT:
                Globals::point.toWorld.applyOther(r);
                break;
            case SPOT:
                Globals::spotLight.toWorld.applyOther(r);
                break;
            case DIRECT:
                Globals::directional.toWorld.applyOther(r);
                break;
            case CAMERA:
                Globals::camera.translate((prev.toV() - next.toV()).multiply(Vector3(.1, -.1, 1)));
        }
    }

    void onRightDrag(Point prev, Point next) override {
        Point diff = next.minus(prev);

        Vector3 dp = diff.scale(1.0 / 25);
        if (keyState == SPOT) {
            if (abs(diff.x) > abs(diff.y)) {
                Globals::spotLight.exp += (diff.x > 0) ? 1 : -1;
            } else {
                Globals::spotLight.angle += (diff.y > 0) ? 1 : -1;
            }
        }
    }

    void onMouseScroll(State direction) override {


        if (direction == UP) {
            if (keyState == POINT) {
                Vector3 dist = Globals::point.toWorld.getColumn(3).toVector3();
                Globals::point.setPosition(dist.scale(1.05).toVector4(1) + Vector4(0, 0, .1, 0));
            } else if (keyState == SPOT) {
                Vector3 dist = Globals::spotLight.toWorld.getColumn(3).toVector3();
                Globals::spotLight.setPosition(dist.scale(1.05).toVector4(1) + Vector4(0, 0, .1, 0));
            } else if (keyState == CAMERA) {
                Globals::camera.translate(Vector3(0, 0, -1));
            }
        } else {
            if (keyState == POINT) {
                Vector3 dist = Globals::point.toWorld.getColumn(3).toVector3();
                Globals::point.setPosition(dist.scale(.95).toVector4(1)+ Vector4(0, 0, -.1, 0));
            } else if (keyState == SPOT) {
                Vector3 dist = Globals::spotLight.toWorld.getColumn(3).toVector3();
                Globals::spotLight.setPosition(dist.scale(.95).toVector4(1)+ Vector4(0, 0, -.1, 0));
            } else if (keyState == CAMERA) {
                Globals::camera.translate(Vector3(0, 0, 1));
            }
        }
    }


};
static Mouse* mouseListener = new Listener();



//TODO: Mouse callbacks!

//TODO: Mouse Motion callbacks!
