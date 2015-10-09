#ifndef WE_TRIMESH_H
#define WE_TRIMESH_H

#include <Windows.h>
#include <gl\GL.h>
#include "scene/animation/Bone.h"
#include "scene/animation/VertexBoneInfo.h"

/**
 * TriMesh defines a mesh of triangles.
 * It uses an indexed triangle list-- (index triples give the 3 vertices in the vertex array that make up each triangle).
 */
class TriMesh
{
protected:
	int numVParts;				//# vertex specifiers (# vertices times 3)
	GLfloat* vertices;			//vertex array
	int numIParts;				//# indices (# triangles times 3)
	GLuint* indices;			//index array for triangles
	GLfloat* normals;
	GLfloat* UVs;				//texture coordinates per vertex
	int matIndex;				//index to an external list of material properties
	VertexBoneInfo* vBIs;		//bone weight information for each loaded vertex
	Bone** bones;				//bones of the mesh
	int numBones;

	TriMesh();					//blank constructor for inheriting classes only (e.g. primitive mesh shapes)

public:
	TriMesh(int numV, GLfloat* ver, int numI, GLuint* ind, GLfloat* nrm, GLfloat* UV);
	TriMesh(const TriMesh& t);
	~TriMesh();
	int getNumVertices() const;
	int getNumTriangles() const;
	int getNumVParts() const;
	GLfloat* getVertices() const;
	int getNumIndices() const;
	GLuint* getIndices() const;
	int getNumNParts() const;
	GLfloat* getNormals() const;
	int getNumUVs() const;
	GLfloat* getUVs() const;
	void setMatIndex( int index );
	int getMatIndex();
	void setVBI( VertexBoneInfo* vbiIn );
	VertexBoneInfo* getVBI();
	void setBones( Bone** bonesIn, int nB );
	Bone** getBones();
	Bone* getBone(int i);
	Bone* getBone(std::string boneName);
};
#endif