/*
 *  BGPlatform.h
 *  Project2
 *
 *  Created by Brady Law on 10/25/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef INC_BGPLATFORM_H
#define INC_BGPLATFORM_H

#include "BubbleGame/Elements/BGMovable.h"

class BGPlatform : public BGMovable {
public:
    BGPlatform(Vector3d pos, const BubbleGame& game, bool tall) : BGMovable(pos, game), tall_(tall) {
        height_ = (tall) ? 200.0f : 50.0f; 
    }
    ~BGPlatform() { }
    
    virtual void Draw();
    virtual void Tick(int time_elapsed);
    void DrawObject();
    
    static const float X_SIZE = 250.0f;
    static const float Y_SIZE = 250.0f;
protected:
    bool alive_; // True if the ball is still on screen
    bool tall_;
    float height_;
};

#endif /* INC_BGPLATFORM_H */