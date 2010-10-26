/*
 *  BGBall.cpp
 *  Project2
 *
 *  Created by Brady Law on 10/25/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "BGBall.h"

#include "GraphicsLib/GLWindow.h"

#ifdef __APPLE__
#include <OPENGL/gl.h>
#include <OPENGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <cmath>                        // standard definitions
#include <iostream>

void BGBall::Draw() {
    GLfloat diffuse_color[] = {1.0f, 0.0f, 1.0f, 1.0f};
    GLfloat specular_color[] = {1.0f, 1.0f, 1.0f, 1.0f};
    
    // set object colors
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffuse_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_color);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50);
    
    glPushMatrix();
        glTranslatef(pos_.x, pos_.y, pos_.z);
    
        // Create ball
        // glColor4f(0.0f,1.0f,0.0f,0.6f);
        glutSolidSphere(BGBall::RADIUS, BGBall::GLUT_SLICES, BGBall::GLUT_SLICES);
    glPopMatrix();
}

void BGBall::Tick(int time_elapsed) {
    GLMovable::Tick(time_elapsed);
}