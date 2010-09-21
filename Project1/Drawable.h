/*
 *  Drawable.h
 *  Project1
 *
 *  Created by Brady Law on 9/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

class Drawable {
public:
	Drawable(float pos_x, float pos_y) : pos_x_(pos_x), pos_y_(pos_y)
	{ }
	virtual void draw() = 0;
	void move(float x, float y);
	
protected:
	float pos_x_;
	float pos_y_;	
};

