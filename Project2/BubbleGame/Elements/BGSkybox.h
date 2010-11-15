/*
 *  BGSkybox.h
 *  Project2
 *
 *  Created by Brady Law on 10/26/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "GraphicsLib/GLMovable.h"
#include "GraphicsLib/RGBpixmap/RGBpixmap.h"

class BGSkybox : public GLMovable {
public:
    BGSkybox(Vector3d pos) : GLMovable(pos) {
        Init();
    }
    ~BGSkybox() { }
    
    void Init();
    
    virtual void Draw();
    virtual void Tick(int time_elapsed);
    
    static const float X_SIZE = 10000.0f;
    static const float Y_SIZE = 10000.0f;
    static const float Z_SIZE = 10000.0f;
protected:
    bool alive_; // True if the ball is still on screen
    RGBpixmap pixmap_;
};
