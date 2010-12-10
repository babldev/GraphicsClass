/*
 *  BGMovable.h
 *  Project2
 *
 *  Created by Brady Law on 12/9/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef INC_BGMOVABLE_H
#define INC_BGMOVABLE_H

#include "GraphicsLib/GLMovable.h"
class BubbleGame;

class BGMovable : public GLMovable {
public:
    BGMovable(Vector3d pos, const BubbleGame& game) : GLMovable(pos), game_(game) { }
    ~BGMovable() { }
    
    static const Vector3d GRAVITY;
protected:
    const BubbleGame& game_;
};

#endif /* INC_BGMOVABLE_H */