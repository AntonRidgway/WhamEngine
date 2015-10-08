#include "SixDOFSpatial.h"

SixDOFSpatial::SixDOFSpatial() : vecDir(1.0, 0.0, 1.0), vecUp(0.0, 1.0, 0.0), vecRight(0.0, 0.0, -1.0), totalRot(1.0f, 0.0f, 0.0f, 0.0f) {
	vecDir.normalizeIn();
	vecUp.normalizeIn();
	vecRight.normalizeIn();
	totalRot.normalizeIn();
}
SixDOFSpatial::SixDOFSpatial(float lx, float ly, float lz,
	float dx, float dy, float dz,
	float ux, float uy, float uz,
	float rx, float ry, float rz,
	float qw, float qx, float qy, float qz) :
	vecDir(dx, dy, dz), vecUp(ux, uy, uz), vecRight(rx, ry, rz), totalRot(qw, qx, qy, qz) {}
SixDOFSpatial::SixDOFSpatial(Vector3f locIn, Vector3f dirIn, Vector3f upIn, Vector3f rightIn, Quaternionf rotIn) {

}
void SixDOFSpatial::yaw(float f) //z-axis rotation
{
	for (int i = 0; i < 3; i++)
	{
		temp0[i] = Mathf::Cos(f)*vecRight.getEntry(i) - Mathf::Sin(f)*vecDir.getEntry(i);
		temp1[i] = Mathf::Cos(f)*vecDir.getEntry(i) + Mathf::Sin(f)*vecRight.getEntry(i);
	}
	Vector3f newRight(temp0);
	Vector3f newDir(temp1);
	vecRight = newRight;
	vecDir = newDir;
}
void SixDOFSpatial::pitch(float f)
{
	for (int i = 0; i < 3; i++)
	{
		temp0[i] = Mathf::Cos(f)*vecDir.getEntry(i) + sinf(f)*vecUp.getEntry(i);
		temp1[i] = cosf(f)*vecUp.getEntry(i) - sinf(f)*vecDir.getEntry(i);
	}
	Vector3f newDir(temp0);
	Vector3f newUp(temp1);
	vecDir = newDir;
	vecUp = newUp;
}
void SixDOFSpatial::roll(float f)
{
	for (int i = 0; i < 3; i++)
	{
		temp0[i] = cosf(f)*vecRight.getEntry(i) + sinf(f)*vecUp.getEntry(i);
		temp1[i] = cosf(f)*vecUp.getEntry(i) - sinf(f)*vecRight.getEntry(i);
	}
	Vector3f newRight(temp0);
	Vector3f newUp(temp1);
	vecRight = newRight;
	vecUp = newUp;
}
void SixDOFSpatial::rotate(Quaternionf q)
{
	q.normalizeIn();
	Vector3f qVec(q.getX(), q.getY(), q.getZ());
	Vector3f dirNew = vecDir.add(qVec.multiply(2)).cross(qVec.cross(vecDir).add(vecDir.multiply(q.getW())));
	vecDir = dirNew;
	Vector3f upNew = vecUp.add(qVec.multiply(2)).cross(qVec.cross(vecUp).add(vecUp.multiply(q.getW())));
	vecUp = upNew;
	Vector3f rightNew = vecRight.add(qVec.multiply(2)).cross(qVec.cross(vecRight).add(vecRight.multiply(q.getW())));
	vecRight = rightNew;
}
void SixDOFSpatial::transForward(float m) {
	translate(vecDir.multiply(m));
}
void SixDOFSpatial::transRight(float m) {
	translate(vecRight.multiply(m));
}
Vector3f SixDOFSpatial::getDir() {
	return vecDir;
}
Vector3f SixDOFSpatial::getUp() {
	return vecUp;
}
Vector3f SixDOFSpatial::getRight() {
	return vecRight;
}