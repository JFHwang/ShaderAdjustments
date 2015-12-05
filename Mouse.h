/* 
 * File:   Mouse.h
 * Author: Evan
 *
 * Created on October 29, 2015, 1:09 PM
 */



#ifndef MOUSE_H
#define	MOUSE_H

#include <GL/glut.h>
#include <list>

#include "Globals.h"
#include "Point.h"

using namespace std;

class Mouse {
public:

    enum State {
        UP = false, DOWN = true
    };

    enum Button {
        LEFT = GLUT_LEFT_BUTTON, MIDDLE_UP = 3, MIDDLE_DOWN = 4, RIGHT = GLUT_RIGHT_BUTTON
    };

    static list<Mouse*> mice;

    Mouse() {
        enable();
    }


    Mouse(const Mouse& orig);

    virtual ~Mouse() {
        disable();
    }

    void disable() {
        mice.remove(this);
    }

    void enable() {
        mice.push_back(this);
    }

    static int x, y;
    static State left, middle, right;

    virtual void onLeftClick() {
    }

    virtual void onRightClick() {
    }

    virtual void onMiddleClick() {
    }

    virtual void onLeftDrag(Point prev, Point next) {
    }

    virtual void onRightDrag(Point prev, Point next) {
    }



    virtual void onMouseScroll(State direction) {

    }

    static void mouseClick(int butt, int state, int xx, int yy) {
        cout << "Click " << butt << endl;

        x = xx;
        y = yy;

        if (butt == MIDDLE_DOWN) {
            for (auto listener : mice) {
                listener->onMouseScroll(DOWN);
            }
        } else if (butt == MIDDLE_UP) {
            for (auto listener : mice) {
                listener->onMouseScroll(UP);
            }
        }
        else if (butt == LEFT) {
            left = (state == GLUT_UP) ? UP : DOWN;
            for (auto listener : mice) {
                listener->onLeftClick();
            }
        } else {
            right = (state == GLUT_UP) ? UP : DOWN;
            for (auto listener : mice) {
                listener->onRightClick();
            }
        }
    }

    static void mouseDragged(int xx, int yy) {

        cout << "Dragged at (" << xx << ", " << yy << ")" << endl;

        Point prev(x, y);
        Point next(xx, yy);
        x = xx;
        y = yy;

        for (auto listener : mice) {
            if (left)
                listener->onLeftDrag(prev, next);
            if (right)
                listener->onRightDrag(prev, next);
        }
    }

    static void mouseWheel(int wheel, int direction, int x, int y) {
        cout << "Wheel" << endl;
        for (auto listener : mice) {
            listener->onMouseScroll((direction > 0) ? UP : DOWN);
        }
    }
    
    

private:

};

#endif	/* MOUSE_H */

