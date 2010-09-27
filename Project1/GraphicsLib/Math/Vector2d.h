//----------------------------------------------------------------------
//    Best if viewed with tabs set every 4 columns.
//----------------------------------------------------------------------
//    File:            Vector2d.h
//    Description:    2-dimensional vectors and points
//    Programmer:        Dave Mount
//    For:            CMSC 427 - Computer Graphics
//    Date:            Fall 2010
//----------------------------------------------------------------------

#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <cstdlib>                        // C standard definitions
#include <cmath>                        // C math definitions
#include <iostream>                        // C++ I/O

//----------------------------------------------------------------------
//    Vector2d - 2-dimensional point object
//
//    This object encapsulates both 2-d point and vector methods. There
//    is no essential difference between Vector2d and Point2d. We create
//    two types for easier readability.
//
//    Beware: Scalar * vector multiplication must be written as v * s, not
//    s * v.
//
//    Summary of methods: (x,y,s are scalars and v and w are vectors)
//        Vector2d()            create vector (0,0)
//        Vector2d(x,y)        create vector (x,y)
//        Vector2d(v)            create a copy of vector v
//        w = v                vector assignment
//        w += v                w = w + v
//        w -= v                w = w - v
//        w *= s                w = w * s
//        w /= s                w = w / s (no error check if s = 0)
//        w + v                returns w + v
//        w - v                returns w - v
//        w * s                returns w * s
//        w / s                returns w / s (no error check if s = 0)
//        w.length()            returns w's length
//        w.normalize()        normalize w's length to unity
//        Vector2d::normalize(w)
//                            returns unit vector in w's direction
//                            (w is not modified)
//        Vector2d::dot(v,w)    returns (v . w)
//        Vector2d::parProject(v,w)
//                            returns parallel projection of v to w
//        Vector2d::orthProject(v,w)
//                            returns perpendicular projection of v to w
//        cout << w            output w
//
//    Point2d is an alias for Vector2d, so from C++'s perspective there is
//    no difference. However, as an aid to readability, use Point2d for
//    point objects and Vector2d for vector objects. E.g.,
//
//    Point2d position;
//    Vector2d velocity;
//
//----------------------------------------------------------------------

typedef double Scalar;                    // real scalar type

class Vector2d {
public:
    Vector2d();                            // constructors
    Vector2d(Scalar x, Scalar y);
    Vector2d(const Vector2d& v);
                                        // assignment operators
    Vector2d& operator=(const Vector2d& v);
    Vector2d& operator+=(const Vector2d& v);
    Vector2d& operator*=(Scalar s);
    Vector2d& operator/=(Scalar s);
    Vector2d& operator-=(const Vector2d& v);
                                        // vector operators
    Vector2d operator+(const Vector2d& v) const;
    Vector2d operator-(const Vector2d& v) const;
    Vector2d operator*(Scalar s) const;
    Vector2d operator/(Scalar s) const;
    Vector2d operator-() const;
                                        // other vector operations
    Scalar length() const;
    void normalize();                    // normalize to unit length
    static Vector2d normalize(const Vector2d& v);
    static Scalar dot(const Vector2d& v, const Vector2d& w);
                                        // parallel and orthogonal projection
    static Vector2d parProject(const Vector2d& v, const Vector2d& w);
    static Vector2d orthProject(const Vector2d& v, const Vector2d& w);
public:
    Scalar x, y;                // variables made public for ease of use
};

                                        // output operator
std::ostream& operator<<(std::ostream& out, const Vector2d& v);

typedef Vector2d Point2d;                // Point2d is alias for Vector2d

#endif
