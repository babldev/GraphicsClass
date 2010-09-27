/*
 *  SGCannon.h
 *  Project1
 *
 *  Created by Brady Law on 9/21/10.
 *  Copyright 2010 Brady Law. All rights reserved.
 *
 */

#include "GraphicsLib/GLMovable.h"

class SGCannon : public GLMovable {
public:
    SGCannon(Vector2d pos) : GLMovable(pos) {
    }
    ~SGCannon() { }
    
    // Keyboard controls
    void MoveLeft();
    void MoveRight();
    
    void set_target(const Vector2d target);
    const Vector2d aim_vector() { return aim_vector_; }
    
    // Inherited methods
    virtual void Draw();
    virtual void Tick(int time_elapsed);
    
    // Constants
    static const float kHeight = 50;
    static const float kWidth = 15;

    static const int MOVE_DISTANCE = 50;
    
private:
    Vector2d target_;
    Vector2d aim_vector_;
    int moving_;
};