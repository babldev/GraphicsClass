/*
 *  BGBall.h
 *  Project2
 *
 *  Created by Brady Law on 10/25/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "GraphicsLib/GLMovable.h"

class BGBall : public GLMovable {
public:
    BGBall(Vector3d pos) : GLMovable(pos) {
        acc_ = Vector3d(0.1f, 0.1f, 0.1f);
    }
    ~BGBall() { }
    
    virtual void Draw();
    virtual void Tick(int time_elapsed);
    
    static const int GLUT_SLICES = 25;
    static const float RADIUS = 50.0f;
protected:
    bool alive_; // True if the ball is still on screen
};