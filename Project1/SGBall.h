/*
 *  GLBall.h
 *  Project1
 *
 *  Created by Brady Law on 9/19/10.
 *  Copyright 2010 Brady Law. All rights reserved.
 *
 */

#include "GLMovable.h"

class SGBall : public GLMovable {
public:
	SGBall(Vector2d pos, float radius) : GLMovable(pos),
            radius_(radius) {
        acc_ = Vector2d(0, -2);
        vel_ = Vector2d(40, 40);
    }
    ~SGBall() { }
	
	virtual void Draw();
    virtual void Tick(int time_elapsed);
    
    static const int kVertexCount;
    static const float kWallDampening;
protected:
	float radius_;
    bool alive_; // True if the ball is still on screen
};