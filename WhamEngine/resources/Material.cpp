#include "stdafx.h"
#include "Material.h"

Material::Material()
{
	emissive = new float[4];
	emissive[0] = 0.0f;	emissive[1] = 0.0f;	emissive[2] = 0.0f;	emissive[3] = 1.0f;
	ambient = new float[4];
	ambient[0] = 0.2f;	ambient[1] = 0.2f;	ambient[2] = 0.2f;	ambient[3] = 1.0f;
	diffuse = new float[4];
	diffuse[0] = 0.8f;	diffuse[1] = 0.8f;	diffuse[2] = 0.8f;	diffuse[3] = 1.0f;	
	specular = new float[4];
	specular[0] = 0.0f;	specular[1] = 0.0f;	specular[2] = 0.0f;	specular[3] = 1.0f;
	shininess = 64.0f;
}
Material::Material( float er, float eg, float eb, float ea,
			float ar, float ag, float ab, float aa,
			float dr, float dg, float db, float da,
			float sr, float sg, float sb, float sa,
			float sh)
{
	emissive = new float[4];
	emissive[0] = er;	emissive[1] = eg;	emissive[2] = eb;	emissive[3] = ea;
	ambient = new float[4];
	ambient[0] = ar;	ambient[1] = ag;	ambient[2] = ab;	ambient[3] = aa;
	diffuse = new float[4];
	diffuse[0] = dr;	diffuse[1] = dg;	diffuse[2] = db;	diffuse[3] = da;	
	specular = new float[4];
	specular[0] = sr;	specular[1] = sg;	specular[2] = sb;	specular[3] = sa;
	shininess = sh;
}
Material::Material( const Material& m )
{
	emissive = new float[4];
	ambient = new float[4];
	diffuse = new float[4];
	specular = new float[4];

	for( int i = 0; i < 4; i++ )
	{
		emissive[i] = m.getEmissive(i);
		ambient[i] = m.getAmbient(i);
		diffuse[i] = m.getDiffuse(i);
		specular[i] = m.getSpecular(i);
	}
	shininess = m.getShininess();
}
Material::~Material()
{
	delete emissive; 
	delete ambient;
	delete diffuse;
	delete specular;
}
GLfloat* Material::getEmissive() const
{
	return emissive;
}
GLfloat Material::getEmissive(int i) const
{
	if(i > -1 && i < 4)
		return emissive[i];
	else
		return 0.0f;
}
GLfloat* Material::getAmbient() const
{
	return ambient;
}
GLfloat Material::getAmbient(int i) const
{
	if(i > -1 && i < 4)
		return ambient[i];
	else
		return 0.0f;
}
GLfloat* Material::getDiffuse() const
{
	return diffuse;
}
GLfloat Material::getDiffuse( int i ) const
{
	if(i > -1 && i < 4)
		return diffuse[i];
	else
		return 0.0f;
}
GLfloat* Material::getSpecular() const
{
	return specular;
}
GLfloat Material::getSpecular( int i ) const
{
	if(i > -1 && i < 4)
		return specular[i];
	else
		return 0.0f;
}
float Material::getShininess() const
{
	return shininess;
}
void Material::setEmissive(float r, float g, float b, float a)
{
	emissive[0] = r;
	emissive[1] = g;
	emissive[2] = b;
	emissive[3] = a;
}
void Material::setAmbient(float r, float g, float b, float a)
{
	ambient[0] = r;
	ambient[1] = g;
	ambient[2] = b;
	ambient[3] = a;
}
void Material::setDiffuse(float r, float g, float b, float a)
{
	diffuse[0] = r;
	diffuse[1] = g;
	diffuse[2] = b;
	diffuse[3] = a;
}
void Material::setSpecular(float r, float g, float b, float a)
{
	specular[0] = r;
	specular[1] = g;
	specular[2] = b;
	specular[3] = a;
}
void Material::setShininess(float s)
{
	shininess = s;
}