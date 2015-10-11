#include "stdafx.h"
#include "Spatial.h"
#include "math/Math.h"

Spatial::Spatial(std::string nameIn) :
	translation(0.0f, 0.0f, 0.0f),
	rotation(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f),
	scale(1.0f), name(nameIn) {};
Spatial::Spatial(Vector3f translationIn, Matrix44f rotationIn, float scaleIn, std::string nameIn ) :
	translation(translationIn), rotation(rotationIn), scale(scaleIn), name(nameIn) {};
Spatial::Spatial(Spatial& s) :
	translation(s.getTranslation()), rotation(s.getRotation()), scale(s.getScale()), name(s.getName()) {};
void Spatial::translate(Vector3f v) {
	translation.addIn(v);
}
void Spatial::translate (float x, float y, float z) {
	translation.addIn(Vector3f(x,y,z));
}
void Spatial::translateX(float amt) {
	translate(amt, 0., 0.);
}
void Spatial::translateY(float amt) {
	translate(0., amt, 0.);
}
void Spatial::translateZ(float amt) {
	translate(0., 0., amt);
}
void Spatial::translateForward(float m) {
	translate(getForward().multiply(m));
}
void Spatial::translateRight(float m) {
	translate(getRight().multiply(m));
}
void Spatial::translateUp(float m) {
	translate(getUp().multiply(m));
}
void Spatial::rotate(Quaternionf q) {
	rotate(q.getW(), q.getX(), q.getY(), q.getZ());
}
void Spatial::rotate( float w, float x, float y, float z )
{
	Matrix44f rotMat(	1-2*(y*y-z*z),	2*(x*y+w*z),	2*(x*z-w*y),	0,
						2*(x*y-w*z),	1-2*(x*x-z*z),	2*(y*z-w*x),	0,
						2*(x*z+w*y),	2*(y*z-w*z),	1-2*(x*x-y*y),	0,
						0,				0,				0,				1);
	rotation.multiplyIn(rotMat);
}
void Spatial::rotateX( float amt )
{
	Matrix44f rotMat (	1,	0,			0,			0,
						0, Mathf::Cos(amt),	-Mathf::Sin(amt), 0,
						0, Mathf::Sin(amt), Mathf::Cos(amt),	0,
						0,	0,			0,			1);
	rotation.multiplyIn(rotMat);
}
void Spatial::rotateY( float amt )
{
	Matrix44f rotMat (	Mathf::Cos(amt),	0, Mathf::Sin(amt),	0,
						0,			1,	0,			0,
						-Mathf::Sin(amt),	0, Mathf::Cos(amt),	0,
						0,	0,			0,			1);
	rotation.multiplyIn(rotMat);
}
void Spatial::rotateZ( float amt )
{
	float cf = Mathf::Cos(amt);
	float sf = Mathf::Sin(amt);
	Matrix44f rotMat (	cf,		-sf,	0.0f,	0.0f,
						sf,		cf,		0.0f,	0.0f,
						0.0f,	0.0f,	1.0f,	0.0f,
						0.0f,	0.0f,	0.0f,	1.0f);
	rotation.multiplyIn(rotMat);
}
void Spatial::yaw(float f) {
	Vector3f camDir = getForward();
	Vector3f camRight = getRight();
	float temp0[3], temp1[3];
	for (int i = 0; i < 3; i++)
	{
		temp0[i] = cosf(f)*camRight.getEntry(i) - sinf(f)*camDir.getEntry(i);
		temp1[i] = cosf(f)*camDir.getEntry(i) + sinf(f)*camRight.getEntry(i);
	}
	setYaw(temp1, temp0);
}
void Spatial::pitch(float f) {
	Vector3f camDir = getForward();
	Vector3f camUp = getUp();
	float temp0[3], temp1[3];
	for (int i = 0; i < 3; i++)
	{
		temp0[i] = cosf(f)*camDir.getEntry(i) + sinf(f)*camUp.getEntry(i);
		temp1[i] = cosf(f)*camUp.getEntry(i) - sinf(f)*camDir.getEntry(i);
	}
	setPitch(temp0, temp1);
}
void Spatial::roll(float f) {
	Vector3f camRight = getRight();
	Vector3f camUp = getUp();
	float temp0[3], temp1[3];
	for (int i = 0; i < 3; i++)
	{
		temp0[i] = cosf(f)*camRight.getEntry(i) + sinf(f)*camUp.getEntry(i);
		temp1[i] = cosf(f)*camUp.getEntry(i) - sinf(f)*camRight.getEntry(i);
	}
	setRoll(temp1,temp0);
	Vector3f newRight(temp0);
	Vector3f newUp(temp1);
}
void Spatial::scaleBy(float f) {
	scale *= f;
}


