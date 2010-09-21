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

class SceneNode {
public:
    SceneNode() { }

    virtual SceneNode() { Destroy(); }
	
	void Release() { delete this; }
	
	virtual void Update() {
		for(std::list<SceneNode*>::iterator i = children_.begin(); i != children_.end(); i++) {
			(*i)->Update();
		}
	}
	
	void Destroy() {
		for(std::list<SceneNode*>::iterator i = children_.begin(); i != children_.end(); i++) {
			(*i)->Release();
		}
        
		children_.clear();
	}
	
	void AddChild(SceneNode* new_child) {
		m_lstChildren.push_back(new_child);
	}
	
protected:
	std::list<SceneNode*> children_;    
}

