#ifndef WE_FSYSMAN_H
#define WE_FSYSMAN_H

#include <string>
#include "resources\Material.h"
#include "scene\SceneGraph.h"

class FileSystemMan
{
private:
	FileSystemMan() {} //Make constructor private.
	FileSystemMan(FileSystemMan const&) = delete; //Disallow the copy constructor.
	void operator=(FileSystemMan const&) = delete; //Disallow copies of the singleton.

	//Texture declarations (temporary; should be moved to resource manager)
	Texture* boxTex;
	Texture* blankTex;
	Texture* brickTex;
	Texture* carpetTex;
	Texture* eyeTex;
	Texture* skyTex;
	Texture* wallTex;
	Texture* wallPicTex;

	Material* dullMat;
	Material* slimeMat;
	Material* shinyMat;
	Material* rShinyMat;
	Material* gShinyMat;
	Material* bShinyMat;
public:
	static FileSystemMan& getInstance() {
		static FileSystemMan instance;
		return instance; //Return a reference only.
	}
	void startUp();
	void shutDown();
	void loadLevel( std::string fileName );
};
#endif