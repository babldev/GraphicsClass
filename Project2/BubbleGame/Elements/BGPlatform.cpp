/*
 *  BGPlatform.cpp
 *  Project2
 *
 *  Created by Brady Law on 10/25/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "BGPlatform.h"

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

void BGPlatform::Draw() {
    GLfloat diffuse_color[] = {0.4f, 0.4f, 0.4f, 1.0f};
    
    // set object colors
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffuse_color);
    
    glPushMatrix();
        glTranslatef(pos_.x, pos_.y, pos_.z);
        glScalef(BGPlatform::X_SIZE, BGPlatform::Y_SIZE, BGPlatform::Z_SIZE);
        glutSolidCube(1);
    glPopMatrix();
}

void BGPlatform::Tick(int time_elapsed) {
    GLMovable::Tick(time_elapsed);
}