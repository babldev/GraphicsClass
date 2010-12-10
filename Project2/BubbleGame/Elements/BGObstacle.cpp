/*
 *  BGObstacle.cpp
 *  Project2
 *
 *  Created by Brady Law on 10/25/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "BGObstacle.h"

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

void BGObstacle::Draw() {
    GLfloat diffuse_color[] = {1.0f, 1.0f, 0.0f, 1.0f};
    GLfloat specular_color[] = {1.0f, 1.0f, 1.0f, 1.0f};
    const GLdouble shadow_proj_matrix[] = {
        1.0f, 0, 0, 0,
        0, 1.0f, 0, 0,
        1.0f, 1.0f, 0, 0,
        0, 0, 25.1f, 1.0f};
    
    glDisable(GL_LIGHTING);
    glPushMatrix();
        glColor4f(0.0f, 0.0f, 0.0f, 0.3f);
        glMultMatrixd(shadow_proj_matrix);
        // glMatrixMode(GL_MODELVIEW);
        DrawObject();
        // glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glEnable(GL_LIGHTING);
    glColor4f(1, 1, 1, 1.0f);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffuse_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_color);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50);
    
    DrawObject();
}

void BGObstacle::DrawObject() {
    glPushMatrix();
        glTranslatef(pos_.x, pos_.y, pos_.z);
        glutSolidSphere(BGObstacle::RADIUS, BGObstacle::GLUT_SLICES, BGObstacle::GLUT_SLICES);
    glPopMatrix();
}

void BGObstacle::Tick(int time_elapsed) {
    Vector3d original_pos = pos_;
    
    GLMovable::Tick(time_elapsed);
    vel_ /= BGObstacle::AIR_RESISTANCE;
    /*
    // Are we colliding with the top?
    float support_platform_z = support_platform_->pos_.z + BGPlatform::Z_SIZE*0.5;
    if ((original_pos.z - BGObstacle::RADIUS) >= support_platform_z &&
        (pos_.z - BGObstacle::RADIUS) < support_platform_z) {
        if (pos_.x < support_platform_->pos_.x + BGPlatform::X_SIZE*0.5f &&
            pos_.x > support_platform_->pos_.x - BGPlatform::X_SIZE*0.5f &&
            pos_.y < support_platform_->pos_.y + BGPlatform::Y_SIZE*0.5f &&
            pos_.y > support_platform_->pos_.y - BGPlatform::Y_SIZE*0.5f) {
            vel_.z *= -1 * BGObstacle::COLLISION_DAMP;
            pos_.z = (support_platform_->pos_.z + BGPlatform::Z_SIZE*0.5 + BGObstacle::RADIUS);
        }
    }
     */
}