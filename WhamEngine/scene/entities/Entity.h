#ifndef WE_ENTITY_H
#define WE_ENTITY_H

#include "scene/Spatial.h"
#include <string>
#include <Windows.h>
#include <gl/GL.h>

class Entity : public Spatial
{
public:
	Entity(std::string nameIn = "null");
	Entity(Vector3f translationIn, Matrix44f rotationIn, Vector3f scaleIn, std::string nameIn = "null");
	Entity(Entity& e);
	void render();
	void setRelativeTranslation(Vector3f transIn);
	Vector3f getRelativeTranslation();
	void setRelativeRotation(Matrix44f rotIn);
	Matrix44f getRelativeRotation();
protected:
	virtual void renderSpecific() = 0;
	Vector3f relTranslation;
	Matrix44f relRotation;
};

#endif