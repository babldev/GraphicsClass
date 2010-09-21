/*
 *  GLMovable.h
 *  Project1
 *
 *  Created by Brady Law on 9/21/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "GLDrawable.h"

class GLMovable : public GLDrawable {
    GLMovable(float x, float y) : x_(x), y_(y) { }
    
    void set_x(float x) { x_ = x; }
    void set_y(float y) { y_ = y; }
    
    float x() { return x_; }
    float y() { return y_; }
    
    void set_dx(float dx) { dx_ = dx; }
    void set_dy(float dy) { dy_ = dy; }
    
    float dx() { return dx_; }
    float dy() { return dy_; }
    
    void set_ddx(float ddx) { ddx_ = ddx; }
    void set_ddy(float ddy) { ddy_ = ddy; }
    
    float ddx() { return ddx_; }
    float ddy() { return ddy_; }
    
protected:
    float x_ = 0, y_ = 0;
    float dx_ = 0, dy_ = 0;
    float ddx_ = 0, ddy_ = 0;
}
