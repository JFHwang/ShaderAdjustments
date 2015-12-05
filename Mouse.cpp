/* 
 * File:   Mouse.cpp
 * Author: Evan
 * 
 * Created on October 29, 2015, 1:09 PM
 */

#include "Mouse.h"

list<Mouse*> Mouse::mice = list<Mouse*>();


 int Mouse::x = 0, Mouse::y = 0;
    Mouse::State Mouse::left = UP;
    Mouse:: State Mouse::right = UP;
     Mouse::State Mouse::middle = UP;


