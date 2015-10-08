#pragma once
#ifndef SDOFSPAT_H
#define SDOFSPAT_H

#include "Spatial.h"
#include "math/Math.h"
#include "math/Quaternion.h"
#include "math/Vector.h"

class SixDOFSpatial : public Spatial {
protected:
	Vector3f vecDir, vecUp, vecRight; //Orientation Vectors
	Quaternionf totalRot; //Rotation Quaternion
	float temp0[3]; float temp1[3]; //Helper arrays for rotation speed
public:
	SixDOFSpatial();
	SixDOFSpatial(float lx, float ly, float lz,
		float dx, float dy, float dz,
		float ux, float uy, float uz,
		float rx, float ry, float rz,
		float qw, float qx, float qy, float qz);
	SixDOFSpatial(Vector3f locIn, Vector3f dirIn, Vector3f upIn, Vector3f rightIn, Quaternionf rotIn);
	void yaw(float f);
	void pitch(float f);
	void roll(float f);
	void rotate(Quaternionf q);
	void transForward(float m);
	void transRight(float m);
	Vector3f getDir();
	Vector3f getUp();
	Vector3f getRight();
};

#endif