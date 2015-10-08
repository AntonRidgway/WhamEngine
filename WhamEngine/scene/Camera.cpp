#include "stdafx.h"

#include <Windows.h>
#include <gl\GLU.h>
#include "Camera.h"
#include "math/Math.h"

Camera::Camera(int wIn, int hIn, std::string name) : Spatial(name) {
	// Adjust the viewport so that it draws to the entire screen, and adjust the camera perspective.
	glViewport(0, 0, wIn, hIn);
	setAspectRatio(((double)wIn) / hIn);
	updateGLCam();
}
Camera::Camera(int wIn, int hIn, Vector3f loc, Matrix44f rot, std::string name) : Spatial(loc, rot, 1.0f, name) {
	// Adjust the viewport so that it draws to the entire screen, and adjust the camera perspective.
	glViewport(0, 0, wIn, hIn);
	setAspectRatio(((double)wIn) / hIn);
	updateGLCam();
}
Camera::Camera(int wIn, int hIn, float lx, float ly, float lz,
	float dx, float dy, float dz,
	float ux, float uy, float uz,
	float rx, float ry, float rz, std::string name) :
	Spatial(Vector3f(lx, ly, lz),
		Matrix44f(rx, ry, rz, 0, ux, uy, uz, 0, dx, dy, dz, 0, 0, 0, 0, 1), 1.0f, name) {
	glViewport(0, 0, wIn, hIn);
	setAspectRatio(((double)wIn) / hIn);
	updateGLCam();
}
void Camera::updateGLCam()
{
	//set the camera world coordinate system
	Vector3f camLoc = getTranslation();
	Vector3f vecUp = getUp();
	Vector3f vecDir = getForward();
	Vector3f lookAt = camLoc.add(vecDir);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double vertAngle = CAM_FOV / aspectRatio;
	gluPerspective(vertAngle, aspectRatio, CAM_ZNEAR, CAM_ZFAR);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camLoc.getEntry(0), camLoc.getEntry(1), camLoc.getEntry(2),
		lookAt.getEntry(0), lookAt.getEntry(1), lookAt.getEntry(2),
		vecUp.getEntry(0), vecUp.getEntry(1), vecUp.getEntry(2));
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
//Adjust the perspective according to changes and update the camera orientation.
void Camera::setAspectRatio(double ar) {
	aspectRatio = ar;
}