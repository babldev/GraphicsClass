/*
 *  GLDrawable.h
 *  Project1
 *
 *  Created by Brady Law on 9/21/10.
 *  Copyright 2010 Brady Law. All rights reserved.
 *
 */

#ifndef INC_GLDRAWABLE_H
#define INC_GLDRAWABLE_H

class GLWindow;

#include <list>
using namespace std;

class GLDrawable {
public:
    GLDrawable() { }
    virtual ~GLDrawable() { Destroy(); }
    
    void Release() { delete this; }
    
    GLWindow* window() { return window_; }
    void set_window(GLWindow* window) { window_ = window; };
    
    virtual void Draw() {
        for(list<GLDrawable*>::iterator i = children_.begin(); i != children_.end(); i++) {
            (*i)->Draw();
        }
    }
    
    virtual void Tick(int time_elapsed) {
        for(list<GLDrawable*>::iterator i = children_.begin(); i != children_.end(); i++) {
            (*i)->Tick(time_elapsed);
        }
    }
    
    void Destroy() {
        for(list<GLDrawable*>::iterator i = children_.begin(); i != children_.end(); i++) {
            (*i)->Release();
        }
        
        children_.clear();
    }
    
    void AddChild(GLDrawable* new_child) {
        children_.push_back(new_child);
        new_child->set_window(window_);
    }
    
protected:
    GLWindow* window_;
    list<GLDrawable*> children_;   
};

#endif /* INC_GLDRAWABLE_H */