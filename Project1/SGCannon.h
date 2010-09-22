/*
 *  SGCannon.h
 *  Project1
 *
 *  Created by Brady Law on 9/21/10.
 *  Copyright 2010 Brady Law. All rights reserved.
 *
 */

#include "GLMovable.h"

class SGCannon : public GLMovable {
public:
	SGCannon(Vector2d pos) : GLMovable(pos) {
    }
    ~SGCannon() { }
    
    // Keyboard controls
    void MoveLeft();
    void MoveRight();
    
    void AimToVector(const Vector2d* target);
    
    // Inherited methods
    virtual void Draw();
    virtual void Tick(int time_elapsed);
    
    // Constants
    static const float kHeight = 50;
    static const float kWidth = 15;

    static const int MOVE_DISTANCE = 50;
    
private:
    int moving_;
};