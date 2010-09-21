/*
 *  GLMovable.h
 *  Project1
 *
 *  Created by Brady Law on 9/21/10.
 *  Copyright 2010 Brady Law. All rights reserved.
 *
 */

#include "GLDrawable.h"
#include "Vector2d.h"

class GLMovable : public GLDrawable {
public:
    GLMovable(Vector2d pos) : pos_(pos) { }
    ~GLMovable() { }
    
    void DrawInWindow(GLWindow* window) { }
    void Tick(int time_elapsed);
    
    // Variables
    Vector2d pos_, vel_, acc_;
    static const double ANIMATION_SPEED;
};
