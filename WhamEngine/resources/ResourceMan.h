#ifndef WE_RESMAN_H
#define WE_RESMAN_H

#include <string>
#include <vector>
#include "LoadedGeometry.h"
#include "Material.h"
#include "Texture.h"
#include "filesys/PoolAllocator.h"
#include "scene/Bone.h"
#include "scene/Node.h"
#include <assimp\anim.h>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\texture.h>

//Implemented as a Singleton class.
class ResourceMan
{
	public:
		static ResourceMan& getInstance() {
			static ResourceMan instance;
			return instance; //Return a reference only.
		}
		void startUp();
		void shutDown();
		bool LoadBmp24(const char* filename, int& riWidth, int& riHeight, unsigned char*& raucData);
		bool LoadMesh(const char* filename, LoadedGeometry*& meshOut);
		Texture* getTexture(std::string fileName);
		Material* getMaterial(std::string fileName);
	private:
		ResourceMan() : loadedTextures() {} //Make constructor private.
		ResourceMan(ResourceMan const&) = delete; //Disallow the copy constructor.
		void operator=(ResourceMan const&) = delete; //Disallow copies of the singleton.

		static const int MAX_NUM_TEXES = 100;
		std::vector<Texture> loadedTextures;//, PoolAllocator<Texture>
		int numTextures;
		Assimp::Importer myImp;

		Texture* loadTexture(aiTexture texIn);
		void buildSkeleton(aiNode* currAiNode, Bone* currBone, Bone** bonePile, int& countBones);
		Node* GetNode( std::string boneName, Node* rootNode );
};

#endif