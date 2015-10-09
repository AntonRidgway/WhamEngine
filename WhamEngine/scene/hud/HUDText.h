#ifndef WE_HUDTEXT_H
#define WE_HUDTEXT_H

#include "Windows.h"
#include <gl/GL.h>
#include <gl/freeglut.h>
#include <string>
#include "scene/lights/Color.h"

class HUDText
{
private:
	std::string text;
	float x, y;
	ColorA color;
public:
	HUDText(std::string textIn, ColorA colorIn, float xIn = 0, float yIn = 0);
	void render();
	std::string getText();
	void setText(std::string newText);
};

#endif