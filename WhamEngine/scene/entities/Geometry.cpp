#include "stdafx.h"
#include "Geometry.h"

Geometry::Geometry( TriMesh* tri, Texture* tex, Material* mat, std::string nameIn ) : Entity(nameIn)
{
	 meshData = tri;
	 meshTex = tex;
	 meshMat = mat;
}
Geometry::Geometry( Geometry& g ) : Entity(g)
{
	meshData = g.getMeshData();
	meshTex = g.getMeshTex();
	meshMat = g.getMeshMat();
}
Geometry::~Geometry()
{
}

int Geometry::getNumVertices() const
{
	return meshData->getNumVertices();
}
GLfloat* Geometry::getVertices() const
{
	return meshData->getVertices();
}
int Geometry::getNumIndices() const
{
	return meshData->getNumIndices();
}
GLuint* Geometry::getIndices() const
{
	return meshData->getIndices();
}
int Geometry::getNumNormals() const
{
	return meshData->getNumNParts();
}
GLfloat* Geometry::getNormals() const
{
	return meshData->getNormals();
}
unsigned char* Geometry::getTexData() const
{
	return meshTex->getData();
}
int Geometry::getTexW() const
{
	return meshTex->getWidth();
}
int Geometry::getTexH() const
{
	return meshTex->getHeight();
}
GLuint Geometry::getTexID() const
{
	return meshTex->getGfxID();
}
void Geometry::setTexID( GLuint newID )
{
	meshTex->setGfxID( newID );
}
GLfloat* Geometry::getUVs() const
{
	return meshData->getUVs();
}
TriMesh* Geometry::getMeshData() const
{
	return meshData;
}
Texture* Geometry::getMeshTex() const
{
	return meshTex;
}
Material* Geometry::getMeshMat() const
{
	return meshMat;
}

void Geometry::renderSpecific()
{
		float shininess [1] = {meshMat->getShininess()};

		//load in mesh properties
		glVertexPointer (3, GL_FLOAT, 0, getVertices());
		glIndexPointer (GL_UNSIGNED_INT, 0, getIndices());
		glNormalPointer (GL_FLOAT, 0, getNormals());
		glTexCoordPointer(2, GL_FLOAT,0, getUVs());
				
		//Load in material properties
		glMaterialfv(GL_FRONT, GL_EMISSION, meshMat->getEmissive());
		glMaterialfv(GL_FRONT, GL_AMBIENT, meshMat->getAmbient());
		glMaterialfv(GL_FRONT, GL_DIFFUSE, meshMat->getDiffuse());
		glMaterialfv(GL_FRONT, GL_SPECULAR, meshMat->getSpecular());
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

		//Bind the current texture.
		GLuint temp = getTexID();
		if( temp != 0 )
		{
			glBindTexture(GL_TEXTURE_2D, temp);
		}
		else
		{
			glGenTextures(1,&temp);
			setTexID(temp);
			glBindTexture(GL_TEXTURE_2D,temp);
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGB8,getTexW(),getTexH(),0,GL_RGB,GL_UNSIGNED_BYTE,getTexData());
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		}

		glDrawElements(GL_TRIANGLES, getNumIndices(), GL_UNSIGNED_INT, getIndices());
}