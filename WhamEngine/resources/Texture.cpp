#include "stdafx.h"
#include <Windows.h>
#include <gl\GL.h>
#include <string>
#include "Texture.h"

Texture::Texture( std::string nameIn, unsigned char* imageIn, int wid, int hgt )
{
	name = nameIn;
	imageData = imageIn;
	imageW = wid;
	imageH = hgt;
	gfxID = 0;
}
Texture::~Texture()
{
	if(gfxID > 0)
		glDeleteTextures((GLsizei)1,&gfxID);
	//if(imageData != NULL)
	//	delete imageData;
}

int Texture::getWidth() const
{
	return imageW;
}
int Texture::getHeight() const
{
	return imageH;
}
unsigned char* Texture::getData() const
{
	return imageData;
}
GLuint Texture::getGfxID() const
{
	return gfxID;
}
void Texture::setGfxID( GLuint newID )
{
	gfxID = newID;
}
std::string Texture::getName() const
{
	return name;
}