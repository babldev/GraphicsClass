/*
 *  GLBall.h
 *  Project1
 *
 *  Created by Brady Law on 9/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>

#include "GLMovable.h"

class SGBall: public GLMovable {
public:
	SGBall(float x, float y, float width) : GLMovable(x, y),
            width_(width) { }
	
	virtual void DrawInWindow(GLWindow* window);

protected:
	float width_;
};