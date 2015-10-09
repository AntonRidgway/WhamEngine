#ifndef WE_LIGHT_H
#define WE_LIGHT_H

#include "Color.h"
#include "scene/Spatial.h"

class Light : public Spatial
{
protected:
	ColorA* ambient;
	ColorA* diffuse;
	ColorA* specular;
	Vector4f* position;

	float cAttenuation;
	float lAttenuation;
	float qAttenuation;

	//spotlight variables
	Vector3f* direction;
	float exponent;
	float cutoff;

	int lightType;
public:
	Light( float ar = 0.2f, float ag = 0.2f, float ab = 0.2f, float aa = 1.0f,
			  float dr = 0.8f, float dg = 0.8f, float db = 0.8f, float da = 1.0f,
			  float sr = 0.5f, float sg = 0.5f, float sb = 0.5f, float sa = 1.0f,
			  float px = 0.0f, float py = 0.0f, float pz = 0.0f,
			  float ca = 1.0f, float la = 0.0f, float qa = 0.0f);
	~Light();
	ColorA* getAmbient();
	ColorA* getDiffuse();
	ColorA* getSpecular();
	Vector4f* getPosition();
	float getAttenuation(int which);
	int getLightType();

	Vector3f* getDirection();
	float getExponent();
	float getCutoff();
};
class DirLight : public Light
{
public:
	DirLight( float ar = 0.2f, float ag = 0.2f, float ab = 0.2f, float aa = 1.0f,
			  float dr = 0.8f, float dg = 0.8f, float db = 0.8f, float da = 1.0f,
			  float sr = 0.5f, float sg = 0.5f, float sb = 0.5f, float sa = 1.0f,
			  float dx = 0.0f, float dy = 0.0f, float dz = -1.0f);
	~DirLight();
};
class PointLight : public Light
{
public:
	PointLight( float ar = 0.2f, float ag = 0.2f, float ab = 0.2f, float aa = 1.0f,
				float dr = 0.8f, float dg = 0.8f, float db = 0.8f, float da = 1.0f,
				float sr = 0.5f, float sg = 0.5f, float sb = 0.5f, float sa = 1.0f,
				float px = 0.0f, float py = 0.0f, float pz = 0.0f,
				float ca = 1.0f, float la = 0.0f, float qa = 0.0f);
	~PointLight();
};
class SpotLight : public Light
{
public:
	SpotLight( float ar = 0.2f, float ag = 0.2f, float ab = 0.2f, float aa = 1.0f,
				float dr = 0.8f, float dg = 0.8f, float db = 0.8f, float da = 1.0f,
				float sr = 0.5f, float sg = 0.5f, float sb = 0.5f, float sa = 1.0f,
				float px = 0.0f, float py = 0.0f, float pz = 0.0f,
				float dx = 0.0f, float dy = 0.0f, float dz = -1.0f, float ex = 15.0f, float co = 30.0f,
				float ca = 1.0f, float la = 0.0f, float qa = 0.0f
				);
	~SpotLight();
};

#endif