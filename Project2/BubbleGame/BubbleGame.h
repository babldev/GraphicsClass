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
#include "BubbleGame/Elements/BGSkybox.h"
#include "BubbleGame/Elements/BGObstacle.h"

class BubbleGame {
public:
    BubbleGame() {
    }
    
    ~BubbleGame() {
        delete window_;
    }
    
    void Init(int* argc, char** argv, int width, int height);
    
    void OnDisplayEvent();
    void OnReshapeEvent(int w, int h);
    void OnMouseEvent(int b, int s, int x, int y);
    void OnKeyboardEvent(unsigned char c, int x, int y);
    void OnPassiveMouseMove(int x, int y);
    void OnMouseMove(int x, int y);
    void OnTick();
    void ToggleFullscreen();
    
    static void DisplayEvent() { game.OnDisplayEvent(); }
    static void ReshapeEvent(int w, int h) { game.OnReshapeEvent(w, h); }
    static void MouseEvent(int b, int s, int x, int y) { game.OnMouseEvent(b, s, x, y); }
    static void KeyboardEvent(unsigned char c, int x, int y) { game.OnKeyboardEvent(c, x, y); }
    static void PassiveMouseMove(int x, int y) { game.OnPassiveMouseMove(x, y); }
    static void MouseMove(int x, int y) { game.OnMouseMove(x, y); }
    static void Tick() { game.OnTick(); }
    void PokeBall(int direction);
    
    static const int TIMER_DELAY;
    
    static const float CAMERA_FOV_DEGREES = 30.0f;
    static const float CAMERA_NEAR_CLIP = 50.0f;
    static const float CAMERA_FAR_CLIP = 100000.0f;
    static const float CAMERA_ZOOM_RATE = 0.05f;
    
    static const int POKE_UP = 0;
    static const int POKE_FORWARDS = 1;
    static const int POKE_BACKWARDS = 2;
    static const int POKE_LEFT = 3;
    static const int POKE_RIGHT = 4;
    
    static BubbleGame game;
    
private:
    void RegisterCallbacks();
    void Reset();
    void AddObstacles();
    void AutoZoomCamera();
    void AddLighting();
    
protected:
    GLWindow* window_;
    bool fullscreen_;
    
    float camera_distance_;
    float camera_auto_distance_;
    float camera_elevation_angle_;
    float camera_azimuth_angle_;
    
    // Camera
    Vector3d camera_up_;
    Vector3d camera_eye_;
    Vector3d camera_center_;
    
    int mouse_pos_x_;
    int mouse_pos_y_;
    
    // Helper pointers
    BGBall* ball_;
    std::list<BGObstacle*> obstacles_;
    BGPlatform* ground_;
    BGSkybox* skybox_;
    
    int last_tick_;
};