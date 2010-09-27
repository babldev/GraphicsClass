/*
 *  GLMovable.h
 *  Project1
 *
 *  Created by Brady Law on 9/21/10.
 *  Copyright 2010 Brady Law. All rights reserved.
 *
 */

#ifndef INC_GLMOVABLE_H
#define INC_GLMOVABLE_H

#include "GraphicsLib/GLDrawable.h"
#include "GraphicsLib/Math/Vector2d.h"

class GLMovable : public GLDrawable {
public:
    GLMovable(Vector2d pos) : pos_(pos) { }
    ~GLMovable() { }
    
    virtual void Draw() { }
    virtual void Tick(int time_elapsed);
    
    // Variables
    Vector2d pos_, vel_, acc_;
    static const float ANIMATION_SPEED = 0.01;
    static const float ROTATE_CONSTANT = 50.0;
};

#endif /* INC_GLMOVABLE_H */