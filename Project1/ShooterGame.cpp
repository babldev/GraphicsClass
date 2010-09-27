/*
 *  ShooterGame.cpp
 *  Project1
 *
 *  Created by Brady Law on 9/21/10.
 *  Copyright 2010 Brady Law. All rights reserved.
 *
 */

#include "ShooterGame.h"
#include "Geometry.h"

#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>

#include <iostream>
#include <sys/timeb.h>

ShooterGame ShooterGame::game = ShooterGame();

const int ShooterGame::TIMER_DELAY = 10000;

// From http://www.firstobject.com/getmillicount-milliseconds-portable-c++.htm
// TODO: I don't like this function...
int GetMilliCount() {
    // Something like GetTickCount but portable
    // It rolls over every ~ 12.1 days (0x100000/24/60/60)
    // Use GetMilliSpan to correct for rollover
    timeb tb;
    ftime( &tb );
    int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
    return nCount;
}

int GetMilliSpan(int nTimeStart) {
    int nSpan = GetMilliCount() - nTimeStart;
    if ( nSpan < 0 )
        nSpan += 0x100000 * 1000;
    return nSpan;
}

void ShooterGame::Init(int* argc, char** argv, int width, int height) {  
    window_ = new GLWindow();
    window_->Init(argc, argv, width, height, 0, 0);
    
    ball_ = new SGBall(Vector2d(300, 400), 50);
    window_->AddChild(ball_);
    
    cannon_ = new SGCannon(Vector2d(0.5 * width, SGCannon::kHeight));
    window_->AddChild(cannon_);
    
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
    glutIdleFunc(ShooterGame::Tick);
    glutPassiveMotionFunc(ShooterGame::MouseMove);
    glutMotionFunc(ShooterGame::MouseMove);  
    
    last_tick_ = GetMilliCount();
    
    // Run
    glutMainLoop();
}

void ShooterGame::OnDisplayEvent(void) {
    glClearColor(0.0, 0.0, 0.0, 1.0);           // background is gray
    glClear(GL_COLOR_BUFFER_BIT);               // clear the window
    
    window_->Draw();

    glutSwapBuffers();                          // swap buffers
}

void ShooterGame::OnReshapeEvent(int w, int h) {
    window_->SetDimensions(w, h);
    
    cout << "MyReshape called width=" << w << " height=" << h << endl;
    glViewport (0, 0, w, h);                    // update the viewport
    glMatrixMode(GL_PROJECTION);                // update projection
    glLoadIdentity();
    gluOrtho2D(0.0, w, 0.0, h);             // map unit square to viewport
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();                        // request redisplay
}

void ShooterGame::OnMouseEvent(int b, int s, int x, int y) {      // mouse click callback
    if (s == GLUT_DOWN) {
        cout << "Mouse click detected at coordinates x="
		<< x << " and y=" << y << endl;
        if (b == GLUT_LEFT_BUTTON) {
            cout << "Left mouse click." << endl;
            
            SGBullet* new_bullet = new SGBullet(cannon_->pos_, cannon_->aim_vector());
            bullets_.insert(new_bullet);
            window_->AddChild(new_bullet);
            
            glutPostRedisplay();
        }
    }
}

void ShooterGame::OnKeyboardEvent(unsigned char c, int x, int y) {
    switch (c) {                                // c is the key that is hit
        case 'q':                               // 'q' means quit
            exit(0);
            break;
        case 'a':
            cannon_->MoveLeft();
            break;
        case 'f':
            cannon_->MoveRight();
            break;
        default:
            cout << "Hit q to quit.  All other characters ignored" << endl;
            break;
    }
}

void ShooterGame::OnTick() {
    // Tick the animation
    int time_elapsed = GetMilliSpan(last_tick_);
    window_->Tick(time_elapsed);
    last_tick_ += time_elapsed;
    
    // Remove dead bullets
    for (set<SGBullet*>::iterator bullet_it = bullets_.begin(); bullet_it != bullets_.end();
         ++bullet_it) {
        if (!(*bullet_it)->alive_) {
            window_->RemoveChild(*bullet_it);
            delete *bullet_it;
            bullets_.erase(bullet_it);
        } else {
            // TODO: Clean this
            // Detect ball collisions
            Circle bullet_shape = (*bullet_it)->Shape();
            Circle ball_shape = ball_->Shape();
            
            if (Geometry::CircleIntersectsCircle(&bullet_shape, &ball_shape)) {
                cout << "Hit!" << endl;
                ball_->vel_ += (Vector2d::parProject((*bullet_it)->vel_,
                                                     ball_->vel_ - (*bullet_it)->vel_)) * 0.5;
                window_->RemoveChild(*bullet_it);
                delete *bullet_it;
                bullets_.erase(bullet_it);
            }
        }
    }
        
    glutPostRedisplay();
}

void ShooterGame::OnMouseMove(int x, int y) {
    // Invert the y value. Glut has upper left as origin, ShooterGame has it as the bottom left.
    Vector2d mouse_pos = Vector2d(x, window_->height() - y);
    cannon_->set_target(mouse_pos);
}