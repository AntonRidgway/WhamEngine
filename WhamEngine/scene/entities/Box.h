#ifndef WE_BOX_H
#define WE_BOX_H

#include "TriMesh.h"

class Box : public TriMesh
{
public:
	Box();
	Box( float w, float l, float h );
	~Box();
};

#endif