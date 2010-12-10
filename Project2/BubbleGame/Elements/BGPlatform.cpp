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
    glDisable(GL_DEPTH_TEST);
    glColorMask(0, 0, 0, 0);
    glStencilFunc(GL_ALWAYS, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glEnable(GL_STENCIL_TEST);
        DrawObject();
    glDisable(GL_STENCIL_TEST);
    glEnable(GL_DEPTH_TEST);
    glColorMask(1, 1, 1, 1);
    DrawObject();
}

void BGPlatform::DrawObject() {
    GLfloat tall_diffuse_color[] = {0.4f, 0.4f, 0.4f, 1.0f};
    GLfloat short_diffuse_color[] = {0.6f, 0.6f, 0.4f, 1.0f};
    
    // set object colors
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE,
                 (tall_) ? tall_diffuse_color : short_diffuse_color);
    
    glPushMatrix();
        glTranslatef(pos_.x, pos_.y, pos_.z);
        glScalef(BGPlatform::X_SIZE, BGPlatform::Y_SIZE, height_);
        glutSolidCube(1.0f);
    glPopMatrix();
}

void BGPlatform::Tick(int time_elapsed) {
    GLMovable::Tick(time_elapsed);
}