#include "stdafx.h"

#include "Pyramid.h"

Pyramid::Pyramid() : TriMesh()
{
	// a 5-vertex pyramid
	numVParts = 15;
	vertices = new GLfloat[15];
	vertices[0]  = -0.5f;	vertices[1]  = 0.0f; 	vertices[2]  =  0.5f;
	vertices[3]  =  0.5f;	vertices[4]  = 0.0f; 	vertices[5]  =  0.5f;
	vertices[6]  =  0.5f;	vertices[7]  = 0.0f;	vertices[8]  = -0.5f;
	vertices[9]  = -0.5f;	vertices[10] = 0.0f;	vertices[11] = -0.5f;
	vertices[12] =  0.0f;	vertices[13] = 0.5f;	vertices[14] =  0.0f;

	//This requires 6 triangles
	numIParts = 18;
	indices = new GLuint[18];
	indices[0] = 3;		indices[1] = 0;		indices[2] = 4;
	indices[3] = 0;		indices[4] = 1;		indices[5] = 4;
	indices[6] = 1;		indices[7] = 2;		indices[8] = 4;
	indices[9] = 2;		indices[10] = 3;	indices[11] = 4;
	indices[12] = 0;	indices[13] = 3;	indices[14] = 2;
	indices[15] = 0;	indices[16] = 2;	indices[17] = 1;

	normals = new GLfloat[15];
	normals[0] = -0.5774f;	normals[1] = -0.5774f;	normals[2] = 0.5774f;
	normals[3] = 0.5774f;	normals[4] = -0.5774f;	normals[5] = 0.5774f;
	normals[6] = 0.5774f;	normals[7] = -0.5774f;	normals[8] = -0.5774f;
	normals[0] = -0.5774f;	normals[1] = -0.5774f;	normals[2] = -0.5774f;
	normals[0] = 0.0f;	normals[1] = 1.0f;	normals[2] = 0.0f;

	UVs = new GLfloat[10];
	UVs[0] = 0.0f;	UVs[1] = 0.0f;
	UVs[2] = 1.0f;	UVs[3] = 0.0f;
	UVs[4] = 0.0f;	UVs[5] = 0.0f;
	UVs[6] = 1.0f;	UVs[7] = 0.0f;
	UVs[8] = 0.5f;	UVs[9] = 1.0f;
}


Pyramid::Pyramid( float w, float h ):TriMesh()
{
	float newWid = 0.5f*w;
	float newHgt = 0.5f*h;

	// a 5-vertex pyramid
	numVParts = 15;
	vertices = new GLfloat[15];
	vertices[0]  = -newWid;	vertices[1]  = 0.0f; 	vertices[2]  =  newWid;
	vertices[3]  =  newWid;	vertices[4]  = 0.0f; 	vertices[5]  =  newWid;
	vertices[6]  =  newWid;	vertices[7]  = 0.0f;	vertices[8]  = -newWid;
	vertices[9]  = -newWid;	vertices[10] = 0.0f;	vertices[11] = -newWid;
	vertices[12] =  0.0f;	vertices[13] = newHgt;	vertices[14] =  0.0f;

	//This requires 6 triangles
	numIParts = 18;
	indices = new GLuint[18];
	indices[0] = 3;		indices[1] = 0;		indices[2] = 4;
	indices[3] = 0;		indices[4] = 1;		indices[5] = 4;
	indices[6] = 1;		indices[7] = 2;		indices[8] = 4;
	indices[9] = 2;		indices[10] = 3;	indices[11] = 4;
	indices[12] = 0;	indices[13] = 3;	indices[14] = 2;
	indices[15] = 0;	indices[16] = 2;	indices[17] = 1;

	normals = new GLfloat[15];
	normals[0] = -0.5774f;	normals[1] = -0.5774f;	normals[2] = 0.5774f;
	normals[3] = 0.5774f;	normals[4] = -0.5774f;	normals[5] = 0.5774f;
	normals[6] = 0.5774f;	normals[7] = -0.5774f;	normals[8] = -0.5774f;
	normals[0] = -0.5774f;	normals[1] = -0.5774f;	normals[2] = -0.5774f;
	normals[0] = 0.0f;	normals[1] = 1.0f;	normals[2] = 0.0f;

	UVs = new GLfloat[10];
	UVs[0] = 0.0f;	UVs[1] = 0.0f;
	UVs[2] = 1.0f;	UVs[3] = 0.0f;
	UVs[4] = 0.0f;	UVs[5] = 0.0f;
	UVs[6] = 1.0f;	UVs[7] = 0.0f;
	UVs[8] = 0.5f;	UVs[9] = 1.0f;
}

Pyramid::~Pyramid()
{
	delete vertices;
	delete indices;
	delete UVs;
}