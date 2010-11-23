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
    GLfloat diffuse_color[] = {1.0f, 0.0f, 1.0f, 0.5f};
    GLfloat specular_color[] = {1.0f, 1.0f, 1.0f, 0.5f};
    
    // (1) Draw Sphere
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
    
    /*
    // (2) Add Shadow
   
    glPushMatrix();
    glTranslatef(pos_.x, pos_.y, support_platform_->pos_.z+BGPlatform::Z_SIZE-BGBall::RADIUS+400.0f);
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    
    for (int i = 0; i < 360; i += (360 / BGBall::GLUT_SLICES)) {
        float deg_in_rad = i * GLWindow::DEGREES_TO_RADIANS;
        
        GLfloat x_pixel = cos(deg_in_rad) * BGBall::RADIUS;
        GLfloat y_pixel = sin(deg_in_rad) * BGBall::RADIUS;
        
        glVertex3f(x_pixel, y_pixel, 0.0f);
    }
    glEnd();
    glPopMatrix();
    glEnable(GL_LIGHTING);
     */
}

void BGBall::Tick(int time_elapsed) {
    Vector3d original_pos = pos_;
    
    GLMovable::Tick(time_elapsed);
    vel_ /= BGBall::AIR_RESISTANCE;
    
    // TODO - This collision algorithm needs serious work
    // Are we colliding with the top?
    if ((original_pos.z - BGBall::RADIUS) > (support_platform_->pos_.z + BGPlatform::Z_SIZE*0.5) &&
            (pos_.z - BGBall::RADIUS) < (support_platform_->pos_.z + BGPlatform::Z_SIZE*0.5)) {
        if (pos_.x < support_platform_->pos_.x + BGPlatform::X_SIZE*0.5f &&
            pos_.x > support_platform_->pos_.x - BGPlatform::X_SIZE*0.5f &&
            pos_.y < support_platform_->pos_.y + BGPlatform::Y_SIZE*0.5f &&
            pos_.y > support_platform_->pos_.y - BGPlatform::Y_SIZE*0.5f) {
        vel_.z *= -1 * BGBall::COLLISION_DAMP;
        pos_.z = (support_platform_->pos_.z + BGPlatform::Z_SIZE*0.5 + BGBall::RADIUS);
        }
    }
}

void BGBall::Poke(Vector3d direction) {
    direction.normalize();
    vel_ += direction * BGBall::POKE_VEL_CHANGE;
}