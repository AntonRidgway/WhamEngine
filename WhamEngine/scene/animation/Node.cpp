#include "stdafx.h"
#include "Node.h"

Node::Node(Node* parentIn, Bone* boneIn)
{
	parent = parentIn;
	myBone = boneIn;
}
Node::~Node()
{
}
void Node::attachChild( Node* c )
{
	children.push_back(c);
}
void Node::removeChild(Node* c) {
	children.erase(std::remove(children.begin(), children.end(), c), children.end());
}
int Node::getNumChildren() {
	return children.size();
}
Node* Node::getChild( int i )
{
	if(i >= 0 && i < children.size()) {
		return children[i];
	}
	return NULL;
}
void Node::setParent(Node* n) {
	parent = n;
}
Node* Node::getParent() {
	return parent;
}
void Node::setBone(Bone* boneIn) {
	myBone = boneIn;
}
Bone* Node::getBone() {
	return myBone;
}