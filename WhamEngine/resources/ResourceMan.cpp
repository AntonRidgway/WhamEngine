#include "stdafx.h"

#include "ResourceMan.h"

const std::string ResourceMan::WINDOWS_FILE_SEPARATOR = "\\";

void ResourceMan::startUp()
{
	//Load Textures from Files
	loadTexture("box.bmp");
	loadTexture("blank.bmp");
	loadTexture("brick.bmp");
	loadTexture("carpet.bmp");

	loadTexture("eyeball.bmp");
	loadTexture("sky.bmp");
	loadTexture("wall.bmp");
	loadTexture("wallpic.bmp");

	materialMap["dull"] = new Material();
	materialMap["slime"] = new Material(0.0f,0.0f,0.0f,1.0f,0.2f,0.2f,0.2f,1.0f,0.8f,0.8f,0.8f,1.0f,0.3f,0.3f,0.3f,0.1f,100.0f);
	materialMap["shiny"] = new Material(0.8f,0.8f,0.8f,1.0f,0.8f,0.8f,0.8f,1.0f,0.2f,0.2f,0.2f,1.0f,0.1f,0.1f,0.1f,1.0f,0.0f);
	materialMap["rShiny"] = new Material(0.8f,0.0f,0.0f,1.0f,0.8f,0.8f,0.8f,1.0f,0.2f,0.2f,0.2f,1.0f,0.1f,0.1f,0.1f,1.0f,0.0f);
	materialMap["gShiny"] = new Material(0.0f,0.8f,0.0f,1.0f,0.8f,0.8f,0.8f,1.0f,0.2f,0.2f,0.2f,1.0f,0.1f,0.1f,0.1f,1.0f,0.0f);
	materialMap["bShiny"] = new Material(0.0f,0.0f,0.8f,1.0f,0.8f,0.8f,0.8f,1.0f,0.2f,0.2f,0.2f,1.0f,0.1f,0.1f,0.1f,1.0f,0.0f);
}
void ResourceMan::shutDown()
{
	std::map<std::string, Texture*>::iterator texItr = textureMap.begin();
	while (texItr != textureMap.end()) {
		texItr = textureMap.erase(texItr);
	}
	std::map<std::string, Material*>::iterator matItr = materialMap.begin();
	while (matItr != materialMap.end()) {
		matItr = materialMap.erase(matItr);
	}
}
void ResourceMan::loadLevel(std::string roomFile, Scene* scene)
{
	////Read in the level file.
	//std::ifstream reader(findFileAbsolute(roomFile));
	//std::vector<char> buffer((std::istreambuf_iterator<char>(reader)), std::istreambuf_iterator<char>());
	//buffer.push_back('\0');
	//reader.close();

	//rapidxml::xml_document<> doc;
	//doc.parse<0>(&buffer[0]);
	//rapidxml::xml_node<>* rootNode = doc.first_node();
	//rapidxml::xml_node<>* entitiesNode = rootNode->first_node();
	//rapidxml::xml_node<>* lightsNode = entitiesNode->next_sibling();
	//rapidxml::xml_node<>* texturesNode = lightsNode->next_sibling();
	//rapidxml::xml_node<>* materialsNode = texturesNode->next_sibling();

	//if (entitiesNode->first_node() != NULL) {
	//	entitiesNode = entitiesNode->first_node();
	//	do { //Construct the entity
	//		TriMesh* shape = buildMesh(entitiesNode);
	//		Geometry* simpleGeom
	//	} while (entitiesNode->next_sibling() != NULL);
	//}


	//---------------------------------------------------------------------------------------------
	//Load Scene Entities (Geometries & Quadrics)
	
	//First, create the walls of our bounding box
	//floor
	
	TriMesh* shape = new Quad(30.0f,30.0f);
	Geometry* simpleGeom = new Geometry(shape, textureMap["carpet.bmp"], materialMap["dull"]);
	simpleGeom->rotateX(1.571f);
	simpleGeom->translate(0.0f,-15.0f,15.0f);
	scene->addSceneE(simpleGeom);
	
	//north wall
	shape = new Quad(30.0f,30.0f);
	simpleGeom = new Geometry(shape, textureMap["wall.bmp"], materialMap["dull"]);
	simpleGeom->translate(0.0f,-15.0f,-15.0f);
	scene->addSceneE(simpleGeom);

	//south wall
	shape = new Quad(30.0f,30.0f);
	simpleGeom = new Geometry(shape, textureMap["wall.bmp"], materialMap["dull"]);
	simpleGeom->rotateY(3.1415f);
	simpleGeom->translate(0.0f,-15.0f,15.0f);
	scene->addSceneE(simpleGeom);

	//west wall
	shape = new Quad(30.0f,30.0f);
	simpleGeom = new Geometry(shape, textureMap["wall.bmp"], materialMap["dull"]);
	simpleGeom->rotateY(-1.571f);
	simpleGeom->translate(-15.0f,-15.0f,0.0f);
	scene->addSceneE(simpleGeom);

	//east wall
	shape = new Quad(30.0f,30.0f);
	simpleGeom = new Geometry(shape, textureMap["wallpic.bmp"], materialMap["dull"]);
	simpleGeom->rotateY(1.571f);
	simpleGeom->translate(15.0f,-15.0f,0.0f);
	scene->addSceneE(simpleGeom);

	//sky
	shape = new Quad(30.0f,30.0f);
	simpleGeom = new Geometry(shape, textureMap["sky.bmp"], materialMap["dull"]);
	simpleGeom->rotateX(-1.571f);
	simpleGeom->translate(0.0f,15.0f,-15.0f);
	scene->addSceneE(simpleGeom);

	//tall box
	shape = new Box(2.0f,1.5f,3.0f);
	simpleGeom = new Geometry(shape, textureMap["box.bmp"], materialMap["dull"]);
	simpleGeom->translate(2.3f,0.0f,-7.5f);
	simpleGeom->rotateY(0.3f);
	scene->addSceneE(simpleGeom);
	
	//Tiny Box
	shape = new Box(1.0f,1.0f,1.0f);
	simpleGeom = new Geometry(shape, textureMap["brick.bmp"], materialMap["dull"]);
	simpleGeom->translate(3.3f, 0.0f, -7.5f);
	simpleGeom->rotateY(0.6f);
	scene->addSceneE(simpleGeom);
	
	//Mid Box
	shape = new Box(2.0f,2.0f,2.0f);
	simpleGeom = new Geometry(shape, textureMap["brick.bmp"], materialMap["dull"]);
	simpleGeom->translate(4.3f, 0.0f, -7.5f);
	simpleGeom->rotateY(0.9f);
	scene->addSceneE(simpleGeom);

	//Regular Pyramid
	shape = new Pyramid(1.0f,2.0f);
	simpleGeom = new Geometry(shape, textureMap["brick.bmp"], materialMap["dull"]);
	simpleGeom->translate(5.3f, 0.0f, -7.5f);
	simpleGeom->rotateY(1.2f);
	scene->addSceneE(simpleGeom);
	
	//tall pyramid
	shape = new Pyramid(1.0f, 3.0f);
	simpleGeom = new Geometry(shape, textureMap["wall.bmp"], materialMap["dull"]);
	simpleGeom->translate(6.3f, 0.0f, -7.5f);
	simpleGeom->rotateY(1.5f);
	scene->addSceneE(simpleGeom);

	//quadrics
	scene->addSceneE(new QuadricSphere(textureMap["eyeball.bmp"], materialMap["slime"],-5.0f,5.0f,0.0f, 1.5f,8,5, GLU_FILL,GLU_SMOOTH,GLU_OUTSIDE,GL_TRUE));
	scene->addSceneE(new QuadricSphere(textureMap["eyeball.bmp"], materialMap["slime"],-5.0f,5.0f,0.0f, 0.5f,6,4, GLU_FILL,GLU_SMOOTH,GLU_OUTSIDE,GL_TRUE));

	//Loaded Mesh
	LoadedGeometry* loadedGeom;
	std::string bobPath = findFileAbsolute("boblampclean.md5mesh");
	LoadMesh(bobPath.c_str(), loadedGeom);
	scene->addSceneE(loadedGeom);
	loadedGeom->translateY(-1.5);
	loadedGeom->rotateX(1.7);
	loadedGeom->setScale(0.01f);

	std::string sinbadPath = findFileAbsolute("Sinbad.3ds");
	LoadMesh(sinbadPath.c_str(), loadedGeom);
	scene->addSceneE(loadedGeom);
	loadedGeom->translateY(1.5);
	loadedGeom->rotateX(-1.7);
	
	scene->addSceneE(new QuadricSphere(textureMap["blank.bmp"], materialMap["bShiny"], -7.0f,7.0f,7.0f,0.3f,6,6,GLU_FILL,GLU_SMOOTH,GLU_OUTSIDE,GL_TRUE));
	scene->addSceneE(new QuadricSphere(textureMap["blank.bmp"], materialMap["gShiny"], 0.0f,0.0f,-7.0f,0.3f,6,6,GLU_FILL,GLU_SMOOTH,GLU_OUTSIDE,GL_TRUE));
	scene->addSceneE(new QuadricSphere(textureMap["blank.bmp"], materialMap["rShiny"], 7.0f,-7.0f,3.0f,0.3f,6,6,GLU_FILL,GLU_SMOOTH,GLU_OUTSIDE,GL_TRUE));

	//---------------------------------------------------------------------------------------------
	//Load HUD Entities
	
	//---------------------------------------------------------------------------------------------
	//Load Lights
	scene->addLightE(new Light(1.0f, 1.0f, 1.0f, 1.0f,
									0.0f, 0.0f, 0.0f, 1.0f,
									0.0f, 0.0f, 0.0f, 1.0f,
									0.0f, 0.0f, 0.0f,
									0.0f, 0.0f, 0.0f));
	scene->addLightE(new PointLight(0.0f,0.0f,0.8f,1.0f,
									0.0f,0.0f,3.2f,1.0f,
									0.5f,0.5f,0.5f,1.0f,
									-7.0f,7.0f,7.0f,
									0.9f,0.1f,0.01f));
	scene->addLightE(new PointLight(0.0f,0.8f,0.0f,1.0f,
									0.0f,3.2f,0.0f,1.0f,
									0.5f,0.5f,0.5f,1.0f,
									0.0f,0.0f,-7.0f,
									0.9f,0.1f,0.01f));
	scene->addLightE(new PointLight(0.8f,0.0f,0.0f,1.0f,
									3.2f,0.0f,0.0f,1.0f,
									0.5f,0.5f,0.5f,1.0f,
									7.0f,-7.0f,3.0f,
									0.9f,0.1f,0.01f));
	scene->addLightE(new DirLight(0.01f,0.0f,0.04f,1.0f,
									0.16f,0.14f,0.06f,1.0f,
									0.04f,0.038f,0.014f,1.0f,
									-1.0f,-1.0f,-1.0f));
}

