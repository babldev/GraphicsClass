/*
 *  Geometry.cpp
 *  Project1
 *
 *  Created by Brady Law on 9/22/10.
 *  Copyright 2010 Brady Law. All rights reserved.
 *
 */

#include "Geometry.h"

// Simple line comparison
bool Geometry::RectangleIntersectsRectangle(const Rectangle* r1, const Rectangle* r2) {
    return !(r1->left() > r2->right() || r1->right() < r2->left() ||
            r1->top() < r2->bottom() || r1->bottom() > r2->top());
}

// If the circle contains any of the rectangle verticies
bool Geometry::RectangleIntersectsCircle(const Rectangle* r, const Circle* c) {
    // TODO: This is a hack and is not correct
    Rectangle circle_container = Rectangle(c->center_, Vector2d(c->radius_, c->radius_));
    return RectangleIntersectsRectangle(r, &circle_container);
}

// Point is within x and y bounds
bool Geometry::RectangleContainsPoint(const Rectangle* r, const Vector2d* p) {
    return (p->x >= r->left() && p->x <= r->right() && p->y >= r->bottom() && p->y <= r->top());
}

bool Geometry::CircleIntersectsCircle(const Circle* c1, const Circle* c2) {
    return (c1->center_ - c2->center_).length() < (c1->radius_ + c2->radius_);
}

// Distance between point and center is less than radius
bool Geometry::CircleContainsPoint(const Circle* c, const Vector2d* p) {
    return ((c->center_ - *p).length() < c->radius_);
}