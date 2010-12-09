//-----------------------------------------------------------------------
//  Best viewed with tabs every 4 columns
//-----------------------------------------------------------------------
//  File:           utilities.h
//  Description:    Some utility math functions
//  Programmer:     Dave Mount
//  For:            CMSC 427 - Fall 2010
//-----------------------------------------------------------------------

#ifndef UTILITIES_H
#define UTILITIES_H

#include <cmath>						// math definitions
#include <string>						// C++ strings
#include <iostream>						// C++ I/O
#include <sys/timeb.h>					// for timer
#include <GL/glut.h>					// OpenGL

#ifndef M_PI							// define PI and PI/2
#define M_PI	3.14159265358979323846
#define M_PI_2	1.57079632679489661923
#endif

// ---------------------------------------------------------------  
// Utility functions for random number generation
// ---------------------------------------------------------------
inline double unifRand(double low, double high)
    { return low + (high-low)*double(rand())/double(RAND_MAX); }

inline bool unifBool()
    { return unifRand(0, 1) < 0.5; }    // this is true 50% of the time

// ---------------------------------------------------------------  
// Clamps val to a value between min and max
// ---------------------------------------------------------------
double clamp(double val, double min, double max);

// ---------------------------------------------------------------  
// Convertion to/from radians and degrees
// ---------------------------------------------------------------
inline double deg2rad(double deg)
{
	return deg* (M_PI/180.0);
}

inline double rad2deg(double rad)
{
	return rad* 180.0/M_PI ;
}

//----------------------------------------------------------------------
//  checkGLerror - OpenGL error handler
//      OpenGL does not generate error messages or exceptions.  In order
//      to check for errors, insert this call at strategic points within
//      the program.  The checkPoint argument is a label for where the
//      error checking was invoked from. Example:
//
//              checkGLerror("After texture-map setup")
//----------------------------------------------------------------------
void checkGLerror(const std::string& checkPoint);

//----------------------------------------------------------------------
//  error - error handler
//----------------------------------------------------------------------
void error(const std::string& msg, bool fatal);

//----------------------------------------------------------------------
//  version control
//----------------------------------------------------------------------
int getVersion();

void setVersion(int v);

//----------------------------------------------------------------------
//  get millisecond time counts
//----------------------------------------------------------------------
int getMilliCount();
int getMilliSpan(int nTimeStart);
double getTimeStep();

#endif
