/*
 *  GLBall.h
 *  Project1
 *
 *  Created by Brady Law on 9/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "GLMovable.h"

class SGBall : public GLMovable {
public:
	SGBall(float x, float y, float radius) : GLMovable(x, y),
            radius_(radius) { }
    ~SGBall() { }
	
	void DrawInWindow(GLWindow* window);
    
    static const float kDeg2Rad;
    static const int kVertexCount;
    
protected:
	float radius_;
};