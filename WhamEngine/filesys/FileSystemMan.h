#ifndef WE_FSYSMAN_H
#define WE_FSYSMAN_H

#include "PoolAllocator.h"
#include "resources/LoadedGeometry.h"
#include "resources/Material.h"
#include "resources/Texture.h"
#include "scene/Box.h"
#include "scene/Pyramid.h"
#include "scene/Quad.h"
#include "scene/Quadric.h"
#include "scene/SceneGraph.h"
#include "scene/StateMan.h"
#include <string>
#include <vector>
#include <fstream>
#include <streambuf>
#include "scene/Bone.h"
#include "scene/Node.h"
#include <assimp\ai_assert.h>
#include <assimp\anim.h>
#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>
#include <assimp\scene.h>
#include <assimp\texture.h>
#include <RapidXML\rapidxml.hpp>

#include <direct.h>
#include <stdlib.h>
#include <stdio.h>
#include <iterator>
#include <iostream>
#include <sstream>

class FileSystemMan
{
private:
	FileSystemMan() {} //Make constructor private.
	FileSystemMan(FileSystemMan const&) = delete; //Disallow the copy constructor.
	void operator=(FileSystemMan const&) = delete; //Disallow copies of the singleton.
	
	Assimp::Importer myImp;

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
	void loadLevel( std::string fileName, SGRoot* graph );
	bool LoadBmp24(const char* filename, int& riWidth, int& riHeight, unsigned char*& raucData);
	bool LoadMesh(const char* filename, LoadedGeometry*& meshOut);
	Texture* getTexture(std::string fileName);
	Material* getMaterial(std::string fileName);

private:
	static const int WINDOWS_MAX_FILENAME = 260;
	static const std::string WINDOWS_FILE_SEPARATOR;
	static const int MAX_NUM_TEXES = 100;
	std::vector<Texture> loadedTextures;//, PoolAllocator<Texture>
	int numTextures;

	bool doesFileExist(std::string fileName);
	std::string findFileAbsolute(std::string fileName);
	Texture* loadTexture(aiTexture texIn);
	void buildSkeleton(aiNode* currAiNode, Bone* currBone, Bone** bonePile, int& countBones);
	Node* GetNode(std::string boneName, Node* rootNode);
};
#endif