/* 
 * File:   Frustum.cpp
 * Author: Evan
 * 
 * Created on November 4, 2015, 8:01 PM
 */

#include "Frustum.h"

  Vector3 Frustum::origin(0,0,0), Frustum::topL(0,0,0), Frustum::topR(0,0,0), Frustum::bottomL(0,0,0), Frustum::bottomR(0,0,0);
    
  Vector3 Frustum::topN(0,0,0), Frustum::bottomN(0,0,0), Frustum::leftN(0,0,0), Frustum::rightN(0,0,0), Frustum::frontN(0,0,-1);
    