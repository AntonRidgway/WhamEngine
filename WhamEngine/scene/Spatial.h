#ifndef WE_SPAT_H
#define WE_SPAT_H

#include <string>
#include "math/Matrix.h"
#include "math/Quaternion.h"

class Spatial
{
private:
	Vector3f translation;
	Matrix44f rotation;	//the spatial's transformation relative to its parent node.
	float scale;
	std::string name;
public:
	Spatial(std::string nameIn = "null");
	Spatial(Vector3f translationIn, Matrix44f rotationIn, float scaleIn = 1.0f, std::string nameIn = "null");
	Spatial(Spatial& s);

	void translate(Vector3f v);
	void translate (float x, float y, float z);
	void translateX(float amt);
	void translateY(float amt);
	void translateZ(float amt);
	void translateForward(float m);
	void translateRight(float m);
	void translateUp(float m);
	void rotate(Quaternionf q);
	void rotate(float w, float x, float y, float z);
	void rotateX(float amt);
	void rotateY(float amt);
	void rotateZ(float amt);
	void yaw(float f);
	void pitch(float f);
	void roll(float f);
	void scaleBy(float f);

	Vector3f getTranslation();
	Matrix44f getRotation();
	Matrix44f getTransformation();
	Vector3f getForward();
	Vector3f getUp();
	Vector3f getRight();
	float getScale();
	std::string getName() const;
	
	void setTranslation(Vector3f v);
	void setTranslation(float x, float y, float z);
	void setRotation(Matrix44f m);
	void setRotation(Quaternionf q);
	void setRotation( float w, float x, float y, float z );
	void setRotation( float a1, float a2, float a3,
					  float b1, float b2, float b3,
					  float c1, float c2, float c3 );
	void setTransformation(Matrix44f m);
	void setTransformation(float a1, float a2, float a3, float a4,
		float b1, float b2, float b3, float b4,
		float c1, float c2, float c3, float c4,
		float d1, float d2, float d3, float d4);
	void setYaw(Vector3f newForward, Vector3f newRight);
	void setPitch(Vector3f newForward, Vector3f newUp);
	void setRoll(Vector3f newUp, Vector3f newRight);
	void setScale( float scaleIn );
	void setName (std::string newName);
};

#endif