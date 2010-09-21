/*
 *  Ball.cpp
 *  Project1
 *
 *  Created by Brady Law on 9/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Ball.h"

#include <cmath>                        // standard definitions

GLfloat COLOR[] = {1.0, 0.0, 0.0};

void Ball::draw() {
	/*
	glColor3fv(COLOR);						// set rectangle color
	glRectf(pos_x_ - 0.5*width_, pos_y_ - 0.5*height_,
			pos_x_ + 0.5*width_, pos_y_ + 0.5*height_);            // draw the rectangle
	*/
	const float DEG2RAD = 3.14159/180;
	
	//glPushMatrix();
	// glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_POLYGON);
	glColor3f(0.0,1.0,0.0); 
	for (int i=0; i < 360; i+=360/60)
	{
		float degInRad = i*DEG2RAD;
		glVertex3f(cos(degInRad)*0.2+pos_x_,sin(degInRad)*0.2+pos_y_,0.0f);
	}
    glEnd();
	// glPopMatrix();
}