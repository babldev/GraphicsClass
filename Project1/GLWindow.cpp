/*
 *  GLWindow.cpp
 *  Project1
 *
 *  Created by Brady Law on 9/21/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "GLWindow.h"

#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>

#include <iostream>

void GLWindow::Init(int* argc, char** argv, int width, int height, int x, int y) {
    glutInit(argc, argv);                      // OpenGL initializations
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);// double buffering and RGB
    glutInitWindowSize(800, 600);               // create a 400x400 window
    glutInitWindowPosition(0, 0);               // ...in the upper left
    glutCreateWindow(argv[0]);                  // create the window
}

void GLWindow::Draw() {
    cout << "Drawing!" << endl;
    
    for(list<SceneNode*>::iterator i = children_.begin(); i != children_.end(); i++) {
        (*i)->DrawInWindow(this);
    }
}