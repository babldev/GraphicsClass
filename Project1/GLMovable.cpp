/*
 *  GLMovable.cpp
 *  Project1
 *
 *  Created by Brady Law on 9/21/10.
 *  Copyright 2010 Brady Law. All rights reserved.
 *
 */

#include "GLMovable.h"

const double GLMovable::ANIMATION_SPEED = 0.01;

void GLMovable::Tick(int time_elapsed) {
    pos_ += vel_ * time_elapsed * ANIMATION_SPEED;
    vel_ += acc_ * time_elapsed * ANIMATION_SPEED;
}