/*
 *  BGBall.h
 *  Project2
 *
 *  Created by Brady Law on 10/25/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef INC_BGBALL_H
#define INC_BGBALL_H

#include "BubbleGame/Elements/BGMovable.h"
#include "BubbleGame/Elements/BGPlatform.h"
#include "BubbleGame/Elements/BGObstacle.h"

#include <set>
using namespace std;

class BGBall : public BGMovable {
public:
    BGBall(Vector3d pos, const BubbleGame& game) : BGMovable(pos, game) {
        acc_ = BGMovable::GRAVITY;
    }
    ~BGBall() { }
    
    virtual void Draw();
    virtual void Tick(int time_elapsed);
    void DrawObject();
    
    void Poke(Vector3d direction);
    
    static const int GLUT_SLICES = 60;
    static const float RADIUS = 75.0f;
    static const float POKE_VEL_CHANGE = 30.0f;
    static const float AIR_RESISTANCE = 1.001f;
    static const float COLLISION_DAMP = 0.55f;
protected:
    bool alive_; // True if the ball is still on screen
};

#endif