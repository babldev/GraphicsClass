/*
 *  Ball.h
 *  Project1
 *
 *  Created by Brady Law on 9/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Drawable.h"

#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>

class Ball: public Drawable {
public:
	Ball(float x, float y, float width, float height) : Drawable(x, y),
		width_(width), height_(height)
	{ }
	
	virtual void draw();
protected:
	float width_;
	float height_;
};
