//-----------------------------------------------------------------------
//      File:           sample1cpp.cpp
//      Description:    A sample OpenGL program
//      Programmer:     Dave Mount
//      For:            CMSC 427 - Computer Graphics
//      Date:           Sep 2010
//
//      This is just a sample skeleton C++ program, which shows the
//      general structure of a minimal OpenGL program.
//-----------------------------------------------------------------------

#include <cstdlib>                      // standard definitions
#include <iostream>                     // C++ I/O
#include <cstdio>                       // C I/O (for sprintf) 
#include <cmath>                        // standard definitions

#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>

using namespace std;                    // make std accessible

//-----------------------------------------------------------------------
// Global data
//-----------------------------------------------------------------------

GLint TIMER_DELAY = 10000;                      // timer delay (10 seconds)
GLfloat RED_RGB[] = {1.0, 0.0, 0.0};            // drawing colors
GLfloat BLUE_RGB[] = {0.0, 0.0, 1.0};

//-----------------------------------------------------------------------
//  Global variables
//-----------------------------------------------------------------------
static bool isReversed = false;                 // draw reversed colors?

//-----------------------------------------------------------------------
//  Callbacks
//      The global variable "isReversed" describes the drawing state.
//      When false, a blue rectangle is drawn on top of red diamond.
//      When true the colors are reversed.  The "isReversed" variable is
//      complemented whenever the left mouse button is clicked or the
//      timer goes off (every 10 seconds).
//-----------------------------------------------------------------------

void myReshape(int w, int h) {
    cout << "MyReshape called width=" << w << " height=" << h << endl;
    glViewport (0, 0, w, h);                    // update the viewport
    glMatrixMode(GL_PROJECTION);                // update projection
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0);             // map unit square to viewport
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();                        // request redisplay
}
                                                // draw diamond and rectangle
void drawObjects(GLfloat* diamColor, GLfloat* rectColor) {
    glColor3fv(diamColor);                      // set diamond color
    glBegin(GL_POLYGON);                        // draw the diamond
        glVertex2f(0.90, 0.50);
        glVertex2f(0.50, 0.90);
        glVertex2f(0.10, 0.50);
        glVertex2f(0.50, 0.10);
    glEnd();
    glColor3fv(rectColor);                      // set rectangle color
    glRectf(0.25, 0.25, 0.75, 0.75);            // draw the rectangle
}

void myDisplay(void) {                          // display callback
    cout << "MyDisplay called" << endl;
    glClearColor(0.5, 0.5, 0.5, 1.0);           // background is gray
    glClear(GL_COLOR_BUFFER_BIT);               // clear the window
    
    if (isReversed)                             // draw the objects
        drawObjects(BLUE_RGB, RED_RGB);
    else
        drawObjects(RED_RGB, BLUE_RGB);
    glutSwapBuffers();                          // swap buffers
}

void myTimer(int id) {                          // timer callback
    cout << "Timer just went off.  Reversing colors." << endl;
    isReversed = !isReversed;                   // reverse drawing colors
    glutPostRedisplay();                        // request redraw
    glutTimerFunc(TIMER_DELAY, myTimer, 0);     // reset timer for 10 seconds
}

void myMouse(int b, int s, int x, int y) {      // mouse click callback
    if (s == GLUT_DOWN) {
        cout << "Mouse click detected at coordinates x="
             << x << " and y=" << y << endl;
        if (b == GLUT_LEFT_BUTTON) {
            isReversed = !isReversed;
            cout << "Left mouse click.  Reversing colors." << endl;
            glutPostRedisplay();
        }
    }
}
                                                // keyboard callback
void myKeyboard(unsigned char c, int x, int y) {
    switch (c) {                                // c is the key that is hit
        case 'q':                               // 'q' means quit
            exit(0);
            break;
        default:
            cout << "Hit q to quit.  All other characters ignored" << endl;
            break;
    }
}

//-----------------------------------------------------------------------
//  Main program
//      This does all the set up for the program.  It creates the game
//      and then passes control to glut.
//-----------------------------------------------------------------------

int main(int argc, char** argv)
{
    cout << "\n\
-----------------------------------------------------------------------\n\
  CMSC 427 Sample Program.\n\
  - Click left mouse button to swap colors.\n\
  - Try resizing and covering/uncovering the window.\n\
  - Hit q to quit.\n\
-----------------------------------------------------------------------\n";

    glutInit(&argc, argv);                      // OpenGL initializations
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);// double buffering and RGB
    glutInitWindowSize(400, 400);               // create a 400x400 window
    glutInitWindowPosition(0, 0);               // ...in the upper left
    glutCreateWindow(argv[0]);                  // create the window

    glutDisplayFunc(myDisplay);                 // setup callbacks
    glutReshapeFunc(myReshape);
    glutMouseFunc(myMouse);
    glutKeyboardFunc(myKeyboard);
    glutTimerFunc(TIMER_DELAY, myTimer, 0);
    glutMainLoop();                             // start it running
    return 0;                                   // ANSI C expects this
}
