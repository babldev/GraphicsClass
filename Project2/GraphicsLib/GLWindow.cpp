/*
 *  GLWindow.cpp
 *  Project2
 *
 *  Created by Brady Law on 10/25/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "GraphicsLib/GLWindow.h"

#ifdef __APPLE__ 
#include <OPENGL/gl.h> 
#include <OPENGL/glu.h> 
#include <GLUT/glut.h> 
#else 
#include <GL/gl.h> 
#include <GL/glu.h> 
#include <GL/glut.h> 
#endif 

#include <iostream>

void GLWindow::Init(int* argc, char** argv, int width, int height, int x, int y) {
    SetDimensions(width, height);
    
    glutInit(argc, argv);                      // OpenGL initializations
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);// double buffering and RGB
    glutInitWindowSize(800, 600);               // create a 400x400 window
    glutInitWindowPosition(0, 0);               // ...in the upper left
    glutCreateWindow(argv[0]);                  // create the window
    
    animation_speed_ = 0.01; // Set default animation speed
}

void GLWindow::Draw() {
    for(list<GLDrawable*>::iterator i = children_.begin(); i != children_.end(); i++) {
        (*i)->Draw();
    }
}

void GLWindow::Tick(int time_elapsed) {
    for(list<GLDrawable*>::iterator i = children_.begin(); i != children_.end(); i++) {
        (*i)->Tick(time_elapsed);
    }
}