#ifndef WE_MATERIAL_H
#define WE_MATERIAL_H

#include <Windows.h>
#include <GL/GLU.h>

class Material
{
private:
	GLfloat* emissive;
	GLfloat* ambient;
	GLfloat* diffuse;
	GLfloat* specular;
	float shininess;
public:
	Material();
	Material( float er, float eg, float eb, float ea,
			  float ar, float ag, float ab, float aa,
			  float dr, float dg, float db, float da,
			  float sr, float sg, float sb, float sa,
			  float sh);
	Material( const Material& m );
	~Material();
	GLfloat* getEmissive() const;
	GLfloat getEmissive( int i ) const;
	GLfloat* getAmbient() const;
	GLfloat getAmbient( int i ) const;
	GLfloat* getDiffuse() const;
	GLfloat getDiffuse( int i ) const;
	GLfloat* getSpecular() const;
	GLfloat getSpecular( int i ) const;
	float getShininess() const;
	void setEmissive(float r, float g, float b, float a);
	void setAmbient(float r, float g, float b, float a);
	void setDiffuse(float r, float g, float b, float a);
	void setSpecular(float r, float g, float b, float a);
	void setShininess(float s);
};

#endif