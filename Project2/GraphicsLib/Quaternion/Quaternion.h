//-----------------------------------------------------------------------
//  Best viewed with tabs every 4 columns
//-----------------------------------------------------------------------
//  File:           Quaternion.h
//  Description:    Quaternion object
//  Programmer:     Dave Mount
//  For:            CMSC 427 - Fall 2010
//-----------------------------------------------------------------------

#ifndef QUATERNION_H
#define QUATERNION_H

#include "GraphicsLib/Math/Vector3d.h"

//-----------------------------------------------------------------------
//	SimpleMatrix - a very simple matrix object
//
//	This is matrix affine transformations in 3-space. That is, it is
//	a 4x4 matrix. The matrix storage approach is intentionally designed
//	to match OpenGL's weird column-major order convention, and thus the
//	16-element matrix stores elements in order so that the [i,j] element
//	is located at index [4*i + j] This makes it possible to pass the
//	matrix to OpenGL matrix procedures, such as glLoadMatrix and
//	glMultMatrix.
//
//	We do not explicitly define an assignment operator or a copy
//	constructor, but the default for C++ is to do a byte-by-byte copy,
//	which works for us. Thus, assigning one object of type SimpleMatrix
//	to another achieves the desired result.
//-----------------------------------------------------------------------

class SimpleMatrix {
private:
	double m[16];						// 4x4 column-major matrix
public:
	SimpleMatrix(); 					// constructor
	double& at(int i, int j)			// index [i,j] (read/write)
	  { return m[i*4 + j]; }
	const double& at(int i, int j) const // index [i,j] (read only)
	  { return m[i*4 + j]; }
	double* oglMat() { return m; }		// OpenGL matrix pointer
};

//-----------------------------------------------------------------------
//	Quaternion
//
//	The rotation by theta degrees about axis u is represented by the
//	quaternion (s, v) where: s = sin theta/2 and v = (cos theta/2)*u.
//
//	The constructor is given the angle in degrees.
//
//	There are two ways to convert a quaternion to a form that can be
//	used by OpenGL. First, apply getAngle and getAxis, and apply them
//	using glRotatef (after converting the angle to degrees). The other
//	is to apply getRotationMatrix and use it to apply glMultMatrixd.
//
//	Public Methods:
//	---------------
//	(p and q are Quaterions, s is a Scalar, and v is a Vector3d)
//
//	Quaternion()				Create a unit quaternion (0 rotation)
//	Quaternion(angle, axis)		Create a quaternion for the given angle
//								and axis of rotation.
//		Assignment ops:
//		---------------
//		p = q; p += q; p-= q;	Assign q to p (with addition/subtraction)
//		p *= s					p = s*p, for a scalar s.
//
//		Arithemetic ops:
//		---------------
//		q + p; q - p; q * p		Addition, subtraction, and multiplication
//		q * s; s * q			Scalar multiplication
//
//	getAxis()                   Get axis of rotation (as Vector3d)
//	getAngle()					Get angle of rotation (in radians)
//	getRotationMatrix()			Get equivalent rotation matrix
//	normalize()					Normalize to unit quaternion
//	setSAndV(s, v)				Set the scalar and vector parts
//	setAngleAndAxis(angle, axis) Set the rotation angle and axis
//	inverse()                  	Return quaternion's inverse
//	rotate(u)					Return application quaternion rotation to u
//	static createFromSAndV(s, v) Create quaternion from scalar and vector
//	static derivative(w, q)		Return derivative for quaternion q
//								relative angular velocity w.
//-----------------------------------------------------------------------

class Quaternion {
public:
	double  s;							// scalar part
	Vector3d v;							// vector part
public:
										// constructors and destructor
	Quaternion();
	Quaternion(double angle, const Vector3d& axis);
										// assignment operators
	Quaternion& operator=(const Quaternion& q);
	Quaternion& operator+= (const Quaternion& q);
	Quaternion& operator-=(const Quaternion& q);
	Quaternion& operator*=(double scale);


	Vector3d getAxis() const;			// getters
	double getAngle() const;			// angle returned in degrees
	SimpleMatrix getRotationMatrix() const; // get OpenGL rotation matrix

										// arithmetic operators
	void normalize();
	void setSAndV(double ss, const Vector3d& vv);
	void setAngleAndAxis(double angle, const Vector3d& axis);
	Quaternion inverse() const;
	Quaternion operator+(const Quaternion& quat) const;
	Quaternion operator-(const Quaternion& quat) const;
	Quaternion operator*(const Quaternion& quat) const;
	Vector3d rotate(const Vector3d& u) const;
	friend Quaternion operator*(const Quaternion& quat, double scalar);
	friend Quaternion operator*(double scalar, const Quaternion& quat);

										// create from s and v
	static Quaternion createFromSAndV(double ss, const Vector3d& vv);

										// derivative wrt angular veloc w
	static Quaternion derivative(const Vector3d& w, const Quaternion& q);
};

#endif
