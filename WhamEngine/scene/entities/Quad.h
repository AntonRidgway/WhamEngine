#ifndef WE_QUAD
#define WE_QUAD

#include "TriMesh.h"

class Quad : public TriMesh
{
public:
	Quad();
	Quad( float w, float h );
	~Quad();
};

#endif