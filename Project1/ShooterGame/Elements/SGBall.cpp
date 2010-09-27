/*
 *  Ball.cpp
 *  Project1
 *
 *  Created by Brady Law on 9/19/10.
 *  Copyright 2010 Brady Law. All rights reserved.
 *
 */

#include "ShooterGame/Elements/SGBall.h"

#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include "GraphicsLib/GLWindow.h"

#include <cmath>                        // standard definitions
#include <iostream>

void SGBall::Draw() {
    glPushMatrix();
        glTranslatef(pos_.x, pos_.y, 0);
        glRotatef(rot_, 0, 0, 1);
    
        // Create ball
        glBegin(GL_POLYGON);
            glColor3f(1.0, 1.0, 1.0);
            
            for (int i = 0; i < 360; i += (360 / kVertexCount)) {
                float deg_in_rad = i * GLWindow::DEGREES_TO_RADIANS;
                
                GLfloat x_pixel = cos(deg_in_rad) * radius_;
                GLfloat y_pixel = sin(deg_in_rad) * radius_;
                
                glVertex3f(x_pixel, y_pixel, 0.0f);
            }
        glEnd();
        
        // Create spin markers
        const float SPIN_MARK_WIDTH = 0.08;
        const float SPIN_MARK_HEIGHT = 1.0;
        glColor3f(0.0, 0.0, 0.0);
        glRectf(-1*SPIN_MARK_WIDTH*radius_,
                -1*SPIN_MARK_HEIGHT*radius_,
                SPIN_MARK_WIDTH*radius_,
                SPIN_MARK_HEIGHT*radius_);

    
    glPopMatrix();
}

void SGBall::Tick(int time_elapsed) {
    GLMovable::Tick(time_elapsed);
    
    if (pos_.x + radius_ > window_->width()) {
        // TODO: Is this the right way to do it?
        pos_.x = window_->width() - radius_;
        vel_.x *= -1 * kWallDampening;
    } else if (pos_.x - radius_ < 0) {
        pos_.x = radius_;
        vel_.x *= -1 * kWallDampening;
    }
    
    if (pos_.y + radius_ > window_->height()) {
        pos_.y = window_->height() - radius_;
        vel_.y *= -1 * kWallDampening;
    } else if (pos_.y - radius_ < 0) {
        pos_.y = radius_;
        vel_.y *= -1 * kWallDampening;
    }
    
    // Rotate update (in degrees)
    rot_ += fmod(rvel_ * time_elapsed * GLMovable::ROTATE_CONSTANT * GLMovable::ANIMATION_SPEED,
                 360);
}

Circle SGBall::Shape() {
    return Circle(pos_, radius_);
}