/**
* Loads the acFilename file into the parameter raucData,
* and its dimensions are placed in riWidth and riHeight.
*/
bool ResourceMan::LoadBmp24(const char* filename, int& riWidth, int& riHeight, unsigned char*& raucData)
{
	//Load the bitmap
	HBITMAP hImage = (HBITMAP)LoadImageA(NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (!hImage)
		return false;

	//Get the Device-Independent Bitmap data from the image (dimensions, color format, etc.)
	DIBSECTION dibSection;
	GetObject(hImage, sizeof(DIBSECTION), &dibSection);

	//Send bitmap image data back to the caller.
	riWidth = dibSection.dsBm.bmWidth;
	riHeight = dibSection.dsBm.bmHeight;
	int iQuantity = dibSection.dsBm.bmWidth*dibSection.dsBm.bmHeight;

	//Make sure it's a 24-bit image
	if (dibSection.dsBm.bmBitsPixel != 24)
		return false;

	//Windows BMPs are stored in BGR format, so reverse it to RGB format.
	unsigned char* aucSrc = (unsigned char*)dibSection.dsBm.bmBits;
	raucData = new unsigned char[3 * iQuantity];
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
bool ResourceMan::LoadMesh(const char* filename, LoadedGeometry*& meshOut)
{
	const aiScene* myScene;
	myScene = myImp.ReadFile(filename, aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType |
		aiProcess_GenSmoothNormals |
		aiProcess_GenUVCoords);
	//If the file could not be read, generate an error.
	if (!myScene)
	{
		MessageBox(NULL, L"Error: could not loaded mesh.", L"LoadGeometry Error", MB_OK | MB_ICONINFORMATION);
		printf("Error: could not load scene '%s': %s\n", filename, myImp.GetErrorString());
		return FALSE;
	}
	if (!myScene->HasMeshes())
	{
		MessageBox(NULL, L"Error: no meshes in loaded mesh file.", L"LoadGeometry Error", MB_OK | MB_ICONINFORMATION);
		printf("Error: No meshes in scene '%s': %s\n", filename, myImp.GetErrorString());
		return FALSE;
	}

	aiMatrix4x4 aiGIT = myScene->mRootNode->mTransformation;
	aiGIT.Inverse();
	Matrix44f* gIT = new Matrix44f(aiGIT.a1, aiGIT.a2, aiGIT.a3, aiGIT.a4,
		aiGIT.b1, aiGIT.b2, aiGIT.b3, aiGIT.b4,
		aiGIT.c1, aiGIT.c2, aiGIT.c3, aiGIT.c4,
		aiGIT.d1, aiGIT.d2, aiGIT.d3, aiGIT.d4);
	/*Matrix44f* gIT = new Matrix44f(aiGIT.a1, aiGIT.b1, aiGIT.c1, aiGIT.d1,
		aiGIT.a2, aiGIT.b2, aiGIT.c2, aiGIT.d2,
		aiGIT.a3, aiGIT.b3, aiGIT.c3, aiGIT.d3,
		aiGIT.a4, aiGIT.b4, aiGIT.c4, aiGIT.d4);*/

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

		assert(myAiMesh->HasPositions());
		assert(myAiMesh->HasNormals());
		assert(myAiMesh->HasFaces());

		GLfloat* posIn = new GLfloat[myAiMesh->mNumVertices * 3];
		GLfloat* normIn = new GLfloat[myAiMesh->mNumVertices * 3];
		GLfloat* uvIn = new GLfloat[myAiMesh->mNumVertices * 2];
		GLuint* indIn = new GLuint[myAiMesh->mNumFaces * 3];

		//load the positions, normals, and UV coordinates of a single vertex
		for (unsigned int j = 0; j < myAiMesh->mNumVertices; j++)
		{
			posIn[j * 3] = (myAiMesh->mVertices[j]).x;
			posIn[j * 3 + 1] = (myAiMesh->mVertices[j]).y;
			posIn[j * 3 + 2] = (myAiMesh->mVertices[j]).z;
			normIn[j * 3] = (myAiMesh->mNormals[j]).x;
			normIn[j * 3 + 1] = (myAiMesh->mNormals[j]).y;
			normIn[j * 3 + 2] = (myAiMesh->mNormals[j]).z;
			if (myAiMesh->HasTextureCoords(0))
			{
				uvIn[j * 2] = (myAiMesh->mTextureCoords[0][j]).x;
				uvIn[j * 2 + 1] = (myAiMesh->mTextureCoords[0][j]).y;
			}
			else
			{
				uvIn[j * 2] = 0;
				uvIn[j * 2 + 1] = 0;
			}
		}

		//load the indices
		for (unsigned int j = 0; j < myAiMesh->mNumFaces; j++)
		{
			const aiFace myFace = myAiMesh->mFaces[j];
			assert(myFace.mNumIndices == 3);
			indIn[j * 3] = myFace.mIndices[0];
			indIn[j * 3 + 1] = myFace.mIndices[1];
			indIn[j * 3 + 2] = myFace.mIndices[2];
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
		for (unsigned int j = 0; j < myAiMesh->mNumBones; j++)
		{
			int currBoneIndex;

			//See if the current Bone is already there
			int index = 0;
			std::string boneName(myAiMesh->mBones[j]->mName.C_Str());
			while (index < spotsFilled && boneMappingNames[index] != boneName) {
				index++;
			}
			if (index == spotsFilled) { //This is a new bone; make a new entry.
				currBoneIndex = spotsFilled; //index of the last open spot
				spotsFilled++;
				bonesIn[index] = new Bone();
			}
			else { // The bone is already present
				currBoneIndex = index;
			}
			boneMappingIDs[currBoneIndex] = currBoneIndex;

			//Copy bone name and orientation
			bonesIn[currBoneIndex]->setName(myAiMesh->mBones[j]->mName.C_Str());
			aiMatrix4x4 currMat = myAiMesh->mBones[j]->mOffsetMatrix;
			bonesIn[currBoneIndex]->setTransformation(currMat.a1, currMat.a2, currMat.a3, currMat.a4,
				currMat.b1, currMat.b2, currMat.b3, currMat.b4,
				currMat.c1, currMat.c2, currMat.c3, currMat.c4,
				currMat.d1, currMat.d2, currMat.d3, currMat.d4);

			//Get the bone weights per vertex
			for (unsigned int k = 0; k < myAiMesh->mBones[j]->mNumWeights; k++)
			{
				unsigned int vertexID = myAiMesh->mBones[j]->mWeights[k].mVertexId;
				float weight = myAiMesh->mBones[j]->mWeights[k].mWeight;
				boneInfoIn[vertexID].addBoneData(currBoneIndex, weight);
			}
		}

		TriMesh* newMesh = new TriMesh(myAiMesh->mNumVertices * 3, posIn, myAiMesh->mNumFaces * 3, indIn, normIn, uvIn);
		meshesIn[i] = newMesh;
		newMesh->setMatIndex(myAiMesh->mMaterialIndex);
		newMesh->setVBI(boneInfoIn);
		//newMesh->setBones(bonesIn, myAiMesh->mNumBones);
	}

	//---------------------------------------------------------------------------------------------
	//Load Materials
	if (myScene->HasMaterials())
	{
		numMaterials = myScene->mNumMaterials;
		materialsIn = new Material*[numMaterials];
		numTextures = myScene->mNumMaterials;
		texturesIn = new Texture*[numTextures];
		for (unsigned int i = 0; i < numMaterials; i++)
		{
			const aiMaterial* myAiMat = myScene->mMaterials[i];

			//get first diffuse texture (implement more later)
			if (myAiMat->GetTextureCount(aiTextureType_DIFFUSE) > 0)
			{
				aiString texName;
				if (myAiMat->GetTexture(aiTextureType_DIFFUSE, 0, &texName, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
				{
					std::string texNameS(texName.C_Str());
					int size = texNameS.size();
					if (texNameS[size - 1] == 'a')
					{
						texNameS[size - 3] = 'b';
						texNameS[size - 2] = 'm';
						texNameS[size - 1] = 'p';
					}
					else if (texNameS[size - 1] == '.')
						texNameS.append("bmp");
					else
						texNameS.append(".bmp");

					texturesIn[i] = loadTexture(texNameS);
					if (texturesIn[i] == NULL) texturesIn[i] = loadTexture("blank.bmp");
				}
				else texturesIn[i] = loadTexture("blank.bmp");
			}
			else {
				texturesIn[i] = loadTexture("blank.bmp");
			}

			aiColor3D emiIn, ambIn, difIn, speIn;
			float shiIn;

			myAiMat->Get(AI_MATKEY_COLOR_EMISSIVE, emiIn);
			myAiMat->Get(AI_MATKEY_COLOR_AMBIENT, ambIn);
			myAiMat->Get(AI_MATKEY_COLOR_DIFFUSE, difIn);
			myAiMat->Get(AI_MATKEY_COLOR_SPECULAR, speIn);
			myAiMat->Get(AI_MATKEY_SHININESS, shiIn);

			materialsIn[i] = new Material(emiIn.r, emiIn.g, emiIn.b, 1.0f,
				//ambIn.r,ambIn.g,ambIn.g,1.0f,
				1 - difIn.r, 1 - difIn.g, 1 - difIn.b, 1.0f,
				difIn.r, difIn.g, difIn.b, 1.0f,
				speIn.r, speIn.g, speIn.b, 1.0f,
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
		texturesIn[0] = loadTexture("blank.bmp");
	}

	//---------------------------------------------------------------------------------------------
	//Lastly, load mesh animations

	if (myScene->HasAnimations())
	{
		numAnimations = myScene->mNumAnimations;
		animationsIn = new AnimClip*[numAnimations];

		for (unsigned int i = 0; i < myScene->mNumAnimations; i++)
		{
			aiAnimation* currAnim = myScene->mAnimations[i];
			AnimChannel** channelsIn = new AnimChannel*[currAnim->mNumChannels];
			//Get the animation for each bone channel
			for (unsigned int j = 0; j < currAnim->mNumChannels; j++)
			{
				aiNodeAnim* currChannel = currAnim->mChannels[j];

				Vector3f** positionKeys = new Vector3f*[currChannel->mNumPositionKeys];
				Quaternionf** rotationKeys = new Quaternionf*[currChannel->mNumRotationKeys];
				float* scalingKeys = new float[currChannel->mNumScalingKeys];
				float* positionKeyTimes = new float[currChannel->mNumPositionKeys];
				float* rotationKeyTimes = new float[currChannel->mNumRotationKeys];
				float* scalingKeyTimes = new float[currChannel->mNumScalingKeys];

				for (unsigned int k = 0; k < currChannel->mNumPositionKeys; k++)
				{
					aiVector3D* currPos = &currChannel->mPositionKeys[k].mValue;
					positionKeys[k] = new Vector3f(currPos->x, currPos->y, currPos->z);
					positionKeyTimes[k] = currChannel->mPositionKeys[k].mTime;
				}
				for (unsigned int k = 0; k < currChannel->mNumRotationKeys; k++)
				{
					aiQuaternion* currRot = &currChannel->mRotationKeys[k].mValue;
					rotationKeys[k] = new Quaternionf(currRot->w, currRot->x, currRot->y, currRot->z);
					rotationKeyTimes[k] = currChannel->mRotationKeys[k].mTime;
				}
				for (unsigned int k = 0; k < currChannel->mNumScalingKeys; k++)
				{
					aiVector3D* currScale = &currChannel->mScalingKeys[k].mValue;
					scalingKeys[k] = currScale->x;
					double currTime = currChannel->mScalingKeys[k].mTime;
				}

				int preState, postState;
				switch (currChannel->mPreState)
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
				switch (currChannel->mPostState)
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

				channelsIn[j] = new AnimChannel(currChannel->mNodeName.C_Str(), preState, postState,
					positionKeys, rotationKeys, scalingKeys, positionKeyTimes, rotationKeyTimes, scalingKeyTimes,
					currChannel->mNumPositionKeys, currChannel->mNumRotationKeys, currChannel->mNumScalingKeys);
			}//end animation channel loop
			animationsIn[i] = new AnimClip(currAnim->mName.C_Str(), currAnim->mDuration, currAnim->mTicksPerSecond,
				channelsIn, currAnim->mNumChannels);
		}//end animation loop
	}
	else
	{
		numAnimations = 0;
		animationsIn = NULL;
	}

	//Get the root-node skeleton
	Bone** skeletonIn = new Bone*[100];
	Bone* currBone = new Bone();
	skeletonIn[0] = currBone;
	aiNode* currRN = myScene->mRootNode;
	int numBones = 0;

	buildSkeleton(currRN, currBone, skeletonIn, numBones);

	meshOut = new LoadedGeometry(meshesIn, texturesIn, materialsIn, animationsIn, skeletonIn, numMeshes, numTextures, numMaterials, numAnimations, numBones, gIT);
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
	//currBone->setTransformation(currMat.a1, currMat.b1, currMat.c1, currMat.d1,
	//							currMat.a2, currMat.b2, currMat.c2, currMat.d2,
	//							currMat.a3, currMat.b3, currMat.c3, currMat.d3,
	//							currMat.a4, currMat.b4, currMat.c4, currMat.d4);
	currBone->setTransformation(currMat.a1, currMat.a2, currMat.a3, currMat.a4,
							currMat.b1, currMat.b2, currMat.b3, currMat.b4,
							currMat.c1, currMat.c2, currMat.c3, currMat.c4,
							currMat.d1, currMat.d2, currMat.d3, currMat.d4);
	countBones++;

	//build skeleton recursively
	int numM = currAiNode->mNumMeshes;
	int numC = currAiNode->mNumChildren;
	for (int i = 0; i < numM && i < 10; i++)
	{
		currBone->setMIndex(i, currAiNode->mMeshes[i]);
		currBone->addNumMIndices(1);
	}
	for (int i = 0; i < numC; i++)
	{
		aiNode* newNode = currAiNode->mChildren[i];
		Bone* newChild = new Bone();
		currBone->attachChild(newChild);
		bonePile[countBones] = newChild;
		buildSkeleton(newNode, newChild, bonePile, countBones);
	}
}
bool ResourceMan::doesFileExist(std::string fileName)
{
	std::ifstream file(fileName);
	return file.good();
}
std::string ResourceMan::findFileAbsolute(std::string fileName)
{
	char buffer[WINDOWS_MAX_FILENAME];
	char *val = _getcwd(buffer, sizeof(buffer));
	if (val == NULL) return NULL; //CWD was not accessible.
	std::string cwdPath(buffer);
	if (doesFileExist(cwdPath + WINDOWS_FILE_SEPARATOR + fileName))
		return cwdPath + WINDOWS_FILE_SEPARATOR + fileName;
	else {
		int lastPos = cwdPath.find_last_of(WINDOWS_FILE_SEPARATOR);
		if (doesFileExist(cwdPath.substr(0,lastPos) + WINDOWS_FILE_SEPARATOR + "assets" + WINDOWS_FILE_SEPARATOR + fileName))
			return cwdPath.substr(0, lastPos) + WINDOWS_FILE_SEPARATOR + "assets" + WINDOWS_FILE_SEPARATOR + fileName;
		else
			return NULL; //Could not file the file.
	}

}
Texture* ResourceMan::loadTexture(std::string fileName)
{
	//Have we already loaded it?
	if (textureMap.find(fileName) == textureMap.end()) {
		int imageW, imageH;
		unsigned char* imageData;
		bool loaded = LoadBmp24(fileName.c_str(), imageW, imageH, imageData);
		Texture* newTex = new Texture(fileName, imageData, imageW, imageH);
		textureMap[fileName] = newTex;
		return newTex;
	}
	else return textureMap.find(fileName)->second;
}
Texture* ResourceMan::loadAssimpTexture(aiTexture texIn)
{
	if (texIn.mHeight == 0)
	{
		int myWid = texIn.mWidth;
		int myHgt = texIn.mHeight;
		aiTexel* myTexel = texIn.pcData;

		int iQuantity = myWid*myHgt;
		unsigned char* raucData = new unsigned char[3 * iQuantity];

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
		return loadTexture("blank.bmp");
	}
}