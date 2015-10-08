#ifndef WE_TEXTURE_H
#define WE_TEXTURE_H

#include <string>
#include <Windows.h>
#include <gl\GL.h>
#include "Texture.h"

class Texture
{
private:
	int imageW;
	int imageH;
	unsigned char* imageData;
	GLuint gfxID;
	std::string name;

public:
	Texture( std::string nameIn, unsigned char* imageIn, int wid, int hgt );
	~Texture();
	int getWidth() const;
	int getHeight() const;
	unsigned char* getData() const;
	GLuint getGfxID() const;
	void setGfxID(GLuint newID);
	std::string getName() const;
};

#endif