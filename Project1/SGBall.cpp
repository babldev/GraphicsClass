/*
 *  Ball.cpp
 *  Project1
 *
 *  Created by Brady Law on 9/19/10.
 *  Copyright 2010 Brady Law. All rights reserved.
 *
 */

#include "SGBall.h"
#include "GLWindow.h"

#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>

#include <cmath>                        // standard definitions
#include <iostream>

const int SGBall::kVertexCount = 30;
const float SGBall::kWallDampening = 0.6;

void SGBall::Draw() {
	glBegin(GL_POLYGON);
        glColor3f(1.0, 1.0, 1.0);
        
        for (int i = 0; i < 360; i += (360 / kVertexCount)) {
            float deg_in_rad = i * GLWindow::DEGREES_TO_RADIANS;
            
            GLfloat x_pixel = window_->GLValForXPixel(cos(deg_in_rad) * radius_ + pos_.x);
            GLfloat y_pixel = window_->GLValForYPixel(sin(deg_in_rad) * radius_ + pos_.y);
            
            glVertex3f(x_pixel, y_pixel, 0.0f);
        }
    glEnd();
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
}
