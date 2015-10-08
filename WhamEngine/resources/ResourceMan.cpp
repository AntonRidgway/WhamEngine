#include "stdafx.h"
#include <assimp\ai_assert.h>
#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>
#include "filesys\PoolAllocator.h"
#include "ResourceMan.h"

void ResourceMan::startUp()
{
	numTextures = 0;
}
void ResourceMan::shutDown()
{
	loadedTextures.clear();
}

/**
	* Loads the acFilename file into the parameter raucData,
	* and its dimensions are placed in riWidth and riHeight.
	*/
bool ResourceMan::LoadBmp24 (const char* filename, int& riWidth, int& riHeight, unsigned char*& raucData)
{
	//Load the bitmap
	HBITMAP hImage = (HBITMAP) LoadImageA(NULL,filename,IMAGE_BITMAP,0,0,LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if ( !hImage )
		return false;
		
	//Get the Device-Independent Bitmap data from the image (dimensions, color format, etc.)
	DIBSECTION dibSection;
	GetObject(hImage,sizeof(DIBSECTION),&dibSection);

	//Send bitmap image data back to the caller.
	riWidth = dibSection.dsBm.bmWidth;
	riHeight = dibSection.dsBm.bmHeight;
	int iQuantity = dibSection.dsBm.bmWidth*dibSection.dsBm.bmHeight;

	//Make sure it's a 24-bit image
	if ( dibSection.dsBm.bmBitsPixel != 24 )
		return false;

	//Windows BMPs are stored in BGR format, so reverse it to RGB format.
	unsigned char* aucSrc = (unsigned char*) dibSection.dsBm.bmBits;
	raucData = new unsigned char[3*iQuantity];
	for (int i = 0, i0 = 0, i1 = 1, i2 = 2; i < iQuantity; i++)
	{
		raucData[i0] = aucSrc[i2];
		raucData[i1] = aucSrc[i1];
		raucData[i2] = aucSrc[i0];
		i0 += 3;
		i1 += 3;
		i2 += 3;
	}
	return true;
}

//Much of this code is based on that at http://ogldev.atspace.co.uk/www/tutorial22/tutorial22.html
//and at http://ogldev.atspace.co.uk/www/tutorial38/tutorial38.html
bool ResourceMan::LoadMesh (const char* filename, LoadedGeometry*& meshOut)
{
	const aiScene* myScene;
	myScene = myImp.ReadFile( filename, aiProcess_CalcTangentSpace |
										aiProcess_Triangulate |
										aiProcess_JoinIdenticalVertices |
										aiProcess_SortByPType |
										aiProcess_GenSmoothNormals |
										aiProcess_GenUVCoords);
	//If the file could not be read, generate an error.
	if(!myScene)
	{
		MessageBox(NULL, L"Error: could not load scene.", L"LoadGeometry Error", MB_OK | MB_ICONINFORMATION);
		printf("Error: could not load scene '%s': %s\n", filename, myImp.GetErrorString());
		return FALSE;
	}
	if(!myScene->HasMeshes())
	{
		MessageBox(NULL, L"Error: no meshes in scene.", L"LoadGeometry Error", MB_OK | MB_ICONINFORMATION);
		printf("Error: No meshes in scene '%s': %s\n", filename, myImp.GetErrorString());
		return FALSE;
	}

	aiMatrix4x4 aiGIT = myScene->mRootNode->mTransformation;
	aiGIT.Inverse();
	Matrix44f* gIT = new Matrix44f(aiGIT.a1,aiGIT.a2,aiGIT.a3,aiGIT.a4,
								  aiGIT.b1,aiGIT.b2,aiGIT.b3,aiGIT.b4,
								  aiGIT.c1,aiGIT.c2,aiGIT.c3,aiGIT.c4,
								  aiGIT.d1,aiGIT.d2,aiGIT.d3,aiGIT.d4);

	//make structures for important data
	unsigned int numMeshes = myScene->mNumMeshes;			//Triangle Meshes
	TriMesh** meshesIn = new TriMesh*[numMeshes];
	unsigned int numTextures;								//Diffuse Textures
	Texture** texturesIn;
	unsigned int numMaterials;								//Materials
	Material** materialsIn;
	unsigned int numAnimations;								//Animations
	AnimClip** animationsIn;

	//---------------------------------------------------------------------------------------------
	//Load Meshes
	for (unsigned int i = 0; i < myScene->mNumMeshes; i++)
	{
		const aiMesh* myAiMesh = myScene->mMeshes[i];

		ai_assert(myAiMesh->HasPositions());
		ai_assert(myAiMesh->HasNormals());
		ai_assert(myAiMesh->HasFaces());

		GLfloat* posIn = new GLfloat[myAiMesh->mNumVertices*3];
		GLfloat* normIn = new GLfloat[myAiMesh->mNumVertices*3];
		GLfloat* uvIn = new GLfloat[myAiMesh->mNumVertices*2];
		GLuint* indIn = new GLuint[myAiMesh->mNumFaces*3];

		//load the positions, normals, and UV coordinates of a single vertex
		for(unsigned int j = 0; j < myAiMesh->mNumVertices; j++)
		{
			posIn[j*3]   = (myAiMesh->mVertices[j]).x;
			posIn[j*3+1] = (myAiMesh->mVertices[j]).y;
			posIn[j*3+2] = (myAiMesh->mVertices[j]).z;
			normIn[j*3] = (myAiMesh->mNormals[j]).x;
			normIn[j*3+1] = (myAiMesh->mNormals[j]).y;
			normIn[j*3+2] = (myAiMesh->mNormals[j]).z;
			if(myAiMesh->HasTextureCoords(0))
			{
				uvIn[j*2] = (myAiMesh->mTextureCoords[0][j]).x;
				uvIn[j*2+1] = (myAiMesh->mTextureCoords[0][j]).y;
			}
			else
			{
				uvIn[j*2] = 0;
				uvIn[j*2+1] = 0;
			}
		}

		//load the indices
		for(unsigned int j = 0; j < myAiMesh->mNumFaces; j++)
		{
			const aiFace myFace = myAiMesh->mFaces[j];
			ai_assert(myFace.mNumIndices == 3);
			indIn[j*3] = myFace.mIndices[0];
			indIn[j*3+1] = myFace.mIndices[1];
			indIn[j*3+2] = myFace.mIndices[2];
		}

		//-----------------------------------------------------------------------------------------
		// Load this mesh's bones

		Bone** bonesIn = new Bone*[myAiMesh->mNumBones];							//bones
		VertexBoneInfo* boneInfoIn = new VertexBoneInfo[myAiMesh->mNumVertices];	//bone weights

		//Set up a mapping to interpret Assimp's bone organization
		std::string* boneMappingNames = new std::string[myAiMesh->mNumBones];
		int* boneMappingIDs = new int[myAiMesh->mNumBones];
		int spotsFilled = 0;

		//Loop through the bones and map them uniquely into our array
		for(unsigned int j = 0; j < myAiMesh->mNumBones; j++)
		{ 
			int currBoneIndex;
			
			//See if the current Bone is already there
			int index = 0;
			std::string boneName(myAiMesh->mBones[j]->mName.C_Str());
			while(index < spotsFilled && boneMappingNames[index] != boneName)
			{
				index++;
			}
			if (index == spotsFilled) //This is a new bone; make a new entry.
			{
				currBoneIndex = spotsFilled; //index of the last open spot
				spotsFilled++;
				bonesIn[index] = new Bone();
			}
			else // The bone is already present
			{
				currBoneIndex = index;
			}
			boneMappingIDs[currBoneIndex] = currBoneIndex;

			//Copy bone name and orientation
			bonesIn[currBoneIndex]->setName(myAiMesh->mBones[j]->mName.C_Str());
			aiMatrix4x4 currMat = myAiMesh->mBones[j]->mOffsetMatrix;
			float* matA = new float[16];
			matA[0] = currMat.a1;	matA[0] = currMat.b1;	matA[0] = currMat.c1;	matA[0] = currMat.d1;
			matA[4] = currMat.a2;	matA[0] = currMat.b2;	matA[0] = currMat.c2;	matA[0] = currMat.d2;
			matA[8] = currMat.a3;	matA[0] = currMat.b3;	matA[0] = currMat.c3;	matA[0] = currMat.d3;
			matA[12] = currMat.a4;	matA[0] = currMat.b4;	matA[0] = currMat.c4;	matA[0] = currMat.d4;
			bonesIn[currBoneIndex]->setTransformation(matA);
			delete[] matA;

			//Get the bone weights per vertex
			for (unsigned int k = 0 ; k < myAiMesh->mBones[j]->mNumWeights ; k++)
			{
				unsigned int vertexID = myAiMesh->mBones[j]->mWeights[k].mVertexId;
				float weight = myAiMesh->mBones[j]->mWeights[k].mWeight;
				boneInfoIn[vertexID].addBoneData(currBoneIndex, weight);
			}
		}

		TriMesh* newMesh = new TriMesh(myAiMesh->mNumVertices*3, posIn, myAiMesh->mNumFaces*3, indIn, normIn, uvIn);
		meshesIn[i] = newMesh;
		newMesh->setMatIndex(myAiMesh->mMaterialIndex);
		newMesh->setVBI(boneInfoIn);
		newMesh->setBones(bonesIn, myAiMesh->mNumBones);
	}

	//---------------------------------------------------------------------------------------------
	//Load Materials
	if(myScene->HasMaterials())
	{
		numMaterials = myScene->mNumMaterials;
		materialsIn = new Material*[numMaterials];
		numTextures = myScene->mNumMaterials;
		texturesIn = new Texture*[numTextures];
		for (unsigned int i = 0; i < numMaterials; i++)
		{
			const aiMaterial* myAiMat = myScene->mMaterials[i];

			//get first diffuse texture (implement more later)
			if(myAiMat->GetTextureCount(aiTextureType_DIFFUSE) > 0)
			{
				aiString texName;
				if (myAiMat->GetTexture(aiTextureType_DIFFUSE, 0, &texName, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
				{
					std::string texNameS (texName.C_Str());
					int size = texNameS.size();
					if (texNameS[size-1] == 'a')
					{
						texNameS[size-3] = 'b';
						texNameS[size-2] = 'm';
						texNameS[size-1] = 'p';
					}
					else if (texNameS[size-1] == '.')
						texNameS.append("bmp");
					else
						texNameS.append(".bmp");

					texturesIn[i] = getTexture(texNameS);
					if(texturesIn[i] == NULL) texturesIn[i] = getTexture("blank.bmp");
				}
				else texturesIn[i] = getTexture("blank.bmp");
			}
			else
			{
				texturesIn[i] = getTexture("sinbad_body.bmp");
			}

			aiColor3D emiIn, ambIn, difIn, speIn;
			float shiIn;

			myAiMat->Get(AI_MATKEY_COLOR_EMISSIVE,emiIn);
			myAiMat->Get(AI_MATKEY_COLOR_AMBIENT,ambIn);
			myAiMat->Get(AI_MATKEY_COLOR_DIFFUSE,difIn);
			myAiMat->Get(AI_MATKEY_COLOR_SPECULAR,speIn);
			myAiMat->Get(AI_MATKEY_SHININESS,shiIn);

			materialsIn[i] = new Material(emiIn.r,emiIn.g,emiIn.b,1.0f,
										//ambIn.r,ambIn.g,ambIn.g,1.0f,
										1-difIn.r,1-difIn.g,1-difIn.b,1.0f,
										difIn.r,difIn.g,difIn.b,1.0f,
										speIn.r,speIn.g,speIn.b,1.0f,
										shiIn);
		}
	}
	else
	{
		numMaterials = 1;
		materialsIn = new Material*[1];
		materialsIn[0] = new Material();
		numTextures = 1;
		texturesIn = new Texture*[1];
		texturesIn[0] = getTexture("blank.bmp");
	}

	//---------------------------------------------------------------------------------------------
	//Lastly, load mesh animations

	if(myScene->HasAnimations())
	{
		numAnimations = myScene->mNumAnimations;
		animationsIn = new AnimClip*[numAnimations];

		for( unsigned int i = 0; i < myScene->mNumAnimations; i++ )
		{
			aiAnimation* currAnim = myScene->mAnimations[i];
			AnimChannel** channelsIn = new AnimChannel*[currAnim->mNumChannels];
			//Get the animation for each channel (that is, each bone)
			for( unsigned int j = 0; j < currAnim->mNumChannels; j++ )
			{
				aiNodeAnim* currChannel = currAnim->mChannels[j];
				
				Vector3f** positionKeys = new Vector3f*[currChannel->mNumPositionKeys];
				Quaternionf** rotationKeys = new Quaternionf*[currChannel->mNumRotationKeys];
				float* scalingKeys = new float[currChannel->mNumScalingKeys];
				float* positionKeyTimes = new float[currChannel->mNumPositionKeys];
				float* rotationKeyTimes = new float[currChannel->mNumRotationKeys];
				float* scalingKeyTimes = new float[currChannel->mNumScalingKeys];

				for(unsigned int k = 0; k < currChannel->mNumPositionKeys; k++)
				{
					aiVector3D* currPos = &currChannel->mPositionKeys[k].mValue;
					positionKeys[k] = new Vector3f(currPos->x,currPos->y,currPos->z);
					positionKeyTimes[k] = currChannel->mPositionKeys[k].mTime;
				}
				for(unsigned int k = 0; k < currChannel->mNumRotationKeys; k++)
				{
					aiQuaternion* currRot = &currChannel->mRotationKeys[k].mValue;
					rotationKeys[k] = new Quaternionf(currRot->w,currRot->x,currRot->y,currRot->z);
					rotationKeyTimes[k] = currChannel->mRotationKeys[k].mTime;
				}
				for(unsigned int k = 0; k < currChannel->mNumScalingKeys; k++)
				{
					aiVector3D* currScale =  &currChannel->mScalingKeys[k].mValue;
					scalingKeys[k] = currScale->x;
					double currTime = currChannel->mScalingKeys[k].mTime;
				}

				int preState, postState;
				switch(currChannel->mPreState)
				{
				case aiAnimBehaviour_DEFAULT:
					preState = 0;
					break;
				case aiAnimBehaviour_CONSTANT:
					preState = 1;
					break;
				case aiAnimBehaviour_LINEAR:
					preState = 2;
					break;
				case aiAnimBehaviour_REPEAT:
					preState = 3;
				}
				switch(currChannel->mPostState)
				{
				case aiAnimBehaviour_DEFAULT:
					postState = 0;
					break;
				case aiAnimBehaviour_CONSTANT:
					postState = 1;
					break;
				case aiAnimBehaviour_LINEAR:
					postState = 2;
					break;
				case aiAnimBehaviour_REPEAT:
					postState = 3;
				}

				channelsIn[j] = new AnimChannel(currChannel->mNodeName.C_Str(),preState,postState,
												positionKeys,rotationKeys,scalingKeys,positionKeyTimes,rotationKeyTimes,scalingKeyTimes,
												currChannel->mNumPositionKeys,currChannel->mNumRotationKeys,currChannel->mNumScalingKeys);
			}//end animation channel loop
			animationsIn[i] = new AnimClip( currAnim->mName.C_Str(), currAnim->mDuration, currAnim->mTicksPerSecond,
											channelsIn,	currAnim->mNumChannels);
		}//end animation loop
	}
	else
	{
		numAnimations = 1;
		animationsIn = new AnimClip*[1];
		animationsIn[0] = new AnimClip();
	}

	//Get the root-node skeleton
	Bone** skeletonIn = new Bone*[100];
	Bone* currBone = new Bone();
	skeletonIn[0] = currBone;
	aiNode* currRN = myScene->mRootNode;
	int numBones = 0;

	buildSkeleton(currRN,currBone,skeletonIn,numBones);

	meshOut = new LoadedGeometry(meshesIn,texturesIn,materialsIn,animationsIn,skeletonIn,numMeshes,numTextures,numMaterials,numAnimations,numBones,gIT);
	return TRUE;
}

/*
 * buildSceneGraph recursively traverses the aiScene's node structure and converts
 * it to a local format.
 */
void ResourceMan::buildSkeleton(aiNode* currAiNode, Bone* currBone, Bone** bonePile, int& countBones)
{
	currBone->setName(currAiNode->mName.C_Str());

	aiMatrix4x4 currMat = currAiNode->mTransformation;

	float* matA = new float[16];
	matA[0] = currMat.a1;	matA[0] = currMat.b1;	matA[0] = currMat.c1;	matA[0] = currMat.d1;
	matA[4] = currMat.a2;	matA[0] = currMat.b2;	matA[0] = currMat.c2;	matA[0] = currMat.d2;
	matA[8] = currMat.a3;	matA[0] = currMat.b3;	matA[0] = currMat.c3;	matA[0] = currMat.d3;
	matA[12] = currMat.a4;	matA[0] = currMat.b4;	matA[0] = currMat.c4;	matA[0] = currMat.d4;
	currBone->setTransformation(matA);

	countBones++;

	//build skeleton recursively
	int numM = currAiNode->mNumMeshes;
	int numC = currAiNode->mNumChildren;
	for(int i = 0; i < numM && i < 10; i++)
	{
		currBone->setMIndex(i,currAiNode->mMeshes[i]);
		currBone->addNumMIndices(1);
	}
	for(int i = 0; i < numC; i++)
	{
		aiNode* newNode = currAiNode->mChildren[i];
		Bone* newChild = new Bone();
		currBone->attachChild(newChild);
		bonePile[countBones] = newChild;
		buildSkeleton(newNode,newChild,bonePile,countBones);
	}
}

Texture* ResourceMan::loadTexture(aiTexture texIn)
{
	if(texIn.mHeight == 0)
	{
		int myWid = texIn.mWidth;
		int myHgt = texIn.mHeight;
		aiTexel* myTexel = texIn.pcData;

		int iQuantity = myWid*myHgt;
		unsigned char* raucData = new unsigned char[3*iQuantity];

		for (int j = 0, j0 = 0, j1 = 1, j2 = 2; j < iQuantity; j++)
		{
			raucData[j0] = myTexel[j].r;
			raucData[j1] = myTexel[j].g;
			raucData[j2] = myTexel[j].b;
			j0 += 3;
			j1 += 3;
			j2 += 3;
		}

		return new Texture("NULL", raucData, myWid, myHgt);
	}
	else//it's in a compressed format; a decoder should be used; I will blank out the texture in the mean-time.
	{
		return getTexture("blank.bmp");
	}
}

Texture* ResourceMan::getTexture( std::string fileName )
{
	//Have we already loaded it?
	for(int i = 0; i < numTextures; i++)
	{
		if(loadedTextures.at(i).getName() == fileName)
			return &loadedTextures.at(i);
	}

	//Load it
	if(numTextures < 16)
	{
	int imageW,imageH;
	unsigned char* imageData;
	bool loaded = LoadBmp24(fileName.c_str(),imageW,imageH,imageData);
	ai_assert(loaded);
	
	Texture* newTex = new Texture(fileName, imageData, imageW, imageH);
	loadedTextures.push_back(*newTex);
	numTextures++;
	return newTex;
	}

	//no room for another texture
	return NULL;
}