/*
 *  GLWindow.h
 *  Project1
 *
 *  Created by Brady Law on 9/21/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "SceneNode.h"

class GLWindow : public SceneNode {
public:
    GLWindow(int width, int height) : width_(width), height_(height) { }
    
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
    
protected:
    int width_;
    int height_;
};