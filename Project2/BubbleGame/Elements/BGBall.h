/*
 *  BGBall.h
 *  Project2
 *
 *  Created by Brady Law on 10/25/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "GraphicsLib/GLMovable.h"
#include "BubbleGame/Elements/BGPlatform.h"
#include "BubbleGame/Elements/BGObstacle.h"

#include <list>
using namespace std;

class BGBall : public GLMovable {
public:
    BGBall(Vector3d pos) : GLMovable(pos) {
        acc_ = Vector3d(0.0f, 0.0f, -20.0f);
    }
    ~BGBall() { }
    
    virtual void Draw();
    virtual void Tick(int time_elapsed);
    void DrawObject();
    
    void Poke(Vector3d direction);
    
    void set_supporting_platform(BGPlatform* platform) {
        support_platform_ = platform;
    }
    
    void set_obstacles(std::list<BGObstacle*>* obstacles) {
        obstacles_ = obstacles;
    }
    
    static const int GLUT_SLICES = 60;
    static const float RADIUS = 50.0f;
    static const float POKE_VEL_CHANGE = 30.0f;
    static const float AIR_RESISTANCE = 1.001f;
    static const float COLLISION_DAMP = 0.55f;
protected:
    bool alive_; // True if the ball is still on screen
    BGPlatform* support_platform_;
    std::list<BGObstacle*> *obstacles_;
};