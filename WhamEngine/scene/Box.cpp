#include "stdafx.h"

#include "Box.h"

//probably this leaves detached arrays from the TriMesh constructor, wasting memory
Box::Box()
{
	// an 8-vertex box
	numVParts = 24;
	vertices = new GLfloat[24];

	//top vertices, clockwise
	vertices[0]  = -0.5f;	vertices[1]  = 0.5f; 	vertices[2]  = -0.5f;
	vertices[3]  =  0.5f;	vertices[4]  = 0.5f; 	vertices[5]  = -0.5f;
	vertices[6]  =  0.5f;	vertices[7]  = 0.5f;	vertices[8]  =  0.5f;
	vertices[9]  = -0.5f;	vertices[10] = 0.5f;	vertices[11] =  0.5f;

	//bottom vertices, clockwise
	vertices[12]  = -0.5f;	vertices[13]  = -0.5f; 	vertices[14]  = -0.5f;
	vertices[15]  =  0.5f;	vertices[16]  = -0.5f; 	vertices[17]  = -0.5f;
	vertices[18]  =  0.5f;	vertices[19]  = -0.5f;	vertices[20]  =  0.5f;
	vertices[21]  = -0.5f;	vertices[22] = -0.5f;	vertices[23] =  0.5f;

	//This requires 12 triangles
	numIParts = 36;
	indices = new GLuint[36];

	//top of the box
	indices[0] = 0;		indices[1] = 2;		indices[2] = 1;
	indices[3] = 0;		indices[4] = 3;		indices[5] = 2;

	//front side
	indices[6] = 3;		indices[7] = 6;		indices[8] = 2;
	indices[9] = 3;		indices[10] = 7;	indices[11] = 6;

	//left side
	indices[12] = 0;	indices[13] = 7;	indices[14] = 3;
	indices[15] = 0;	indices[16] = 4;	indices[17] = 7;

	//right side
	indices[18] = 2;	indices[19] = 5;	indices[20] = 1;
	indices[21] = 2;	indices[22] = 6;	indices[23] = 5;

	//back side
	indices[24] = 1;	indices[25] = 4;	indices[26] = 0;
	indices[27] = 1;	indices[28] = 5;	indices[29] = 4;

	//bottom side
	indices[30] = 7;	indices[31] = 5;	indices[32] = 6;
	indices[33] = 7;	indices[34] = 4;	indices[35] = 5;

	//normal components
	normals = new GLfloat[24];
	normals[0] = -0.5774f;	normals[1] = 0.5774f;	normals[2] = -0.5774f;
	normals[3] = 0.5774f;	normals[4] = 0.5774f;	normals[5] = -0.5774f;
	normals[6] = 0.5774f;	normals[7] = 0.5774f;	normals[8] = 0.5774f;
	normals[9] = -0.5774f;	normals[10] = 0.5774f;	normals[11] = 0.5774f;

	normals[12] = -0.5774f;	normals[13] = -0.5774f;	normals[14] = -0.5774f;
	normals[15] = 0.5774f;	normals[16] = -0.5774f;	normals[17] = -0.5774f;
	normals[18] = 0.5774f;	normals[19] = -0.5774f; normals[20] = 0.5774f;
	normals[21] = -0.5774f;	normals[22] = -0.5774f; normals[23] = 0.5774f;

	//texture coordinates
	UVs = new GLfloat[16];
	UVs[0] = 1.0f;	UVs[1] = 1.0f;
	UVs[2] = 0.0f;	UVs[3] = 1.0f;
	UVs[4] = 0.0f;	UVs[5] = 0.0f;
	UVs[6] = 1.0f;	UVs[7] = 0.0f;

	UVs[8] = 0.0f;	UVs[9] = 1.0f;
	UVs[10] = 1.0f;	UVs[11] = 1.0f;
	UVs[12] = 1.0f;	UVs[13] = 0.0f;
	UVs[14] = 0.0f;	UVs[15] = 0.0f;
};

