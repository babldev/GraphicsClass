/*
 *  Geometry.h
 *  Project1
 *
 *  Created by Brady Law on 9/22/10.
 *  Copyright 2010 Brady Law. All rights reserved.
 *
 */

#ifndef INC_GEOMETRY_H
#define INC_GEOMETRY_H

#include "Rectangle.h"
#include "Circle.h"
#include "Vector2d.h"

class Geometry {
public:
    static bool RectangleIntersectsRectangle(const Rectangle* r1, const Rectangle* r2);
    static bool RectangleIntersectsCircle(const Rectangle* r, const Circle* c);
    static bool RectangleContainsPoint(const Rectangle* r, const Vector2d* p);
    static bool CircleIntersectsCircle(const Circle* c1, const Circle* c2);
    static bool CircleContainsPoint(const Circle* c, const Vector2d* p);
};

#endif /* INC_GEOMETRY_H */