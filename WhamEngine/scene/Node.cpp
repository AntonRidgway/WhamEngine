#include "stdafx.h"
#include "Node.h"

Node::Node()
{
	parent = NULL;
}
Node::Node( Node* par )
{
	parent = par;
}
Node::~Node()
{
}
void Node::attachChild( Geometry* c )
{
	gChildren.push_back(c);
}
void Node::attachChild( Node* c )
{
	nChildren.push_back(c);
}
Spatial* Node::getChild( std::string nodeName )
{
	if(getName()==nodeName) return this;
	std::vector<Geometry*>::iterator gItr;
	for ( gItr = gChildren.begin(); gItr != gChildren.end(); gItr++ )
	{
		if((*gItr)->getName() == nodeName) return *gItr;
	}
	std::vector<Node*>::iterator nItr;
	for( nItr = nChildren.begin(); nItr != nChildren.end(); nItr++ )
	{
		Spatial* wantedNode = (*nItr)->getChild(nodeName);
		if(wantedNode != NULL) return wantedNode;
	}
	return NULL;
}
Node* Node::getNChild( unsigned int index ) const
{
	if(index >= 0 && index < nChildren.size())
	{
		return nChildren[index];
	}
	return NULL;
}