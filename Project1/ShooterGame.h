/*
 *  ShooterGame.h
 *  Project1
 *
 *  Created by Brady Law on 9/21/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "GLWindow.h"

#include "SGBall.h"
#include "SGGun.h"

class ShooterGame {
public:
    ShooterGame() {
    }
    
    ~ShooterGame() {
    }
    
    InitWithSize(int width, int height) {
        window_ = new GLWindow(int width, int height);
        ball_ = new SGBall(50, 50);
        
        window_.AddChild(ball_);
    }
    
protected:
    GLWindow* window_;
    SGBall* ball_;
}