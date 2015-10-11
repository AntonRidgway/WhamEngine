#ifndef WE_SKNODE_H
#define WE_SKNODE_H

#include <vector>
#include "math/Matrix.h"
#include "scene/Spatial.h"

class Bone : public Spatial
{
private:
	Bone* parent;
	std::vector<Bone*> children;
	unsigned int* meshIndex;
	int numMIndices;
	Matrix44f* animTransform;
public:
	Bone();
	Bone( Bone* parent );
	~Bone();
	void attachChild( Bone* b );
	void setParent( Bone* b );
	//Bone* getChild( std::string boneName ) const;
	Bone* getChild( unsigned int index ) const;
	int getNumChildren() const;
	void setMIndex( int i, unsigned int val );
	unsigned int getMIndex( int i ) const;
	void addNumMIndices( int i );
	int getNumMIndices() const;
	void setAnimTransform( Matrix44f* transIn );
	Matrix44f* getAnimTransform();
};

#endif