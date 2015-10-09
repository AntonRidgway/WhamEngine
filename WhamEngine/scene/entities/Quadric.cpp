#include "stdafx.h"

#include "Quadric.h"
#include <gl\GL.h>

Quadric::Quadric(Texture* texIn, Material* matIn, GLfloat x, GLfloat y, GLfloat z, GLenum dSIn, GLenum nIn, GLenum oIn, GLenum teIn)
{
	quadObj = gluNewQuadric();
	myTex = texIn;
	myMat = matIn;
	translate(x,y,z);
	gluQuadricDrawStyle(quadObj,dSIn);
	gluQuadricNormals(quadObj, nIn);
	gluQuadricOrientation(quadObj, oIn);
	gluQuadricTexture(quadObj, teIn);
}
Quadric::~Quadric()
{
	gluDeleteQuadric(quadObj);
}
GLUquadricObj* Quadric::getObject()
{
	return quadObj;
}
GLfloat Quadric::getX() { return getTranslation().getEntry(0); }
GLfloat Quadric::getY() { return getTranslation().getEntry(1); }
GLfloat Quadric::getZ() { return getTranslation().getEntry(2); }

QuadricSphere::QuadricSphere(Texture* texIn, Material* matIn, GLfloat x, GLfloat y, GLfloat z, GLdouble rIn, GLint lonIn, GLint latIn,
							  GLenum dSIn, GLenum nIn, GLenum oIn, GLenum teIn)
			  :Quadric(texIn,matIn,x,y,z,dSIn,nIn,oIn,teIn)
{
	radius = rIn;
	slices = lonIn;
	stacks = latIn;
}
QuadricSphere::~QuadricSphere()
{
}
void QuadricSphere::renderSpecific()
{
	float shininess [1] = {myMat->getShininess()};

	//Load in material properties
	glMaterialfv(GL_FRONT, GL_EMISSION, myMat->getEmissive());
	glMaterialfv(GL_FRONT, GL_AMBIENT, myMat->getAmbient());
	glMaterialfv(GL_FRONT, GL_DIFFUSE, myMat->getDiffuse());
	glMaterialfv(GL_FRONT, GL_SPECULAR, myMat->getSpecular());
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	GLuint gfxID = myTex->getGfxID();
	if( gfxID != 0 )
	{
		glBindTexture(GL_TEXTURE_2D, gfxID);
	}
	else
	{
		glGenTextures(1,&gfxID);
		myTex->setGfxID(gfxID);
		glBindTexture(GL_TEXTURE_2D,gfxID);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB8,myTex->getWidth(),myTex->getHeight(),0,GL_RGB,GL_UNSIGNED_BYTE,myTex->getData());
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	}
	
	gluSphere(quadObj,radius,slices,stacks);
}