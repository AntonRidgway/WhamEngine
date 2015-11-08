#ifndef WE_ENTITY_H
#define WE_ENTITY_H

#include "scene/Spatial.h"
#include <string>
#include <Windows.h>
#include <gl/GL.h>

//placeholder class
class Entity : public Spatial
{
public:
	Entity(std::string nameIn = "null");
	Entity(Vector3f translationIn, Matrix44f rotationIn, Vector3f scaleIn, std::string nameIn = "null");
	Entity(Entity& e);
	void render();
protected:
	virtual void renderSpecific() = 0;
};

#endif