/*
 *  Ball.cpp
 *  Project1
 *
 *  Created by Brady Law on 9/19/10.
 *  Copyright 2010 Brady Law. All rights reserved.
 *
 */

#include "SGBall.h"

#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>

#include <cmath>                        // standard definitions
#include <iostream>

const float SGBall::kDeg2Rad = 3.14159/180;
const int SGBall::kVertexCount = 60;

void SGBall::DrawInWindow(GLWindow* window) {
    cout << "Drawing ball..." << endl;
    
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
    
	for (int i = 0; i < 360; i += (360 / kVertexCount)) {
		float deg_in_rad = i * kDeg2Rad;
		glVertex3f(cos(deg_in_rad) * radius_ + x_, sin(deg_in_rad) * radius_ + y_, 0.0f);
	}
    
    glEnd();
}
