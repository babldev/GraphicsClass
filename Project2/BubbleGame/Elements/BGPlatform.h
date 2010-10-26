/*
 *  BGPlatform.h
 *  Project2
 *
 *  Created by Brady Law on 10/25/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "GraphicsLib/GLMovable.h"

class BGPlatform : public GLMovable {
public:
    BGPlatform(Vector3d pos) : GLMovable(pos) {
    }
    ~BGPlatform() { }
    
    virtual void Draw();
    virtual void Tick(int time_elapsed);
    
    static const float X_SIZE = 2500.0f;
    static const float Y_SIZE = 2500.0f;
    static const float Z_SIZE = 1.0f;
protected:
    bool alive_; // True if the ball is still on screen
};
