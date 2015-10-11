#include "stdafx.h"
#include <Windows.h>
#include <gl\GL.h>
#include "TriMesh.h"
TriMesh::TriMesh()
{
}
TriMesh::TriMesh(int numV, GLfloat* ver, int numI, GLuint* ind, GLfloat* nrm, GLfloat* UVin)
{
	numVParts = numV;
	vertices = new float[numVParts];
	for ( int i = 0; i < numVParts; i++ )
		vertices[i] = ver[i];

	numIParts = numI;
	indices = new GLuint[numIParts];
	for ( int i = 0; i < numIParts; i++ )
		indices[i] = ind[i];

	normals = new GLfloat[numVParts];
	for( int i = 0; i < numVParts; i++ )
		normals[i] = nrm[i];

	int tempNum = numVParts*2/3;
	UVs = new GLfloat[tempNum];
	for ( int i = 0; i < tempNum; i++ )
		UVs[i] = UVin[i];
}
TriMesh::TriMesh(const TriMesh& t)
{
	numVParts = t.getNumVertices();
	vertices = new float[numVParts];
	float* temp1 = t.getVertices();
	for ( int i = 0; i < numVParts; i++ )
		vertices[i] = temp1[i];

	numIParts = t.getNumIndices();
	indices = new GLuint[numIParts];
	GLuint* temp2 = t.getIndices();
	for ( int i = 0; i < numIParts; i++ )
		indices[i] = temp2[i];

	normals = new GLfloat[numVParts];
	GLfloat* temp3 = t.getNormals();
	for ( int i = 0; i < numVParts; i++ )
		normals[i] = temp3[i];

	int tempNum = numVParts*2/3;
	UVs = new GLfloat[tempNum];
	GLfloat* temp4 = t.getUVs();
	for ( int i = 0; i < tempNum; i++ )
		UVs[i] = temp4[i];

}
TriMesh::~TriMesh()
{
	if(vertices != NULL)
		delete[] vertices;
	if(indices != NULL)
		delete[] indices;
	if(normals != NULL)
		delete[] normals;
	if( UVs != NULL )
		delete[] UVs;
}

int TriMesh::getNumVertices() const
{
	return numVParts/3;
}
int TriMesh::getNumTriangles() const
{
	return numIParts/3;
}
int TriMesh::getNumVParts() const
{
	return numVParts;
}
GLfloat* TriMesh::getVertices() const
{
	return vertices;
}
int TriMesh::getNumIndices() const
{
	return numIParts;
}
GLuint* TriMesh::getIndices() const
{
	return indices;
}
int TriMesh::getNumNParts() const
{
	return numVParts;
}
GLfloat* TriMesh::getNormals() const
{
	return normals;
}
int TriMesh::getNumUVs() const
{
	return numVParts*2/3;
}
GLfloat* TriMesh::getUVs() const
{
	return UVs;
}
void TriMesh::setMatIndex( int index )
{
	matIndex = index;
}
int TriMesh::getMatIndex()
{
	return matIndex;
}
void TriMesh::setVBI( VertexBoneInfo* vbiIn )
{
	vBIs = vbiIn;
}
VertexBoneInfo* TriMesh::getVBI()
{
	return vBIs;
}
//void TriMesh::setBones( Bone** bonesIn, int nB )
//{
//	bones = bonesIn;
//	numBones = nB;
//}
//Bone** TriMesh::getBones()
//{
//	return bones;
//}
//Bone* TriMesh::getBone(int i)
//{
//	if (i >= 0 && i < numBones)
//		return bones[i];
//	return NULL;
//}
//Bone* TriMesh::getBone(std::string boneName)
//{
//	for(int i = 0; i < numBones; i++)
//	{
//		if(bones[i]->getName() == boneName)
//			return bones[i];
//	}
//	return NULL;
//}