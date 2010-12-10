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
#include "GraphicsLib/Math/Vector3d.h"

class GLMovable : public GLDrawable {
public:
    GLMovable(Vector3d pos) : pos_(pos) { }
    ~GLMovable() { }
    
    virtual void Draw() { }
    virtual void Tick(int time_elapsed);
    
    Vector3d pos() {
        return pos_;
    }
    
    Vector3d vel() {
        return vel_;
    }
    
    Vector3d acc() {
        return acc_;
    }
    
    void set_pos(Vector3d pos) {
        pos_ = pos;
    }
    
    void set_vel(Vector3d vel) {
        vel_ = vel;
    }
    
    void set_acc(Vector3d acc) {
        acc_ = acc;
    }
    
    // Variables
    Vector3d pos_, vel_, acc_;
    static const float ROTATE_CONSTANT = 50.0;
};

#endif /* INC_GLMOVABLE_H */