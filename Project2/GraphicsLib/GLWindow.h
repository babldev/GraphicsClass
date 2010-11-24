/*
 *  GLWindow.h
 *  Project2
 *
 *  Created by Brady Law on 10/25/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef INC_GLWINDOW_H
#define INC_GLWINDOW_H

#include "GraphicsLib/GLDrawable.h"

#include <list>
using namespace std;

class GLWindow {
public:
    GLWindow() { }
    ~GLWindow() { Destroy(); }
    
    void Init(int* argc, char** argv, int width, int height, int x, int y);
    
    void SetDimensions(int width, int height) {
        width_ = width;
        height_ = height;
    }
    
    int width() {
        return width_;
    }
    
    int height() {
        return height_;
    }
    
    void Draw();
    
    void Tick(int time_elapsed);
    
    void Destroy() {
        for(list<GLDrawable*>::iterator i = children_.begin(); i != children_.end(); i++) {
            (*i)->Release();
        }
        
        children_.clear();
    }
    
    void AddChild(GLDrawable* new_child) {
        children_.push_back(new_child);
        new_child->set_window(this);
    }
    
    void RemoveChild(GLDrawable* child) {
        children_.remove(child);
    }
    
    void ClearChildren() {
        children_.clear();
    }
    
    float animation_speed() {
        return animation_speed_;
    }
    
    float animation_speed_;
    
    static const float DEGREES_TO_RADIANS = 3.14159/180;
    static const float RADIANS_TO_DEGREES = 180/3.14159;
    static const float ANIMATION_SPEED_INC = 0.002;
    
protected:
    // Window size
    int width_;
    int height_;
    
    list<GLDrawable*> children_; 
};

#endif /* INC_GLWINDOW_H */