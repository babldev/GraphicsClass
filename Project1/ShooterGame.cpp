/*
 *  ShooterGame.cpp
 *  Project1
 *
 *  Created by Brady Law on 9/21/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ShooterGame.h"

#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>

#include <iostream>

ShooterGame ShooterGame::game = ShooterGame();

const int ShooterGame::TIMER_DELAY = 10000;

void ShooterGame::Init(int* argc, char** argv, int width, int height) {  
    // Create window
    window_ = new GLWindow();
    window_->Init(argc, argv, width, height, 0, 0);
    
    // Add objects
    ball_ = new SGBall(0.5, 0.5, 0.2);
    window_->AddChild(ball_);
    
    // Terminal instructions
    cout << "\n\
	-----------------------------------------------------------------------\n\
	CMSC 427 - Project 1.\n\
	- Click left mouse button to swap colors.\n\
	- Try resizing and covering/uncovering the window.\n\
	- Hit q to quit.\n\
	-----------------------------------------------------------------------\n";
    
    // Set up callbacks
    glutDisplayFunc(ShooterGame::DisplayEvent);
    glutReshapeFunc(ShooterGame::ReshapeEvent);
    glutMouseFunc(ShooterGame::MouseEvent);
    glutKeyboardFunc(ShooterGame::KeyboardEvent);
    glutTimerFunc(TIMER_DELAY, ShooterGame::Tick, 0);
    
    // Run
    glutMainLoop();
}

void ShooterGame::OnDisplayEvent(void) {
    cout << "MyDisplay called" << endl;
    glClearColor(0.0, 0.0, 0.0, 1.0);           // background is gray
    glClear(GL_COLOR_BUFFER_BIT);               // clear the window
    
    window_->Draw();

    glutSwapBuffers();                          // swap buffers
}

void ShooterGame::OnReshapeEvent(int w, int h) {
    cout << "MyReshape called width=" << w << " height=" << h << endl;
    glViewport (0, 0, w, h);                    // update the viewport
    glMatrixMode(GL_PROJECTION);                // update projection
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0);             // map unit square to viewport
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();                        // request redisplay
}

void ShooterGame::OnMouseEvent(int b, int s, int x, int y) {      // mouse click callback
    if (s == GLUT_DOWN) {
        cout << "Mouse click detected at coordinates x="
		<< x << " and y=" << y << endl;
        if (b == GLUT_LEFT_BUTTON) {
            cout << "Left mouse click." << endl;
            glutPostRedisplay();
        }
    }
}

void ShooterGame::OnKeyboardEvent(unsigned char c, int x, int y) {
    switch (c) {                                // c is the key that is hit
        case 'q':                               // 'q' means quit
            exit(0);
            break;
        default:
            cout << "Hit q to quit.  All other characters ignored" << endl;
            break;
    }
}

void ShooterGame::OnTick(int id) {
    cout << "Timer just went off.  Reversing colors." << endl;
    glutPostRedisplay();                        // request redraw
    glutTimerFunc(TIMER_DELAY, ShooterGame::Tick, 0);     // reset timer for 10 seconds
}