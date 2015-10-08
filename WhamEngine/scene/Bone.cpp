#include "stdafx.h"

#include "Bone.h"

Bone::Bone()
{
	parent = NULL;
	meshIndex = new unsigned int[10];
	for(int i = 0; i < 10; i++) meshIndex[i]=-1;
	numMIndices = 0;
}
Bone::Bone( Bone* parentIn )
{
	parent = parentIn;
	meshIndex = new unsigned int[10];
	for(int i = 0; i < 10; i++) meshIndex[i]=-1;
	numMIndices = 0;
}
Bone::~Bone()
{
}
void Bone::attachChild( Bone* b )
{
	children.push_back(b);
	b->setParent(this);
}
void Bone::setParent( Bone* b )
{
	parent = b;
}
/*Bone* Bone::getChild( std::string boneName ) const
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
}*/
Bone* Bone::getChild( unsigned int index ) const
{
	if(index >= 0 && index < children.size())
	{
		return children[index];
	}
	return NULL;
}
void Bone::setMIndex( int i, unsigned int val )
{
	meshIndex[i] = val;
}
unsigned int Bone::getMIndex( int i ) const
{
	return meshIndex[i];
}
void Bone::setAnimTransform( Matrix44f* transIn )
{
	if(animTransform != NULL) delete animTransform;
	animTransform = transIn;
}
Matrix44f* Bone::getAnimTransform()
{
	return animTransform;
}
void Bone::addNumMIndices( int i )
{
	numMIndices += i;
}
int Bone::getNumMIndices() const
{
	return numMIndices;
}