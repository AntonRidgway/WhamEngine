#ifndef WE_QUADRIC_H
#define WE_QUADRIC_H

#include "Entity.h"
#include "resources/Texture.h"
#include "resources/Material.h"

class Quadric : public Entity
{
protected:
	GLUquadricObj* quadObj;
	Texture* myTex;
	Material* myMat;
public:
	Quadric(Texture* texIn, Material* matIn, GLfloat x = 0.0f, GLfloat y = 0.0f, GLfloat z = 0.0f,
			GLenum dSIn = GLU_FILL, GLenum nIn = GLU_SMOOTH, GLenum oIn = GLU_OUTSIDE, GLenum teIn = GL_TRUE);
	~Quadric();
	GLUquadricObj* getObject();
	GLfloat getX();
	GLfloat getY();
	GLfloat getZ();
};

class QuadricSphere : public Quadric
{
private:
	GLdouble radius;
	GLint slices;
	GLint stacks;
public:
	QuadricSphere(Texture* texIn, Material* matIn,
				   GLfloat x = 0.0f, GLfloat y = 0.0f, GLfloat z = 0.0f,
				   GLdouble rIn = 1.0f, GLint lonIn = 6, GLint latIn = 6,
				   GLenum dSIn = GLU_FILL, GLenum nIn = GLU_SMOOTH, GLenum oIn = GLU_OUTSIDE, GLenum teIn = GL_TRUE);
	~QuadricSphere();
	virtual void renderSpecific();
};

#endif