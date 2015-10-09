#include "stdafx.h"
#include "Entity.h"

Entity::Entity(std::string nameIn) : Spatial(nameIn) {}
Entity::Entity(Vector3f translationIn, Matrix44f rotationIn, float scaleIn, std::string nameIn) : Spatial(translationIn, rotationIn, scaleIn, nameIn) {};
Entity::Entity(Entity& e) : Spatial(e) {};
void Entity::render() {
	Matrix44f rotation = getRotation();
	float rotMatrix[16] =
	{
		rotation.getEntry(0,0), rotation.getEntry(0,1), rotation.getEntry(0,2), 0.0f,
		rotation.getEntry(1,0), rotation.getEntry(1,1), rotation.getEntry(1,2), 0.0f,
		rotation.getEntry(2,0), rotation.getEntry(2,1), rotation.getEntry(2,2), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	//float rotMatrix[16] =
	//{
	//	rotation.getEntry(0,0), rotation.getEntry(1,0), rotation.getEntry(2,0), 0.0f,
	//	rotation.getEntry(0,1), rotation.getEntry(1,1), rotation.getEntry(2,1), 0.0f,
	//	rotation.getEntry(0,2), rotation.getEntry(1,2), rotation.getEntry(2,2), 0.0f,
	//	0.0f, 0.0f, 0.0f, 1.0f
	//};
	Vector3f translation = getTranslation();
	float transMatrix[16] =
	{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		translation.getEntry(0), translation.getEntry(1), translation.getEntry(2), 1.0f
	};
	float scale = getScale();
	float scaleMatrix[16] =
	{
		scale, 0.0f, 0.0f, 0.0f,
		0.0f, scale, 0.0f, 0.0f,
		0.0f, 0.0f, scale, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	// set the model-to-world transformation
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMultMatrixf(transMatrix);
	glMultMatrixf(rotMatrix);
	glMultMatrixf(scaleMatrix);
	renderSpecific();
	glPopMatrix();
}