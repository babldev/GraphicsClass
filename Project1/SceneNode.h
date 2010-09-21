/*
 *  SceneNode.h
 *  Project1
 *
 *  Created by Brady Law on 9/21/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 *  Code made with some help from:
 *  http://www.gamedev.net/reference/programming/features/scenegraph/page2.asp
 *
 */

#include <list>
using namespace std;

class GLWindow;

class SceneNode {
public:
    SceneNode() { }

    virtual ~SceneNode() { Destroy(); }
	
	void Release() { delete this; }
	
	virtual void DrawInWindow(GLWindow* window) {
		for(list<SceneNode*>::iterator i = children_.begin(); i != children_.end(); i++) {
			(*i)->DrawInWindow(window);
		}
	}
	
	void Destroy() {
		for(list<SceneNode*>::iterator i = children_.begin(); i != children_.end(); i++) {
			(*i)->Release();
		}
        
		children_.clear();
	}
	
	void AddChild(SceneNode* new_child) {
		children_.push_back(new_child);
	}
	
protected:
	list<SceneNode*> children_;    
};

