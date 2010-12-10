/*
 *  BGObstacle.h
 *  Project2
 *
 *  Created by Brady Law on 10/25/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef INC_BGOBSTACLE_H
#define INC_BGOBSTACLE_H

#include "BubbleGame/Elements/BGMovable.h"
#include "BubbleGame/Elements/BGPlatform.h"

class BGObstacle : public BGMovable {
public:
    BGObstacle(Vector3d pos, const BubbleGame& game) : BGMovable(pos, game) {
        // acc_ = Vector3d(0.0f, 0.0f, -20.0f);
    }
    ~BGObstacle() { }
    
    virtual void Draw();
    virtual void Tick(int time_elapsed);
    void DrawObject();
    
    float radius() {
        return BGObstacle::RADIUS;
    }
    
    static const int GLUT_SLICES = 60;
    static const float RADIUS = 100.0f;
    static const float POKE_VEL_CHANGE = 30.0f;
    static const float AIR_RESISTANCE = 1.001f;
    static const float COLLISION_DAMP = 0.85f;
protected:
    bool alive_; // True if the ball is still on screen
};

#endif /* INC_BGOBSTACLE_H */