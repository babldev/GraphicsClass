//-----------------------------------------------------------------------
//  Best viewed with tabs every 4 columns
//-----------------------------------------------------------------------
//  File:           Vector3d.cpp
//  Description:    Vectors and Points in 3d
//  Programmer:     Dave Mount
//  For:            CMSC 427 - Fall 2010
//-----------------------------------------------------------------------

#include "Vector3d.h"

using namespace std;					// make std:: accessible

//----------------------------------------------------------------------
// Constructors and Destructors
//----------------------------------------------------------------------

Vector3d::Vector3d()
  : x(0), y(0), z(0) {}

Vector3d::Vector3d(double _x, double _y, double _z)
  : x(_x), y(_y), z(_z) {}

Vector3d::Vector3d(const Vector3d& copy)
  : x(copy.x), y(copy.y), z(copy.z) {}

//----------------------------------------------------------------------
// Assignment operators
//----------------------------------------------------------------------

Vector3d& Vector3d::operator=(const Vector3d& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

Vector3d& Vector3d::operator+=(const Vector3d& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vector3d& Vector3d::operator-=(const Vector3d& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Vector3d& Vector3d::operator*=(double s)
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

Vector3d& Vector3d::operator/=(double s)
{
	x /= s;
	y /= s;
	z /= s;
	return *this;
}

//----------------------------------------------------------------------
// Arithmetic operators
//----------------------------------------------------------------------

Vector3d operator-(const Vector3d& v)
	{ return Vector3d(-v.x, -v.y, -v.z); }

Vector3d operator+(const Vector3d& v, const Vector3d& w)
	{ return Vector3d(v.x + w.x, v.y + w.y, v.z + w.z); }

Vector3d operator-(const Vector3d& v, const Vector3d& w)
	{ return Vector3d(v.x - w.x, v.y - w.y, v.z - w.z); }

Vector3d operator*(double s, const Vector3d& v)
	{ return Vector3d(s * v.x, s * v.y, s * v.z); }

Vector3d operator*(const Vector3d& v, double s)
	{ return Vector3d(v.x * s, v.y * s, v.z * s); }

Vector3d operator/(const Vector3d& v, double s)
	{ return Vector3d(v.x / s, v.y / s, v.z /s); }

//----------------------------------------------------------------------
// Additional methods
//----------------------------------------------------------------------

double Vector3d::length() const
	{ return sqrt(x*x + y*y + z*z); }

void Vector3d::clamp(double min, double max)
{
	double len = length();
	if (max < GEOM_INF && len > max) {	// too long?
		x *= (max/len);
		y *= (max/len);
		z *= (max/len);
	}
	else if (min > 0 && len < min) {	// too short?
		x *= (min/len);
		y *= (min/len);
		z *= (min/len);
    }
}

void Vector3d::normalize()				// normalize to unit length
{
	double len = length();
	if (len < GEOM_EPS) return;
	x /= len;
	y /= len;
	z /= len;
}

										// functional form 
Vector3d Vector3d::normalize(const Vector3d& v)
{
	double len = v.length();
	return (len < GEOM_EPS ? v : (1/len) * v);
}

//----------------------------------------------------------------------
// Additional utilities
//----------------------------------------------------------------------

double Vector3d::dist(const Vector3d& v, const Vector3d& w)
{
	return sqrt(
		  (v.x - w.x)*(v.x - w.x)
		+ (v.y - w.y)*(v.y - w.y) 
		+ (v.z - w.z)*(v.z - w.z));
}

double Vector3d::dot(const Vector3d& v, const Vector3d& w)
{
	return  (v.x * w.x) + (v.y * w.y) + (v.z * w.z);
}
										// cross product
Vector3d Vector3d::cross(const Vector3d& v, const Vector3d& w)
{
	return Vector3d(
		v.y*w.z - v.z*w.y,
		v.z*w.x - v.x*w.z,
		v.x*w.y - v.y*w.x);
}

//----------------------------------------------------------------------
//	Projection:
//		parProject - parallel part of projection of v onto w
//		orthProject - orthogonal part of projection of v onto w
//
//		Thus: project(v, w) + orthog(v, w) == v
//----------------------------------------------------------------------

Vector3d Vector3d::parProject(const Vector3d& v, const Vector3d& w)
{
	return Vector3d((Vector3d::dot(v, w)*(1/Vector3d::dot(w, w))) * w);
}

Vector3d Vector3d::orthProject(const Vector3d& v, const Vector3d& w)
{
	return v - Vector3d::parProject(v, w);
}


//----------------------------------------------------------------------
// Converts Cartesian to spherical coords
//	from (x,y,z) to (radius, theta, phi) in radians, where theta gives
//	the longitude and phi gives the latitude (start at 0 for north pole)
//----------------------------------------------------------------------

Vector3d Vector3d::cartesianToSpherical(const Vector3d& v)
{
	double lenXY = sqrt(v.x*v.x + v.y*v.y);

	Vector3d spherical;
	spherical.x = v.length();
	spherical.y = atan2(v.y, v.x);	// theta
	spherical.z = -atan2(v.z, lenXY);	// phi

	return spherical;
}

//----------------------------------------------------------------------
// Converts spherical to Cartesian
//	from (rho, theta, phi) in radians to (x,y,z)
//----------------------------------------------------------------------

Vector3d Vector3d::sphericalToCartesian(const Vector3d& v)
{
	Vector3d cartesian;
	cartesian.x = v.x * cos(v.y) * sin(v.z);
	cartesian.y = v.x * sin(v.y) * sin(v.z);
	cartesian.z = v.x * cos(v.z);

	return cartesian;
}

//----------------------------------------------------------------------
//	Common vectors
//----------------------------------------------------------------------
Vector3d Vector3d::zero()  { return Vector3d(0, 0, 0); }
Vector3d Vector3d::yUnit() { return Vector3d(1, 0, 0); }
Vector3d Vector3d::xUnit() { return Vector3d(0, 1, 0); }
Vector3d Vector3d::zUnit() { return Vector3d(0, 0, 1); }

//----------------------------------------------------------------------
//	Output operator
//----------------------------------------------------------------------
ostream& operator<<(ostream& out, const Vector3d& v)
	{ return out << "[" << v.x << ", " << v.y << ", " << v.z << "]"; }
