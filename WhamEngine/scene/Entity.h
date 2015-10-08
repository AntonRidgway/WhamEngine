#ifndef WE_ENTITY_H
#define WE_ENTITY_H

#include "Spatial.h"
#include <string>

//placeholder class
class Entity : public Spatial
{
public:
	Entity(std::string nameIn = "null");
	Entity(Vector3f translationIn, Matrix44f rotationIn, float scaleIn = 1.0f, std::string nameIn = "null");
	Entity(Entity& e);
	virtual void draw() = 0;
};

#endif