#ifndef WE_PYRAMID_H
#define WE_PYRAMID_H

#include "TriMesh.h"

class Pyramid : public TriMesh
{
public:
	Pyramid();
	Pyramid( float w, float h );
	~Pyramid();
};

#endif