#include "stdafx.h"

#include "Quad.h"

Quad::Quad() : TriMesh()
{
	// a 4-vertex Quad
	numVParts = 12;
	vertices = new GLfloat[12];
	vertices[0]  = -0.5f;	vertices[1]  = 1.0f; 	vertices[2]  = 0.0f;
	vertices[3]  = -0.5f;	vertices[4]  = 0.0f; 	vertices[5]  = 0.0f;
	vertices[6]  =  0.5f;	vertices[7]  = 0.0f;	vertices[8]  = 0.0f;
	vertices[9]  =  0.5f;	vertices[10] = 1.0f;	vertices[11] = 0.0f;

	//This requires 2 triangles
	numIParts = 6;
	indices = new GLuint[6];
	indices[0] = 0;		indices[1] = 1;		indices[2] = 2;
	indices[3] = 0;		indices[4] = 2;		indices[5] = 3;

	normals = new GLfloat[12];
	normals[0] = -0.707f;	normals[1] = 0.707f;	normals[2] = 0.0f;
	normals[3] = -0.707f;	normals[4] = -0.707f;	normals[5] = 0.0f;
	normals[6] = 0.707f;	normals[7] = -0.707f;	normals[8] = 0.0f;
	normals[9] = 0.707f;	normals[10] = 0.707f;	normals[11] = 0.0f;

	//Texture coordinates, by vertex (x,y,x,y,x,y,x,y)
	UVs = new GLfloat[8];
	UVs[0] = 0.0f;	UVs[1] = 1.0f;
	UVs[2] = 0.0f;	UVs[3] = 0.0f;
	UVs[4] = 1.0f;	UVs[5] = 0.0f;
	UVs[6] = 1.0f;	UVs[7] = 1.0f;
}
Quad::Quad( float w, float h ) : TriMesh()
{
	float hw = w/2;

	// a 4-vertex Quad
	numVParts = 12;
	vertices = new float[12];
	vertices[0]  = -hw;	vertices[1]  = h; 		vertices[2]  = 0.0f;
	vertices[3]  = -hw;	vertices[4]  = 0.0f; 	vertices[5]  = 0.0f;
	vertices[6]  =  hw;	vertices[7]  = 0.0f;	vertices[8]  = 0.0f;
	vertices[9]  =  hw;	vertices[10] = h;		vertices[11] = 0.0f;

	//This requires 2 triangles
	numIParts = 6;
	indices = new GLuint[6];
	indices[0] = 0;		indices[1] = 1;		indices[2] = 2;
	indices[3] = 0;		indices[4] = 2;		indices[5] = 3;

	// Normals for each vertex
	normals = new GLfloat[12];
	normals[0] = -0.707f;	normals[1] = 0.707f;	normals[2] = 0.0f;
	normals[3] = -0.707f;	normals[4] = -0.707f;	normals[5] = 0.0f;
	normals[6] = 0.707f;	normals[7] = -0.707f;	normals[8] = 0.0f;
	normals[9] = 0.707f;	normals[10] = 0.707f;	normals[11] = 0.0f;
	
	//Texture coordinates, by vertex
	UVs = new GLfloat[8];
	UVs[0] = 0.0f;	UVs[1] = 1.0f;
	UVs[2] = 0.0f;	UVs[3] = 0.0f;
	UVs[4] = 1.0f;	UVs[5] = 0.0f;
	UVs[6] = 1.0f;	UVs[7] = 1.0f;
}

Quad::~Quad()
{
	delete vertices;
	delete indices;
	delete normals;
	delete UVs;
}