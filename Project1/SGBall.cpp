/*
 *  Ball.cpp
 *  Project1
 *
 *  Created by Brady Law on 9/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "SGBall.h"

#include <cmath>                        // standard definitions

GLfloat COLOR[] = {1.0, 0.0, 0.0};

void SGBall::DrawInWindow(GLWindow* window) {
	const float kDeg2Rad = 3.14159/180;
    const int kVertexCount = 60;

	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);
    
	for (int i = 0; i < 360; i += (360 / kVertexCount)) {
		float deg_in_rad = i * kDeg2Rad;
		glVertex3f(cos(deg_in_rad) * radius_ + pos_x_, sin(deg_in_rad) * radius_ + pos_y_, 0.0f);
	}
    
    glEnd();
}