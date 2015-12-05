/* 
 * File:   KeyTracker.h
 * Author: Evan
 *
 * Created on November 29, 2015, 11:15 AM
 */

#ifndef KEYTRACKER_H
#define	KEYTRACKER_H
#include <list>

namespace Keys {
    typedef bool (*Callback)(unsigned char);

    extern bool _down[256];
    extern std::list<Callback> _listeners;


    bool isPressed(char key);

    void registerCallback(Callback listener);

    void onKeyPress(unsigned char key, int x, int y);

    void onKeyRelease(unsigned char key, int x, int y);
}


#endif	/* KEYTRACKER_H */

