#include "stdafx.h"
#include "Entity.h"

Entity::Entity(std::string nameIn) : Spatial(nameIn) {}
Entity::Entity(Vector3f translationIn, Matrix44f rotationIn, float scaleIn, std::string nameIn) : Spatial(translationIn, rotationIn, scaleIn, nameIn) {};
Entity::Entity(Entity& e) : Spatial(e) {};