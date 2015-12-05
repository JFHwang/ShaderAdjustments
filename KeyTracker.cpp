/* 
 * File:   KeyTracker.cpp
 * Author: Evan
 * 
 * Created on November 29, 2015, 11:15 AM
 */

#include "KeyTracker.h"

bool Keys::_down[256] = {};
std::list<Keys::Callback> Keys::_listeners;

bool Keys::isPressed(char key) {
    return _down[key];
}

void Keys::registerCallback(Keys::Callback listener) {
    _listeners.push_back(listener);
}

void Keys::onKeyPress(unsigned char key, int x, int y) {
    if (key >= 0 && key <= 256)
        _down[key] = true;

    for (auto listener : _listeners) {
        if (listener(key))
            break;
    }
}

void Keys::onKeyRelease(unsigned char key, int x, int y) {
    if (key >= 0 && key <= 256)
        _down[key] = false;
}