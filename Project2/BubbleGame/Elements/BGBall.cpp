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
#include "Utilities/Utilities.h"

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
    
        glMultMatrixd(ang_pos_.getRotationMatrix().oglMat());
        
        glScalef(BGBall::RADIUS, BGBall::RADIUS, BGBall::RADIUS);
        glutSolidSphere(1.0f, BGBall::GLUT_SLICES, BGBall::GLUT_SLICES);
        
        // Add geometry to show rotation
        glScalef(1.1f, 1.1f, 1.1f);
        glutSolidIcosahedron();
    glPopMatrix();
}

void BGBall::Tick(int time_elapsed) {
    GLMovable::Tick(time_elapsed);
    vel_ *= BGBall::AIR_RESISTANCE;
    ang_vel_ *= BGBall::AIR_RESISTANCE;
        
    double dt = time_elapsed * window_->animation_speed();
    Quaternion w_quat;
    w_quat.setSAndV(0, ang_vel_);
    Quaternion q_dot = 0.5f * (w_quat * ang_pos_);
    ang_pos_ = ang_pos_ + q_dot * dt;
    ang_pos_.normalize();
    
    /* Check for Ball/Obstacle collision. Simple collisions between 2 spheres. */
    const set<BGObstacle*> obstacles = game_.obstacles();
    for (set<BGObstacle*>::iterator ob_it = obstacles.begin(); ob_it != obstacles.end(); ob_it++) {
        Vector3d collision_vector = (*ob_it)->pos_ - pos_;
        float collision_amount = (*ob_it)->radius() + BGBall::RADIUS - collision_vector.length();
        
        // And there is one now
        if (collision_amount > 0) {
            HandleCollision(collision_vector, collision_amount);
        }
    }
    
    /* Check for Ball/Platform collision. A little more complicated collision between a sphere and
     * box. */
    const set<BGPlatform*> platforms = game_.platforms();
    for (set<BGPlatform*>::iterator p_it = platforms.begin(); p_it != platforms.end(); p_it++) {
        BGPlatform* platform = *p_it;
        Vector3d p_center = platform->pos();
        Vector3d p_size = platform->size() / 2;
        
        Vector3d closest_point = Vector3d(
                clamp(pos_.x, p_center.x - p_size.x, p_center.x + p_size.x),
                clamp(pos_.y, p_center.y - p_size.y, p_center.y + p_size.y),
                clamp(pos_.z, p_center.z - p_size.z, p_center.z + p_size.z));
        Vector3d collision_vector = closest_point - pos_;
        float collision_amount = RADIUS - collision_vector.length();
        
        if (collision_amount >= 0) {
            HandleCollision(collision_vector, collision_amount);
        }
    }
}

void BGBall::HandleCollision(Vector3d collision_vector, float collision_amount) {
    collision_vector.normalize();
    
    Vector3d v_par = Vector3d::parProject(vel_, collision_vector);
    Vector3d v_orth = vel_ - v_par;
    vel_ = v_orth - COLLISION_DAMP * v_par; // Apply the new dampened velocity
    
    ang_vel_ = (1 / RADIUS) * Vector3d::cross(v_orth, collision_vector);
    
    // Separate the collided objects
    pos_ += (Vector3d::zero() - collision_vector) * collision_amount;
}

void BGBall::Poke(Vector3d direction) {
    direction.normalize();
    vel_ += direction * BGBall::POKE_VEL_CHANGE;
}
