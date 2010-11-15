/*
 *  GLerror.cpp
 *  Project2
 *
 *  Created by Brady Law on 10/26/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "GLerror.h"
#include <iostream>

#ifdef __APPLE__ 
#include <OPENGL/gl.h> 
#include <OPENGL/glu.h> 
#include <GLUT/glut.h> 
#else 
#include <GL/gl.h> 
#include <GL/glu.h> 
#include <GL/glut.h> 
#endif 

using namespace std;

void checkGLerror(const char* checkPoint) {
    GLenum errCode;
    while ((errCode = glGetError()) != GL_NO_ERROR) {
        cerr << "OpenGL Error at "  << checkPoint  << ": "  << gluErrorString(errCode)  << endl;
    }
    cerr.flush();
}