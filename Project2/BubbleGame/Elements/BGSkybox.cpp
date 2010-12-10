/*
 *  BGSkybox.cpp
 *  Project2
 *
 *  Created by Brady Law on 10/26/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "BubbleGame/Elements/BGSkybox.h"

#include "GraphicsLib/GLWindow.h"
#include "GraphicsLib/GLerror.h"

#ifdef __APPLE__
#include <OPENGL/gl.h>
#include <OPENGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <cmath>                        // standard definitions
#include <iostream>

void BGSkybox::Init() {
    //------------------------------------------------------------------
    //  Read texture from a .bmp file (done once)
    //------------------------------------------------------------------
    // TODO - This needs to be updated to the local directory
    if (!pixmap_.readBMPFile("skybox-clouds.bmp", true, true)) {
        cerr << "File skybox-clouds.bmp cannot be read or illegal format" << endl;
        exit(1);
    }
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);      // store pixels by byte
    glBindTexture(GL_TEXTURE_2D, 0);            // select current texture (0)
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    // set texture parameters
    // glTexParameteri(GL_TEXTURE_2D, /* assign parameters for texture 0 */ );
    glTexImage2D(                               // initialize texture
                 GL_TEXTURE_2D,                          // texture is 2-d
                 0,                                      // resolution level 0
                 GL_RGB,                                 // internal format
                 pixmap_.nCols,                         // image width
                 pixmap_.nRows,                         // image height
                 0,                                      // no border
                 GL_RGB,                                 // my format
                 GL_UNSIGNED_BYTE,                       // my type
                 pixmap_.pixel);                        // the pixels
    
    checkGLerror("texture setup");
}

void BGSkybox::Draw() {
    glDisable(GL_LIGHTING);
    GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glEnable(GL_TEXTURE_2D);                    // enable texture mapping
    
    glMaterialfv(GL_FRONT_AND_BACK,             // white background
                 GL_AMBIENT_AND_DIFFUSE,
                 white);

    glPushMatrix();
    glScalef(BGSkybox::X_SIZE, BGSkybox::Y_SIZE, BGSkybox::Z_SIZE);
    
    // Top face
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glTranslatef(-0.5f, -0.5f, 0.0f);
    glMatrixMode(GL_MODELVIEW);
    
    glBegin(GL_POLYGON);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(-0.25f, -0.25f); glVertex3f(-1.0f,1.0f, 1.0f);  // Bottom Left
    glTexCoord2f(0.25f, -0.25f); glVertex3f(1.0f,1.0f, 1.0f);   // Bottom Right
    glTexCoord2f(0.25f, 0.25f); glVertex3f(1.0f,-1.0f, 1.0f);    // Top Right
    glTexCoord2f(-0.25f, 0.25f); glVertex3f(-1.0f,-1.0f, 1.0f);   // Top Left
    glEnd();
    
    // Front face
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glTranslatef(-0.5f, -0.5f, 0.0f);
    glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(-0.25f, -0.5f);glVertex3f(1.0f, -1.0f, -1.0f);  // Bottom Left
    glTexCoord2f(0.25f, -0.5f); glVertex3f(-1.0f, -1.0f, -1.0f);   // Bottom Right
    glTexCoord2f(0.25f, -0.25f); glVertex3f(-1.0f, -1.0f, 1.0f);    // Top Right
    glTexCoord2f(-0.25f, -0.25f); glVertex3f(1.0f, -1.0f, 1.0f);   // Top Left
    glEnd();
    
    // Back Face
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glTranslatef(-0.5f, -0.5f, 0.0f);
    // No rotate
    glMatrixMode(GL_MODELVIEW);
    
    glBegin(GL_QUADS);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(-0.25f, -0.5f); glVertex3f(-1.0f, 1.0f, -1.0f);  // Bottom Left
    glTexCoord2f(0.25f, -0.5f); glVertex3f(1.0f, 1.0f, -1.0f);   // Bottom Right
    glTexCoord2f(0.25f, -0.25f); glVertex3f(1.0f, 1.0f, 1.0f);    // Top Right
    glTexCoord2f(-0.25f, -0.25f); glVertex3f(-1.0f, 1.0f, 1.0f);   // Top Left
    glEnd();
    
    // Right Face
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glTranslatef(-0.5f, -0.5f, 0.0f);
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    
    glBegin(GL_QUADS);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(-0.25f, -0.5f); glVertex3f(1.0f, 1.0f, -1.0f);  // Bottom Left
    glTexCoord2f(0.25f, -0.5f); glVertex3f(1.0f, -1.0f, -1.0f);   // Bottom Right
    glTexCoord2f(0.25f, -0.25f);  glVertex3f(1.0f, -1.0f, 1.0f);    // Top Right
    glTexCoord2f(-0.25f, -0.25f); glVertex3f(1.0f, 1.0f, 1.0f);   // Top Left
    glEnd();
    
    // Left Face
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glTranslatef(-0.5f, -0.5f, 0.0f);
    glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    
    glBegin(GL_QUADS);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(-0.25f, -0.5f);glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Left
    glTexCoord2f(0.25f, -0.5f); glVertex3f(-1.0f, 1.0f, -1.0f);   // Bottom Right
    glTexCoord2f(0.25f, -0.25f); glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Right
    glTexCoord2f(-0.25f, -0.25f); glVertex3f(-1.0f, -1.0f, 1.0f);   // Top Left
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);                   // disable texture mapping
    glEnable(GL_LIGHTING);
}

void BGSkybox::Tick(int time_elapsed) {
    GLMovable::Tick(time_elapsed);
}