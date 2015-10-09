#ifndef WE_COLOR_H
#define WE_COLOR_H

//RGB Color Scheme
class Color
{
private:
	float* data; //imprecision is OK
public:
	Color (float r, float g, float b);
	Color (const Color& c);
	~Color();
	float getR() const;
	float getG() const;
	float getB() const;
	float* getData() const;
	void setValues( float r, float g, float b );
};

//RGBA Color Scheme
class ColorA
{
private:
	float* data; //imprecision is OK
public:
	ColorA (float r, float g, float b, float a);
	ColorA (const ColorA& c);
	~ColorA();
	float getR() const;
	float getG() const;
	float getB() const;
	float getA() const;
	float* getData() const;
	void setValues( float r, float g, float b, float a );
};

#endif