#include "stdafx.h"

#include "Color.h"

//-------------------------------------------------------------------------------------------------
//Color

Color::Color (float r, float g, float b)
{
	data = new float[3];
	data[0] = r;
	data[1] = g;
	data[2] = b;
}
Color::Color (const Color& c)
{
	data = new float[3];
	data[0] = c.getR();
	data[1] = c.getG();
	data[2] = c.getB();
}
Color::~Color()
{
	delete[] data;
}
float Color::getR() const { return data[0]; }
float Color::getG() const { return data[1]; }
float Color::getB() const { return data[2]; }
float* Color::getData() const { return data; }
void Color::setValues( float r, float g, float b )
{
	data[0] = r;
	data[1] = g;
	data[2] = b;
}


//-------------------------------------------------------------------------------------------------
//ColorA

ColorA::ColorA (float r, float g, float b, float a)
{
	data = new float[4];
	data[0] = r;
	data[1] = g;
	data[2] = b;
	data[3] = a;
}
ColorA::ColorA (const ColorA& c)
{
	data = new float[4];
	data[0] = c.getR();
	data[1] = c.getG();
	data[2] = c.getB();
	data[3] = c.getA();
}
ColorA::~ColorA()
{
	delete[] data;
}
float ColorA::getR() const { return data[0]; }
float ColorA::getG() const { return data[1]; }
float ColorA::getB() const { return data[2]; }
float ColorA::getA() const { return data[3]; }
float* ColorA::getData() const { return data; }
void ColorA::setValues( float r, float g, float b, float a )
{
	data[0] = r;
	data[1] = g;
	data[2] = b;
	data[3] = a;
}