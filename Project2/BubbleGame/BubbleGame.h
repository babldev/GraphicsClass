/*
 *  BubbleGame.h
 *  Project2
 *
 *  Created by Brady Law on 10/25/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "GraphicsLib/GLWindow.h"

#include "BubbleGame/Elements/BGBall.h"
#include "BubbleGame/Elements/BGPlatform.h"

class BubbleGame {
public:
    BubbleGame() { }
    
    ~BubbleGame() {
        delete window_;
    }
    
    void Init(int* argc, char** argv, int width, int height);
    void RegisterCallbacks();
    void Reset();
    
    void OnDisplayEvent();
    void OnReshapeEvent(int w, int h);
    void OnMouseEvent(int b, int s, int x, int y);
    void OnKeyboardEvent(unsigned char c, int x, int y);
    void OnMouseMove(int x, int y);
    void OnTick();
    void ToggleFullscreen();
    
    static void DisplayEvent() { game.OnDisplayEvent(); }
    static void ReshapeEvent(int w, int h) { game.OnReshapeEvent(w, h); }
    static void MouseEvent(int b, int s, int x, int y) { game.OnMouseEvent(b, s, x, y); }
    static void KeyboardEvent(unsigned char c, int x, int y) { game.OnKeyboardEvent(c, x, y); }
    static void MouseMove(int x, int y) { game.OnMouseMove(x, y); }
    static void Tick() { game.OnTick(); }
    
    static const int TIMER_DELAY;
    
    static const float CAMERA_FOV_DEGREES = 30.0f;
    static const float CAMERA_NEAR_CLIP = 50.0f;
    static const float CAMERA_FAR_CLIP = 100000.0f;
        
    static BubbleGame game;
    
protected:
    GLWindow* window_;
    bool fullscreen_;
    
    // Camera
    Vector3d camera_up_;
    Vector3d camera_eye_;
    Vector3d camera_center_;
    
    
    // Helper pointers
    BGBall* ball_;
    BGPlatform* ground_;
    
    int last_tick_;
};