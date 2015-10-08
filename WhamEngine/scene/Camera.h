#ifndef WE_CAMERA_H
#define WE_CAMERA_H

#include "Spatial.h"

class Camera : public Spatial
{
private:
	//viewport parameters
	const double CAM_FOV = 100.;
	const double CAM_ZNEAR = 1.0;
	const double CAM_ZFAR = 100.;
	double aspectRatio;

public:
	Camera(int wIn, int hIn, std::string name = "camera");
	Camera(int wIn, int hIn, Vector3f loc, Matrix44f rot, std::string name = "camera");
	Camera(int wIn, int hIn, float lx, float ly, float lz,
		float dx, float dy, float dz,
		float ux, float uy, float uz,
		float rx, float ry, float rz, std::string name = "camera");
	void setAspectRatio(double ar);
	void updateGLCam();
};

#endif