#include "stdafx.h"
#include "Entity.h"

Entity::Entity(std::string nameIn) : Spatial(nameIn), relativeTransform(Matrix44f::identity) {}
Entity::Entity(Vector3f translationIn, Matrix44f rotationIn, Vector3f scaleIn, std::string nameIn) : Spatial(translationIn, rotationIn, scaleIn, nameIn), relativeTransform(Matrix44f::identity) {};
Entity::Entity(Entity& e) : Spatial(e), relativeTransform(Matrix44f::identity) {};
void Entity::render() {
	Matrix44f rotation = getRotation();
	float rotMatrix[16] =
	{
		rotation.getEntry(0,0), rotation.getEntry(0,1), rotation.getEntry(0,2), 0.0f,
		rotation.getEntry(1,0), rotation.getEntry(1,1), rotation.getEntry(1,2), 0.0f,
		rotation.getEntry(2,0), rotation.getEntry(2,1), rotation.getEntry(2,2), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	Vector3f translation = getTranslation();
	float transMatrix[16] =
	{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		translation.getEntry(0), translation.getEntry(1), translation.getEntry(2), 1.0f
	};
	Vector3f scale = getScale();
	float scaleMatrix[16] =
	{
		scale.getEntry(0), 0.0f, 0.0f, 0.0f,
		0.0f, scale.getEntry(1), 0.0f, 0.0f,
		0.0f, 0.0f, scale.getEntry(2), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	float relMatrix[16] =
	{
		relativeTransform.getEntry(0,0), relativeTransform.getEntry(0,1), relativeTransform.getEntry(0,2), relativeTransform.getEntry(0,3),
		relativeTransform.getEntry(1,0), relativeTransform.getEntry(1,1), relativeTransform.getEntry(1,2), relativeTransform.getEntry(1,3),
		relativeTransform.getEntry(2,0), relativeTransform.getEntry(2,1), relativeTransform.getEntry(2,2), relativeTransform.getEntry(2,3),
		relativeTransform.getEntry(3,0), relativeTransform.getEntry(3,1), relativeTransform.getEntry(3,2), relativeTransform.getEntry(3,3)
	};

	// set the model-to-world transformation
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMultMatrixf(transMatrix);
	glMultMatrixf(rotMatrix);
	glMultMatrixf(scaleMatrix);
	glMultMatrixf(relMatrix);
	renderSpecific();
	glPopMatrix();
}
void Entity::setRelativeTransform(Matrix44f matIn) {
	relativeTransform = matIn;
}
Matrix44f Entity::getRelativeTransform() {
	return relativeTransform;
}