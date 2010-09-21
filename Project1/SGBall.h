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
        acc_ = Vector2d(0, -1);
    }
    ~SGBall() { }
	
	void DrawInWindow(GLWindow* window);
    
    static const float kDeg2Rad;
    static const int kVertexCount;
    
protected:
	float radius_;
};