#include "stdafx.h"
#include "Entity.h"

Entity::Entity(std::string nameIn) : Spatial(nameIn), relTranslation(0.f,0.f,0.f), relRotation(Matrix44f::identity) {}
Entity::Entity(Vector3f translationIn, Matrix44f rotationIn, Vector3f scaleIn, std::string nameIn) : Spatial(translationIn, rotationIn, scaleIn, nameIn), relTranslation(0.f, 0.f, 0.f), relRotation(Matrix44f::identity) {};
Entity::Entity(Entity& e) : Spatial(e), relTranslation(0.f, 0.f, 0.f), relRotation(Matrix44f::identity) {};
void Entity::render() {
	Matrix44f sRotation = getRotation();
	float sRotMatrix[16] =
	{
		sRotation.getEntry(0,0), sRotation.getEntry(0,1), sRotation.getEntry(0,2), 0.0f,
		sRotation.getEntry(1,0), sRotation.getEntry(1,1), sRotation.getEntry(1,2), 0.0f,
		sRotation.getEntry(2,0), sRotation.getEntry(2,1), sRotation.getEntry(2,2), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	Matrix44f eRotation = getRelativeRotation();
	float eRotMatrix[16] =
	{
		eRotation.getEntry(0,0), eRotation.getEntry(0,1), eRotation.getEntry(0,2), 0.0f,
		eRotation.getEntry(1,0), eRotation.getEntry(1,1), eRotation.getEntry(1,2), 0.0f,
		eRotation.getEntry(2,0), eRotation.getEntry(2,1), eRotation.getEntry(2,2), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	Vector3f sTranslation = getTranslation();
	float sTransMatrix[16] =
	{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		sTranslation.getEntry(0), sTranslation.getEntry(1), sTranslation.getEntry(2), 1.0f
	};
	Vector3f eTranslation = getRelativeTranslation();
	float eTransMatrix[16] =
	{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		eTranslation.getEntry(0), eTranslation.getEntry(1), eTranslation.getEntry(2), 1.0f
	};
	Vector3f scale = getScale();
	float scaleMatrix[16] =
	{
		scale.getEntry(0), 0.0f, 0.0f, 0.0f,
		0.0f, scale.getEntry(1), 0.0f, 0.0f,
		0.0f, 0.0f, scale.getEntry(2), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	// set the model-to-world transformation
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMultMatrixf(sTransMatrix);
	glMultMatrixf(sRotMatrix);
	glMultMatrixf(scaleMatrix);
	glMultMatrixf(eTransMatrix);
	glMultMatrixf(eRotMatrix);
	renderSpecific();
	glPopMatrix();
}
void Entity::setRelativeTranslation(Vector3f transIn) {
	relTranslation = transIn;
}
Vector3f Entity::getRelativeTranslation() {
	return relTranslation;
}
void Entity::setRelativeRotation(Matrix44f rotIn) {
	relRotation = rotIn;
}
Matrix44f Entity::getRelativeRotation() {
	return relRotation;
}