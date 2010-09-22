/*
 *  ShooterGame.h
 *  Project1
 *
 *  Created by Brady Law on 9/21/10.
 *  Copyright 2010 Brady Law. All rights reserved.
 *
 */

#include "GLWindow.h"
#include "SGBall.h"
#include "SGCannon.h"

class ShooterGame {
public:
    ShooterGame() { }
    
    ~ShooterGame() {
        delete window_;
    }
    
    void Init(int* argc, char** argv, int width, int height);
    
    void OnDisplayEvent();
    void OnReshapeEvent(int w, int h);
    void OnMouseEvent(int b, int s, int x, int y);
    void OnKeyboardEvent(unsigned char c, int x, int y);
    void OnTick();
    
    static void DisplayEvent() { game.OnDisplayEvent(); }
    static void ReshapeEvent(int w, int h) { game.OnReshapeEvent(w, h); }
    static void MouseEvent(int b, int s, int x, int y) { game.OnMouseEvent(b, s, x, y); }
    static void KeyboardEvent(unsigned char c, int x, int y) { game.OnKeyboardEvent(c, x, y); }
    static void Tick() { game.OnTick(); }
    
    static const int TIMER_DELAY;
    
    static ShooterGame game;
    
protected:
    GLWindow* window_;
    
    // Helper pointers
    SGBall* ball_;
    SGCannon* cannon_;
    
    int last_tick_;
};