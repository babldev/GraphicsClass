//-----------------------------------------------------------------------
//  Best viewed with tabs every 4 columns
//-----------------------------------------------------------------------
//  File:           Vector3d.h
//  Description:    Vectors and Points in 3d
//  Programmer:     Dave Mount
//  For:            CMSC 427 - Fall 2010
//-----------------------------------------------------------------------

#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <cstdlib>						// standard C definitions
#include <cmath>						// math includes
#include <iostream>						// C++ I/O

//-----------------------------------------------------------------------
// Useful constants
//-----------------------------------------------------------------------
const double GEOM_EPS = 1.0E-6;			// small number for float compare
const double GEOM_INF = 1.0E+30;		// a big number

//-----------------------------------------------------------------------
//	Vector3d - 3-dimensional points and vectors
//
//	This class represents a 3d vector with overloaded operators to
//	perform simple arithmetic on the vector. The class fields are
//	public for efficiency and ease of use. 
//
//	For simplicity, rather than define a separate Point3d class, we
//	simply alias Point3d to Vector3d.
//
//	This class encapsulates both 3-d point and vector methods, with
//	overloaded operators for simple arithmetic. The class fields have
//	been made public for ease of access.
//
//	Summary of methods: (x,y,z,s are scalars and v and w are vectors)
//		Vector3d()			create vector (0,0,0)
//		Vector3d(x,y,z)		create vector (x,y,z)
//		Vector3d(v)			create a copy of vector v
//		w = v				vector assignment
//		w += v				w = w + v
//		w -= v				w = w - v
//		w *= s				w = w * s
//		w /= s				w = w / s (no error check if s = 0)
//		w + v				returns w + v
//		w - v				returns w - v
//		s * w				returns s * w
//		w * s				returns w * s
//		w / s				returns w / s (no error check if s = 0)
//		w.length()			returns w's length
//		w.clamp(min, max)	clamp coords to fit in interval [min,max]
//		w.normalize()		normalize w's length to unity
//		Vector3d::normalize(w) returns unit vector in w's direction
//							(w is not modified)
//		Vector3d::dist(v,w)	returns distance from v to w
//		Vector3d::dot(v,w)	returns (v . w)
//		Vector3d::cross(v,w) returns cross product (v x w)
//		Vector3d::parProject(v,w) returns parallel part of projection
//							of v onto w
//		Vector3d::orthProject(v,w) returns orthogonal part of
//							projection of v onto w
//		Vector3d::cartesianToSpherical(v) return conversion of v from
//							Cartesian to Spherical coords
//		Vector3d::sphericalToCartesian(v) return conversion of v from
//							Spherical to Cartesian coords
//		Vector3d::zero()	return vector (0,0,0)
//		Vector3d::xUnit()	return vector (1,0,0)
//		Vector3d::yUnit()	return vector (0,1,0)
//		Vector3d::zUnit()	return vector (0,0,1)
//		cout << w			output w
//
//	Point3d is an alias for Vector3d, so from C++'s perspective there is
//	no difference. However, as an aid to readability, use Point3d for
//	point objects and Vector3d for vector objects. E.g.,
//
//	Point3d position;
//	Vector3d velocity;
//----------------------------------------------------------------------

class Vector3d;
typedef Vector3d Point3d;				// Point is alias for Vector

class Vector3d {
public:									// public members for easy access
	double x, y, z;						// coordinates
public:
	Vector3d();							// constructors and destructors
	Vector3d(double x, double y, double z);
	Vector3d(const Vector3d& v);
										// assignment operators
	Vector3d& operator=(const Vector3d& v);
	Vector3d& operator+= (const Vector3d& v);
	Vector3d& operator-=(const Vector3d& v);
	Vector3d& operator*=(double s);
	Vector3d& operator/=(double s);

	double length() const;				// additional methods
	void clamp(double min, double max);
	void normalize();
	static Vector3d normalize(const Vector3d& v);

										// additional utilities
	static double dist(const Vector3d& v, const Vector3d& w);
	static double dot(const Vector3d& v, const Vector3d& w);
    static double angle(const Vector3d& v, const Vector3d& w);
	static Vector3d cross(const Vector3d& v, const Vector3d& w);
	static Vector3d parProject(const Vector3d& v, const Vector3d& w);
	static Vector3d orthProject(const Vector3d& v, const Vector3d& w);
	static Vector3d cartesianToSpherical(const Vector3d& v);
	static Vector3d sphericalToCartesian(const Vector3d& v);

	static Vector3d zero();				// commonly used vectors
	static Vector3d zUnit();
	static Vector3d yUnit();
	static Vector3d xUnit();

										// arithmetic operators
	friend Vector3d operator-(const Vector3d& v);
	friend Vector3d operator+(const Vector3d& v, const Vector3d& w);
	friend Vector3d operator-(const Vector3d& v, const Vector3d& w);
	friend Vector3d operator*(double s, const Vector3d& v);
	friend Vector3d operator*(const Vector3d& v, double s);
	friend Vector3d operator/(const Vector3d& v, double s);
};

//----------------------------------------------------------------------
//	Output operator
//----------------------------------------------------------------------

std::ostream& operator<<(std::ostream& out, const Vector3d& v);

#endif
