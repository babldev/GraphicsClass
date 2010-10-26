/*
 *  GLMovable.cpp
 *  Project1
 *
 *  Created by Brady Law on 9/21/10.
 *  Copyright 2010 Brady Law. All rights reserved.
 *
 */

#include "GraphicsLib/GLMovable.h"
#include "GLWindow.h"

void GLMovable::Tick(int time_elapsed) {
    pos_ += vel_ * time_elapsed * window_->animation_speed();
    vel_ += acc_ * time_elapsed * window_->animation_speed();
}