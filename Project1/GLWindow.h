/*
 *  GLWindow.h
 *  Project1
 *
 *  Created by Brady Law on 9/21/10.
 *  Copyright 2010 Brady Law. All rights reserved.
 *
 */

#ifndef INC_GLWINDOW_H
#define INC_GLWINDOW_H

#include "GLDrawable.h"

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
    
    float GLValForXPixel(float pixels) {
        return pixels / (float) width_;
    }
    
    float GLValForYPixel(float pixels) {
        return pixels / (float) height_;
    }
    
protected:
    int width_;
    int height_;
    
    list<GLDrawable*> children_; 
};

#endif /* INC_GLWINDOW_H */