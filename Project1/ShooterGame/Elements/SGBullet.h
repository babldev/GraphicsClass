/*
 *  SGBullet.h
 *  Project1
 *
 *  Created by Brady Law on 9/22/10.
 *  Copyright 2010 Brady Law. All rights reserved.
 *
 */

#include "GLMovable.h"
#include "Circle.h"

class SGBullet : public GLMovable {
public:
    SGBullet(Vector2d pos, Vector2d vel) : GLMovable(pos), alive_(true) {
        vel_ = Vector2d::normalize(vel) * kShootSpeed;
    }
    ~SGBullet() { }
    
    virtual void Draw();
    virtual void Tick(int time_elapsed);
    Circle Shape();
    
    static const int kShootSpeed = 80;
    static const int kVertexCount = 10;
    static const int kRadius = 5;

    bool alive_; // True if the ball is still on screen
};