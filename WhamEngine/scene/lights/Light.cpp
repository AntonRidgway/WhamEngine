#include "stdafx.h"

#include "../math/Vector.h"
#include "Color.h"
#include "Light.h"

Light::Light(float ar, float ag, float ab, float aa,
				   float dr, float dg, float db, float da,
				   float sr, float sg, float sb, float sa,
				   float px, float py, float pz,
				   float ca, float la, float qa)
{
	ambient = new ColorA(ar,ag,ab,aa);
	diffuse = new ColorA(dr,dg,db,da);
	specular = new ColorA(sr,sg,sb,sa);
	position = new Vector4f(px,py,pz,1.0f);
	cAttenuation = ca;
	lAttenuation = la;
	qAttenuation = qa;
	lightType = 0;
}
Light::~Light()
{
	delete ambient;
	delete diffuse;
	delete specular;
	delete position;
}
ColorA* Light::getAmbient()
{
	return ambient;
}
ColorA* Light::getDiffuse()
{
	return diffuse;
}
ColorA* Light::getSpecular()
{
	return specular;
}
Vector4f* Light::getPosition()
{
	return position;
}
float Light::getAttenuation(int which)
{
	if(which == 1) return lAttenuation;
	else if (which == 2) return qAttenuation;
	else return cAttenuation;
}
int Light::getLightType()
{
	return lightType;
}
Vector3f* Light::getDirection()
{
	return direction;
}
float Light::getExponent()
{
	return exponent;
}
float Light::getCutoff()
{
	return cutoff;
}

//Note that directional lights disregard attenuation
DirLight::DirLight(float ar, float ag, float ab, float aa,
				   float dr, float dg, float db, float da,
				   float sr, float sg, float sb, float sa,
				   float dx, float dy, float dz)
		 :Light(ar,ag,ab,aa,
				   dr,dg,db,da,
				   sr,sg,sb,sa,
				   dx,dy,dz)
{
	position->getArray()[3] = 0.0f;
	lightType = 1;
}
DirLight::~DirLight()
{
}
PointLight::PointLight(float ar, float ag, float ab, float aa,
				   float dr, float dg, float db, float da,
				   float sr, float sg, float sb, float sa,
				   float px, float py, float pz,
				   float ca, float la, float qa):
				Light(ar,ag,ab,aa,
						 dr,dg,db,da,
						 sr,sg,sb,sa,
						 px,py,pz,
						 ca,la,qa)
{
	position->getArray()[3] = 1.0f;
	lightType = 2;
}
PointLight::~PointLight()
{
	lightType = 3;
}

SpotLight::SpotLight( float ar, float ag, float ab, float aa,
				float dr, float dg, float db, float da,
				float sr, float sg, float sb, float sa,
				float px, float py, float pz,
				float dx, float dy, float dz, float ex, float co,
				float ca, float la, float qa) :
				Light(ar,ag,ab,aa,
						 dr,dg,db,da,
						 sr,sg,sb,sa,
						 px,py,pz,
						 ca,la,qa)
{
	direction = new Vector3f(dx,dy,dz);
	exponent = ex;
	cutoff = co;
}
SpotLight::~SpotLight()
{
	delete direction;
}