/*
 *  Circle.h
 *  Project1
 *
 *  Created by Brady Law on 9/22/10.
 *  Copyright 2010 Brady Law. All rights reserved.
 *
 */

#ifndef INC_CIRCLE_H
#define INC_CIRCLE_H

#include "GraphicsLib/Math/Vector2d.h"

class Circle {
public:
    Circle(Vector2d center, Scalar radius) : center_(center), radius_(radius) { }
    Vector2d center_;
    Scalar radius_;
};

#endif /* INC_CIRCLE_H */