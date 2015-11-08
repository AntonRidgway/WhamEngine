#ifndef WE_NODE_H
#define WE_NODE_H

#include <algorithm>
#include <vector>
#include "scene/animation/Bone.h"
#include "scene/Spatial.h"

class Node : public Spatial
{
private:
	Node* parent;
	std::vector<Node*> children;
	Bone* myBone;
public:
	Node( Node* parentIn, Bone* boneIn );
	~Node();
	void attachChild(Node* c);
	void removeChild(Node* c);
	int getNumChildren();
	Node* getChild(int i);
	void setParent(Node* n);
	Node* getParent();
	void setBone(Bone* boneIn);
	Bone* getBone();
};

#endif