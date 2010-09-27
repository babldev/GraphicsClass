/*
 *  SGBullet.cpp
 *  Project1
 *
 *  Created by Brady Law on 9/22/10.
 *  Copyright 2010 Brady Law. All rights reserved.
 *
 */

#include "ShooterGame/Elements/SGBullet.h"
#include "GraphicsLib/GLWindow.h"
#include "GraphicsLib/Geometry/Geometry.h"

#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>

#include <cmath>                        // standard definitions
#include <iostream>

void SGBullet::Draw() {
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 0.0);
    
    for (int i = 0; i < 360; i += (360 / kVertexCount)) {
        float deg_in_rad = i * GLWindow::DEGREES_TO_RADIANS;
        
        GLfloat x_pixel = cos(deg_in_rad) * kRadius + pos_.x;
        GLfloat y_pixel = sin(deg_in_rad) * kRadius + pos_.y;
        
        glVertex3f(x_pixel, y_pixel, 0.0f);
    }
    glEnd();
}

void SGBullet::Tick(int time_elapsed) {
    if (alive_) {
        GLMovable::Tick(time_elapsed);
        Circle bullet_shape = Shape();
        Rectangle window_shape = window_->Shape();
        alive_ = Geometry::RectangleIntersectsCircle(&window_shape, &bullet_shape);
        if (!alive_)
            cout << "DEAD!" << endl;
    }
}

Circle SGBullet::Shape() {
    return Circle(pos_, kRadius);
}