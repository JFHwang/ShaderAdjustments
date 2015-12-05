/* 
 * File:   Game.cpp
 * Author: Evan
 * 
 * Created on November 27, 2015, 7:28 PM
 */

#include "Game.h"
#include "Ball.h"

Ball* Game::ball = new Ball(Vector3(width/2, .5, height/2));
bool Game::isPaused = false;