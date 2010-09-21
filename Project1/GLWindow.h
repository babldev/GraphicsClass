/*
 *  GLWindow.h
 *  Project1
 *
 *  Created by Brady Law on 9/21/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "SceneNode.h"

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
	
	void Destroy() {
		for(list<SceneNode*>::iterator i = children_.begin(); i != children_.end(); i++) {
			(*i)->Release();
		}
        
		children_.clear();
	}
	
	void AddChild(SceneNode* new_child) {
		children_.push_back(new_child);
	}
    
protected:
    int width_;
    int height_;
    
    list<SceneNode*> children_; 
};