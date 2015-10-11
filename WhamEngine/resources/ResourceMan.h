#ifndef WE_FSYSMAN_H
#define WE_FSYSMAN_H

#include "PoolAllocator.h"
#include "resources/LoadedGeometry.h"
#include "resources/Material.h"
#include "resources/Texture.h"
#include "scene/entities/Box.h"
#include "scene/entities/Geometry.h"
#include "scene/entities/Pyramid.h"
#include "scene/entities/Quad.h"
#include "scene/entities/Quadric.h"
#include "scene/Scene.h"
#include "scene/StateMan.h"
#include <string>
#include <vector>
#include <fstream>
#include <streambuf>
#include "scene/animation/Bone.h"
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

class ResourceMan
{
private:
	ResourceMan() {} //Make constructor private.
	ResourceMan(ResourceMan const&) = delete; //Disallow the copy constructor.
	void operator=(ResourceMan const&) = delete; //Disallow copies of the singleton.
	
	static const int WINDOWS_MAX_FILENAME = 260;
	static const std::string WINDOWS_FILE_SEPARATOR;
	static const int MAX_NUM_TEXES = 100;

	Assimp::Importer myImp;
	std::map<std::string, Texture*> textureMap;
	std::map<std::string, Material*> materialMap;
	std::map<std::string, TriMesh*> meshMap;
	std::map<std::string, Geometry*> geometryMap;
	std::map<std::string, Light*> lightMap;

	bool LoadBmp24(const char* filename, int& riWidth, int& riHeight, unsigned char*& raucData);
	bool LoadMesh(const char* filename, LoadedGeometry*& meshOut);
	Texture* loadTexture(std::string fileName);
	Texture* loadAssimpTexture(aiTexture texIn);
	void buildSkeleton(aiNode* currAiNode, Bone* currBone, Bone** bonePile, int& countBones);
	bool doesFileExist(std::string fileName);
	std::string findFileAbsolute(std::string fileName);
	
public:
	static ResourceMan& getInstance() {
		static ResourceMan instance;
		return instance; //Return a reference only.
	}
	void startUp();
	void shutDown();
	void loadLevel( std::string fileName, Scene* scene );
};
#endif