Vector3f Spatial::getTranslation() {
	return translation;
}
Matrix44f Spatial::getRotation() {
	return rotation;
}
Matrix44f Spatial::getTransformation() {
	return Matrix44f(rotation.getEntry(0, 0)*scale, rotation.getEntry(0, 1), rotation.getEntry(0, 2), 
						rotation.getEntry(0, 0)*translation.getEntry(0)*scale + rotation.getEntry(0, 1)*translation.getEntry(1)
						+ rotation.getEntry(0, 2)*translation.getEntry(2),
					rotation.getEntry(1, 0), rotation.getEntry(1, 1)*scale, rotation.getEntry(1, 2),
						rotation.getEntry(1, 0)*translation.getEntry(0) + rotation.getEntry(1, 1)*translation.getEntry(1)*scale
						+ rotation.getEntry(1, 2)*translation.getEntry(2),
					rotation.getEntry(2, 0), rotation.getEntry(2, 1), rotation.getEntry(2, 2)*scale,
						rotation.getEntry(2, 0)*translation.getEntry(0) + rotation.getEntry(2, 1)*translation.getEntry(1)
						+ rotation.getEntry(2, 2)*translation.getEntry(2)*scale,
					0.0f, 0.0f, 0.0f, 1.0f );
}
Vector3f Spatial::getForward() {
	//return Vector3f(rotation.getEntry(2, 0), rotation.getEntry(2, 1), rotation.getEntry(2, 2));
	return Vector3f(rotation.getEntry(0, 2), rotation.getEntry(1, 2), rotation.getEntry(2, 2));
}
Vector3f Spatial::getUp() {
	//return Vector3f(rotation.getEntry(1, 0), rotation.getEntry(1, 1), rotation.getEntry(1, 2));
	return Vector3f(rotation.getEntry(0, 1), rotation.getEntry(1, 1), rotation.getEntry(2, 1));
}
Vector3f Spatial::getRight() {
	//return Vector3f(rotation.getEntry(0, 0), rotation.getEntry(0, 1), rotation.getEntry(0, 2));
	return Vector3f(rotation.getEntry(0, 0), rotation.getEntry(1, 0), rotation.getEntry(2, 0));
}
float Spatial::getScale() {
	return scale;
}
std::string Spatial::getName() const {
	return name;
}

void Spatial::setTranslation(Vector3f v) {
	translation = Vector3f(v);
}
void Spatial::setTranslation( float x, float y, float z ) {
	translation = Vector3f(x,y,z);
}
void Spatial::setRotation(Matrix44f m) {
	rotation = Matrix44f(m);
}
void Spatial::setRotation(Quaternionf q) {
	setRotation(q.getW(), q.getX(), q.getY(), q.getZ());
}
void Spatial::setRotation( float w, float x, float y, float z )
{
	rotation.setEntry(0,0,1-2*(y*y-z*z));	rotation.setEntry(0,1,2*(x*y+w*z));		rotation.setEntry(0,2,2*(x*z-w*y));
	rotation.setEntry(1,0,2*(x*y-w*z));		rotation.setEntry(1,1,1-2*(x*x-z*z));	rotation.setEntry(1,2,2*(y*z+w*x));
	rotation.setEntry(2,0,2*(x*z+w*y));		rotation.setEntry(2,1,2*(y*z-x*w));		rotation.setEntry(2,2,1-2*(x*x-y*y));
}

void Spatial::setRotation( float a1, float a2, float a3,
						   float b1, float b2, float b3,
						   float c1, float c2, float c3 )
{
	rotation.setEntry(0,0,a1);	rotation.setEntry(0,1,a2);	rotation.setEntry(0,2,a3);
	rotation.setEntry(1,0,b1);	rotation.setEntry(1,1,b2);	rotation.setEntry(1,2,b3);
	rotation.setEntry(2,0,c1);	rotation.setEntry(2,1,c2);	rotation.setEntry(2,2,c3);
}
void Spatial::setTransformation(Matrix44f m) {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			rotation.setEntry(i, j, m.getEntry(i, j));
	Matrix44f translationMat = rotation.transpose().multiply(m);
	for (int i = 0; i < 3; i++)
		translation.setEntry(i, translationMat.getEntry(3,i));
	//TODO: This doesn't account for scale!
}
void Spatial::setTransformation(float a1, float a2, float a3, float a4,
	float b1, float b2, float b3, float b4,
	float c1, float c2, float c3, float c4,
	float d1, float d2, float d3, float d4) {
	setTransformation(Matrix44f(a1,a2,a3,a4,b1,b2,b3,b4,c1,c2,c3,c4,d1,d2,d3,d4));
}

void Spatial::setYaw(Vector3f newForward, Vector3f newRight) {
	rotation.setEntry(0, 2, newForward.getEntry(0)); rotation.setEntry(1, 2, newForward.getEntry(1)); rotation.setEntry(2, 2, newForward.getEntry(2)); //forward
	rotation.setEntry(0, 0, newRight.getEntry(0)), rotation.setEntry(1, 0, newRight.getEntry(1)), rotation.setEntry(2, 0, newRight.getEntry(2)); //right
}
void Spatial::setPitch(Vector3f newForward, Vector3f newUp) {
	rotation.setEntry(0, 2, newForward.getEntry(0)); rotation.setEntry(1, 2, newForward.getEntry(1)); rotation.setEntry(2, 2, newForward.getEntry(2)); //forward
	rotation.setEntry(0, 1, newUp.getEntry(0)); rotation.setEntry(1, 1, newUp.getEntry(1)); rotation.setEntry(2, 1, newUp.getEntry(2)); //up
}
void Spatial::setRoll(Vector3f newUp, Vector3f newRight) {
	rotation.setEntry(0, 1, newUp.getEntry(0)); rotation.setEntry(1, 1, newUp.getEntry(1)); rotation.setEntry(2, 1, newUp.getEntry(2)); //up
	rotation.setEntry(0, 0, newRight.getEntry(0)), rotation.setEntry(1, 0, newRight.getEntry(1)), rotation.setEntry(2, 0, newRight.getEntry(2)); //right
}
void Spatial::setScale( float scaleIn) {
	scale = scaleIn;
}
void Spatial::setName( std::string newName ) {
	name = newName;
}
