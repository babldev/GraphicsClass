//----------------------------------------------------------------------
//	Best if viewed with tabs set every 4 columns.
//----------------------------------------------------------------------
//	File:			Vector2d.cpp
//	Description:	2-dimensional point
//	Programmer:		Dave Mount
//	For:			CMSC 427 - Computer Graphics
//	Date:			Fall 2010
//----------------------------------------------------------------------

#include "Vector2d.h"

											// constructors
Vector2d::Vector2d() : x(0), y(0) { }

Vector2d::Vector2d(Scalar _x, Scalar _y) : x(_x), y(_y) { }

Vector2d::Vector2d(const Vector2d& v) : x(v.x), y(v.y) { }

											// assignment ops
Vector2d& Vector2d::operator=(const Vector2d& v) 
	{ x = v.x; y = v.y; return *this; }

Vector2d& Vector2d::operator+=(const Vector2d& v)
	{ x += v.x; y += v.y; return *this; }

Vector2d& Vector2d::operator-=(const Vector2d& v) 
	{ x -= v.x; y -= v.y; return *this; }

Vector2d& Vector2d::operator*=(Scalar s) 
	{ x *= s; y *= s; return *this; }

Vector2d& Vector2d::operator/=(Scalar s) 
	{ x /= s; y /= s; return *this; }
											// arithmetic ops
Vector2d Vector2d::operator+(const Vector2d& v) const 
	{ return Vector2d(x + v.x, y + v.y); }

Vector2d Vector2d::operator-(const Vector2d& v) const 
	{ return Vector2d(x - v.x, y -v.y); }

Vector2d Vector2d::operator*(Scalar s) const
	{ return Vector2d(s*x, s*y); }

Vector2d Vector2d::operator/(Scalar s) const
	{ return Vector2d(x/s, y/s); }

Vector2d Vector2d::operator-() const
	{ return Vector2d(-x, -y); }

Scalar Vector2d::length() const
	{ return sqrt(x*x + y*y); }

void Vector2d::normalize() {				// normalize to unit length
	Scalar w = length(); 
	if (w == 0) { x = 1; y = 0; }			// too short!
	else { x /= w; y /= w; }				// scale by 1/length
}

Vector2d Vector2d::normalize(const Vector2d& v) {
	Vector2d tmp = v; 
	tmp.normalize(); 
	return tmp;
}
											// dot product
Scalar Vector2d::dot(const Vector2d& v, const Vector2d& w)
	{ return v.x * w.x + v.y * w.y; }

											// project v parallel to w
Vector2d Vector2d::parProject(const Vector2d& v, const Vector2d& w)
	{ return w * (dot(v,w) / dot(w,w)); }

											// project v orthogonal to w
Vector2d Vector2d::orthProject(const Vector2d& v, const Vector2d& w)
	{ return v - parProject(v, w); } 

											// output operator
std::ostream& operator<<(std::ostream& out, const Vector2d& p) {
	out << "(" << p.x << ", " << p.y << ")";
	return out;
}
