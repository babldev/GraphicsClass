/*
 *  GLBall.h
 *  Project1
 *
 *  Created by Brady Law on 9/19/10.
 *  Copyright 2010 Brady Law. All rights reserved.
 *
 */

#include "GraphicsLib/GLMovable.h"
#include "GraphicsLib/Geometry/Circle.h"

class SGBall : public GLMovable {
public:
    SGBall(Vector2d pos, float radius) : GLMovable(pos),
            radius_(radius), rot_(0.0), rvel_(0.0) {
        acc_ = Vector2d(0, -2);
        vel_ = Vector2d(40, 40);
    }
    ~SGBall() { }
    
    virtual void Draw();
    virtual void Tick(int time_elapsed);
    Circle Shape();
    
    static const int kVertexCount = 30;
    static const float kWallDampening = 0.6;

    float rot_, rvel_;
protected:
    float radius_;    
    bool alive_; // True if the ball is still on screen
};