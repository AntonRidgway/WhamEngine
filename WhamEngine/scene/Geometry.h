#ifndef WE_GEOM_H
#define WE_GEOM_H

#include <Windows.h>
#include <gl\GL.h>
#include <string>
#include "Entity.h"
#include "TriMesh.h"
#include "resources/Material.h"
#include "resources/Texture.h"

class Geometry : public Entity
{
private:
	TriMesh* meshData;					// the Geometry's mesh of triangles
	Texture* meshTex;					// the texture to apply to the mesh
	Material* meshMat;					// the material to apply to the mesh

public:
	Geometry( TriMesh* tri, Texture* tex, Material* mat, std::string nameIn = "geometry" );
	Geometry( Geometry& g );
	~Geometry();

	TriMesh* getMeshData() const;
	int getNumVertices() const;
	GLfloat* getVertices() const;
	int getNumIndices() const;
	GLuint* getIndices() const;
	int getNumNormals() const;
	GLfloat* getNormals() const;
	GLfloat* getUVs() const;

	Texture* getMeshTex() const;
	unsigned char* getTexData() const;
	int getTexW() const;
	int getTexH() const;
	GLuint getTexID() const;
	void setTexID( GLuint newID );

	Material* getMeshMat() const;

	void draw();
};

#endif