#include "stdafx.h"
#include "HUDText.h"

HUDText::HUDText(std::string textIn, ColorA colorIn, float xIn, float yIn) : text(textIn), color(colorIn), x(xIn), y(yIn) {}
void HUDText::render() {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2f(x, y);
	glColor4f(color.getR(), color.getG(), color.getB(), color.getA());
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)text.c_str());
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}
std::string HUDText::getText() {
	return text;
}
void HUDText::setText(std::string newText) {
	text = newText;
}