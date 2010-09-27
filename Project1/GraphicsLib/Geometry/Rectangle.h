/*
 *  Rectangle.h
 *  Project1
 *
 *  Created by Brady Law on 9/22/10.
 *  Copyright 2010 Brady Law. All rights reserved.
 *
 */

#ifndef INC_RECTANGLE_H
#define INC_RECTANGLE_H

#include "Vector2d.h"

class Rectangle {
public:
    Rectangle(Vector2d center, Vector2d size) : center_(center), size_(size) { }
    
    Scalar left() const { return center_.x - size_.x; }
    Scalar right() const { return center_.x + size_.x; }
    Scalar bottom() const { return center_.y - size_.y; }
    Scalar top() const { return center_.y + size_.y; }
    
    Vector2d center_, size_;
};

#endif /* INC_RECTANGLE_H */