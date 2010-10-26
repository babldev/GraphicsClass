/*
 *  BubbleGame.cpp
 *  Project2
 *
 *  Created by Brady Law on 10/25/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "BubbleGame.h"

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
#include <sys/timeb.h>

BubbleGame BubbleGame::game = BubbleGame();

const int BubbleGame::TIMER_DELAY = 10000;

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

void BubbleGame::Init(int* argc, char** argv, int width, int height) {  
    window_ = new GLWindow();
    window_->Init(argc, argv, width, height, 0, 0);
    
    // Terminal instructions
    cout << "\n\
    -----------------------------------------------------------------------\n\
    CMSC 427 - Project 2.\n\
    - Use 'a' and 's' to move your cannon left and right.\n\
    - Hit 'f' to enter fullscreen mode.\n\
    - Hit '+' and '-' to alter the animation speed\n\
    (make sure to hit shift correctly).\n\
    - Hit 'r' too reset.\n\
    - Hit 'q' to quit.\n\
    -----------------------------------------------------------------------\n";
    
    RegisterCallbacks();
    glutGameModeString( "1024x768:16@60" );
    
    glClearColor(0.8, 0.8, 1.0, 1.0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    
    Reset();
    
    camera_up_ = Vector3d(0.0f, 0.0f, 1.0f);
    
    // Run
    glutMainLoop();
}

void BubbleGame::Reset() {
    // TODO: Reset ball, floor
    ball_ = new BGBall(Vector3d(0.0f, 0.0f, 400.0f));
    ground_ = new BGPlatform(Vector3d(0.0f, 0.0f, -100.0f));
    
    window_->AddChild(ball_);
    window_->AddChild(ground_);
    
    last_tick_ = GetMilliCount();
}

void BubbleGame::RegisterCallbacks() {
    glutDisplayFunc(BubbleGame::DisplayEvent);
    glutReshapeFunc(BubbleGame::ReshapeEvent);
    glutMouseFunc(BubbleGame::MouseEvent);
    glutKeyboardFunc(BubbleGame::KeyboardEvent);
    glutIdleFunc(BubbleGame::Tick);
    glutPassiveMotionFunc(BubbleGame::MouseMove);
    glutMotionFunc(BubbleGame::MouseMove);  
}

void BubbleGame::OnDisplayEvent(void) {
    glClear(GL_COLOR_BUFFER_BIT);               // clear the window
    
    // Update the camera
    camera_eye_ = Vector3d(ball_->pos_.x,
                           ball_->pos_.y + 5000.0f,
                           ball_->pos_.z + 5000.0f);
    camera_center_ = ball_->pos_;
    
    glLoadIdentity();
    gluLookAt(camera_eye_.x, camera_eye_.y, camera_eye_.z,
              camera_center_.x, camera_center_.y, camera_center_.z,
              camera_up_.x, camera_up_.y, camera_up_.z);
    // gluLookAt(0.0f, 1.0f, 1000.0f, 0, 0, 0, 0, 0, 1.0f);
    window_->Draw();
    
    // Add lighting
    // (1) Ambient lighting
    GLfloat ambientIntensity[4] = {0.5f, 0.5f, 0.5f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientIntensity);
    
    // (2) Infinite lighting
    GLfloat lt0Intensity[4] = {0.75f, 0.75f, 0.75f, 1.0f}; // white
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lt0Intensity);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lt0Intensity);
    
    GLfloat lt0Position[4] = {-5.0f, -5.0f, 10.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lt0Position); // attenuation params (a,b,c)
    glEnable(GL_LIGHT0);
    
    // (3) Spotlight lighting
    GLfloat lt1Intensity[4] = {0.3f, 0.3f, 0.3f, 1.0f}; // white
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lt1Intensity);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lt1Intensity);
    
    GLfloat lt1Position[4] = {ball_->pos_.x, ball_->pos_.y, ball_->pos_.z + 200.0f, 0.0f};
    glLightfv(GL_LIGHT1, GL_POSITION, lt1Position); // attenuation params (a,b,c)
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.0f);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION,	0.0f);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.001f);
    glEnable(GL_LIGHT1);
    
    // (4) Spotlight lighting
    GLfloat lt2Intensity[4] = {0.3f, 0.3f, 0.3f, 1.0f}; // white
    glLightfv(GL_LIGHT2, GL_DIFFUSE, lt2Intensity);
    glLightfv(GL_LIGHT2, GL_SPECULAR, lt2Intensity);
    
    GLfloat lt2Position[4] = {300.0f, -1700.0f, 500.0f, 1.0f};
    glLightfv(GL_LIGHT2, GL_POSITION, lt2Position); // attenuation params (a,b,c)
    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.0f);
    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION,	0.0f);
    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.0005f);
    glEnable(GL_LIGHT2);
    
    glutSwapBuffers();                          // swap buffers
}

void BubbleGame::OnReshapeEvent(int w, int h) {
    window_->SetDimensions(w, h);
    float ratio = (float) w / h;
    
    cout << "MyReshape called width=" << w << " height=" << h << endl;
    glViewport (0, 0, w, h);                    // update the viewport
    glMatrixMode(GL_PROJECTION);                // update projection
    glLoadIdentity();
    gluPerspective(BubbleGame::CAMERA_FOV_DEGREES,
                   ratio,
                   BubbleGame::CAMERA_NEAR_CLIP,
                   BubbleGame::CAMERA_FAR_CLIP);  // map unit square to viewport
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();                        // request redisplay
    
}

void BubbleGame::OnMouseEvent(int b, int s, int x, int y) {      // mouse click callback
}

void BubbleGame::OnKeyboardEvent(unsigned char c, int x, int y) {
    switch (c) {                                // c is the key that is hit
        case 'q':                               // 'q' means quit
            exit(0);
            break;
        case 'f':
            ToggleFullscreen();
            break;
        case 'r':
            Reset();
            break;
        default:
            cout << "Hit q to quit.  All other characters ignored" << endl;
            break;
    }
}

void BubbleGame::ToggleFullscreen() {
    fullscreen_ = !fullscreen_;
    
    if (fullscreen_) {
        glutEnterGameMode();
    } else {
        glutLeaveGameMode();
        OnReshapeEvent(800, 600);
    }
    
    RegisterCallbacks();
}

void BubbleGame::OnTick() {
    // Tick the animation
    int time_elapsed = GetMilliSpan(last_tick_);
    window_->Tick(time_elapsed);
    last_tick_ += time_elapsed;
    
    glutPostRedisplay();
}

void BubbleGame::OnMouseMove(int x, int y) {
    // Invert the y value. Glut has upper left as origin, BubbleGame has it as the bottom left.
}