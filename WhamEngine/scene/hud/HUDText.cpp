#include "stdafx.h"
#include "HUDText.h"

HUDText::HUDText(std::string textIn, ColorA colorIn, float xIn, float yIn) : text(textIn), color(colorIn), x(xIn), y(yIn) {}
void HUDText::render() {
	glRasterPos2f(x, y);
	glColor4f(color.getR(), color.getG(), color.getB(), color.getA());
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)text.c_str());
}
std::string HUDText::getText() {
	return text;
}
void HUDText::setText(std::string newText) {
	text = newText;
}