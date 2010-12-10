/*
 *  BGBall.cpp
 *  Project2
 *
 *  Created by Brady Law on 10/25/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "BubbleGame/Elements/BGBall.h"
#include "GraphicsLib/GLWindow.h"
#include "BubbleGame/BubbleGame.h"

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

void BGBall::Draw() {
    GLfloat diffuse_color[] = {0, 1.0f, 1.0f, 1.0f};
    GLfloat specular_color[] = {1.0f, 1.0f, 1.0f, 1.0f};
    const GLdouble shadow_proj_matrix[] = {
        1.0f, 0, 0, 0,
        0, 1.0f, 0, 0,
        1.0f, 1.0f, 0, 0,
        0, 0, 50.1f, 1.0f};
    
    // FIXME: Temporary hardcoded shadow fix
    if (pos_.z > 25.0f) {
        glStencilFunc(GL_EQUAL, 1, 1);
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
        glEnable(GL_STENCIL_TEST);
        
        glDisable(GL_LIGHTING);
        glPushMatrix();
        glColor4f(0.0f, 0.0f, 0.0f, 0.15f);
        glMultMatrixd(shadow_proj_matrix);
        // glMatrixMode(GL_MODELVIEW);
        DrawObject();
        // glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glEnable(GL_LIGHTING);
        glColor4f(1, 1, 1, 1.0f);
        
        glDisable(GL_STENCIL_TEST);
    }
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffuse_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_color);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50);
    DrawObject();
}

void BGBall::DrawObject() {
    glPushMatrix();
        glTranslatef(pos_.x, pos_.y, pos_.z);
        glScalef(BGBall::RADIUS, BGBall::RADIUS, BGBall::RADIUS);
        glutSolidSphere(1.0f, BGBall::GLUT_SLICES, BGBall::GLUT_SLICES);
    glScalef(1.1f, 1.1f, 1.1f);
        glutSolidIcosahedron();
    glPopMatrix();
}

void BGBall::Tick(int time_elapsed) {
    Vector3d original_pos = pos_;
    
    GLMovable::Tick(time_elapsed);
    vel_ /= BGBall::AIR_RESISTANCE;
    
    /* Check for Ball/Obstacle collision. Simple collisions between 2 spheres. */
    const set<BGObstacle*> obstacles = game_.obstacles();
    for (set<BGObstacle*>::iterator ob_it = obstacles.begin(); ob_it != obstacles.end(); ob_it++) {
        Vector3d orig_distance_vector = (*ob_it)->pos_ - original_pos;
        float orig_collision_amount = (*ob_it)->radius() + BGBall::RADIUS - 
        orig_distance_vector.length();
        
        // If there wasn't a collision originally...
        if (orig_collision_amount <= 0) {
            Vector3d distance_vector = (*ob_it)->pos_ - pos_;
            float collision_amount = (*ob_it)->radius() + BGBall::RADIUS - distance_vector.length();
            
            // And there is one now
            if (collision_amount > 0) {
                // Update the velocity and position to handle the collision
                cout << "Collision!" << endl;
                Vector3d v_par = Vector3d::parProject(vel_, distance_vector);
                Vector3d v_orth = vel_ - v_par;
                vel_ = v_orth - COLLISION_DAMP * v_par; // Apply the new dampened velocity
                
                // Separate the collided objects
                distance_vector.normalize();
                pos_ += (Vector3d::zero() - distance_vector) * collision_amount;
            }
        }
    }
    
    /* Check for Ball/Platform collision. A little more complicated collision between a sphere and
     * box. */
    const set <BGPlatform*> platforms = game_.platforms();
    for (set<BGPlatform*>::iterator p_it = platforms.begin(); p_it != platforms.end(); p_it++) {
    }
}

void BGBall::Poke(Vector3d direction) {
    direction.normalize();
    vel_ += direction * BGBall::POKE_VEL_CHANGE;
}