Box::Box( float w, float l, float h )
{
	// an 8-vertex box
	numVParts = 24;
	vertices = new float[24];

	float hw = w/2;
	float hl = l/2;
	float hh = h/2;

	//top vertices, counterclockwise
	vertices[0]  = -hw;		vertices[1]  = hh; 		vertices[2]  = -hl;
	vertices[3]  =  hw;		vertices[4]  = hh; 		vertices[5]  = -hl;
	vertices[6]  =  hw;		vertices[7]  = hh;		vertices[8]  =  hl;
	vertices[9]  = -hw;		vertices[10] = hh;		vertices[11] =  hl;

	//bottom vertices, counterclockwise
	vertices[12]  = -hw;	vertices[13] = -hh; 	vertices[14] = -hl;
	vertices[15]  =  hw;	vertices[16] = -hh; 	vertices[17] = -hl;
	vertices[18]  =  hw;	vertices[19] = -hh;	vertices[20] =  hl;
	vertices[21]  = -hw;	vertices[22] = -hh;	vertices[23] =  hl;

	//This requires 12 triangles
	numIParts = 36;
	indices = new GLuint[36];

	//top of the box
	indices[0] = 0;		indices[1] = 2;		indices[2] = 1;
	indices[3] = 0;		indices[4] = 3;		indices[5] = 2;

	//front side
	indices[6] = 3;		indices[7] = 6;		indices[8] = 2;
	indices[9] = 3;		indices[10] = 7;	indices[11] = 6;

	//left side
	indices[12] = 0;	indices[13] = 7;	indices[14] = 3;
	indices[15] = 0;	indices[16] = 4;	indices[17] = 7;

	//right side
	indices[18] = 2;	indices[19] = 5;	indices[20] = 1;
	indices[21] = 2;	indices[22] = 6;	indices[23] = 5;

	//back side
	indices[24] = 1;	indices[25] = 4;	indices[26] = 0;
	indices[27] = 1;	indices[28] = 5;	indices[29] = 4;

	//bottom side
	indices[30] = 7;	indices[31] = 5;	indices[32] = 6;
	indices[33] = 7;	indices[34] = 4;	indices[35] = 5;

	//normal components
	normals = new GLfloat[24];
	normals[0] = -0.5774f;	normals[1] = 0.5774f;	normals[2] = -0.5774f;
	normals[3] = 0.5774f;	normals[4] = 0.5774f;	normals[5] = -0.5774f;
	normals[6] = 0.5774f;	normals[7] = 0.5774f;	normals[8] = 0.5774f;
	normals[9] = -0.5774f;	normals[10] = 0.5774f;	normals[11] = 0.5774f;

	normals[12] = -0.5774f;	normals[13] = -0.5774f;	normals[14] = -0.5774f;
	normals[15] = 0.5774f;	normals[16] = -0.5774f;	normals[17] = -0.5774f;
	normals[18] = 0.5774f;	normals[19] = -0.5774f; normals[20] = 0.5774f;
	normals[21] = -0.5774f;	normals[22] = -0.5774f; normals[23] = 0.5774f;

	//texture coordinates
	UVs = new GLfloat[16];
	UVs[0] = 1.0f;	UVs[1] = 1.0f;
	UVs[2] = 0.0f;	UVs[3] = 1.0f;
	UVs[4] = 0.0f;	UVs[5] = 0.0f;
	UVs[6] = 1.0f;	UVs[7] = 0.0f;

	UVs[8] = 0.0f;	UVs[9] = 1.0f;
	UVs[10] = 1.0f;	UVs[11] = 1.0f;
	UVs[12] = 1.0f;	UVs[13] = 0.0f;
	UVs[14] = 0.0f;	UVs[15] = 0.0f;
};
Box::~Box()
{
	delete vertices;
	delete indices;
	delete UVs;
}