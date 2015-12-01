#include "stdafx.h"

#include "ResourceMan.h"

const std::string ResourceMan::WINDOWS_FILE_SEPARATOR = "\\";

void ResourceMan::startUp()
{
	//Load Textures from Files
	loadTexture("ball.bmp");
	loadTexture("bball.bmp");
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
	materialMap["sky"] = new Material(1.f, 1.f, 1.f, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f);
	materialMap["rShiny"] = new Material(0.8f,0.0f,0.0f,1.0f,0.2f,0.2f,0.2f,1.0f,0.2f,0.2f,0.2f,1.0f,0.1f,0.1f,0.1f,1.0f,0.0f);
	materialMap["gShiny"] = new Material(0.0f,0.8f,0.0f,1.0f,0.2f,0.2f,0.2f,1.0f,0.2f,0.2f,0.2f,1.0f,0.1f,0.1f,0.1f,1.0f,0.0f);
	materialMap["bShiny"] = new Material(0.0f,0.0f,0.8f,1.0f,0.2f,0.2f,0.2f,1.0f,0.2f,0.2f,0.2f,1.0f,0.1f,0.1f,0.1f,1.0f,0.0f);
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
	simpleGeom->rotateX(Mathf::HALF_PI);
	simpleGeom->translate(0.0f,-15.0f,15.0f);
	scene->addSceneE(simpleGeom);
	PhysicsMan::getInstance().addPlane(NULL, 0., Vector3f(0.f,0.f,0.f), Vector3f(0.f, 1.f, 0.f), -15.f);
	
	//north wall
	shape = new Quad(30.0f,30.0f);
	simpleGeom = new Geometry(shape, textureMap["wall.bmp"], materialMap["dull"]);
	simpleGeom->translate(0.0f,-15.0f,-15.0f);
	scene->addSceneE(simpleGeom);
	PhysicsMan::getInstance().addPlane(NULL, 0., Vector3f(0.f, 0.f, 0.f), Vector3f(0.f, 0.f, -1.f), -15.f);

	//south wall
	shape = new Quad(30.0f,30.0f);
	simpleGeom = new Geometry(shape, textureMap["wall.bmp"], materialMap["dull"]);
	simpleGeom->rotateY(-Mathf::PI);
	simpleGeom->translate(0.0f, -15.0f, 15.0f);
	scene->addSceneE(simpleGeom);
	PhysicsMan::getInstance().addPlane(NULL, 0., Vector3f(0.f, 0.f, 0.f), Vector3f(0.f, 0.f, 1.f), -15.f);

	//west wall
	shape = new Quad(30.0f,30.0f);
	simpleGeom = new Geometry(shape, textureMap["wall.bmp"], materialMap["dull"]);
	simpleGeom->rotateY(-Mathf::HALF_PI);
	simpleGeom->translate(-15.0f, -15.0f, 0.0f);
	scene->addSceneE(simpleGeom);
	PhysicsMan::getInstance().addPlane(NULL, 0., Vector3f(0.f, 0.f, 0.f), Vector3f(1.f, 0.f, 0.f), -15.f);

	//east wall
	shape = new Quad(30.0f,30.0f);
	simpleGeom = new Geometry(shape, textureMap["wallpic.bmp"], materialMap["dull"]);
	simpleGeom->rotateY(Mathf::HALF_PI);
	simpleGeom->translate(15.0f, -15.0f, 0.0f);
	scene->addSceneE(simpleGeom);
	PhysicsMan::getInstance().addPlane(NULL, 0., Vector3f(0.f, 0.f, 0.f), Vector3f(-1.f, 0.f, 0.f), -15.f);

	//sky
	shape = new Quad(30.0f,30.0f);
	simpleGeom = new Geometry(shape, textureMap["sky.bmp"], materialMap["sky"]);
	simpleGeom->rotateX(-1.571f);
	simpleGeom->translate(0.0f, 15.0f, -15.0f);
	scene->addSceneE(simpleGeom);
	PhysicsMan::getInstance().addPlane(NULL, 0., Vector3f(0.f, 0.f, 0.f), Vector3f(0.f, -1.f, 0.f), -15.f);

	//tall box
	shape = new Box(2.0f,1.5f,3.0f);
	simpleGeom = new Geometry(shape, textureMap["box.bmp"], materialMap["dull"]);
	scene->addSceneE(simpleGeom);
	PhysicsMan::getInstance().addBox(simpleGeom, 1.f,Vector3f(0.f,0.f,0.f), Vector3f(5.f, 3.f, 0.f), Quaternionf(0.f, 1.f, 1.f, 1.f), Vector3f(1.0, 1.5, 0.75));
	
	//Tiny Box
	shape = new Box(1.0f,1.0f,1.0f);
	simpleGeom = new Geometry(shape, textureMap["brick.bmp"], materialMap["dull"]);
	scene->addSceneE(simpleGeom);
	PhysicsMan::getInstance().addBox(simpleGeom, 0.3f, Vector3f(0.f, 0.f, 0.f), Vector3f(-3.f, 10.f, 0.f), Quaternionf(0.f, 0.f, 0.f, 1.f), Vector3f(0.5f,0.5f,0.5f));

	//Mid Box
	shape = new Box(2.0f,2.0f,2.0f);
	simpleGeom = new Geometry(shape, textureMap["brick.bmp"], materialMap["dull"]);
	scene->addSceneE(simpleGeom);
	PhysicsMan::getInstance().addBox(simpleGeom, 5.f, Vector3f(0.f, 0.f, 0.f), Vector3f(2.f, 10.f, 0.f), Quaternionf(0.f, 1.f, 1.f, 1.f), Vector3f(1.f, 1.f, 1.f));

	//Regular Pyramid
	shape = new Pyramid(1.0f,2.0f);
	simpleGeom = new Geometry(shape, textureMap["brick.bmp"], materialMap["dull"]);
	scene->addSceneE(simpleGeom);
	PhysicsMan::getInstance().addConvexHull(simpleGeom, 1.f, Vector3f(0.f, 0.f, 0.f), Vector3f(10.f, 5.f, 2.f), Quaternionf(0.f, 1.f, 1.f, 1.f),
		shape->getVertices(), shape->getNumVertices());
	
	//tall pyramid
	shape = new Pyramid(1.0f, 3.0f);
	simpleGeom = new Geometry(shape, textureMap["wall.bmp"], materialMap["dull"]);
	scene->addSceneE(simpleGeom);
	PhysicsMan::getInstance().addConvexHull(simpleGeom, 1.f, Vector3f(0.f, 0.f, 0.f), Vector3f(10.f, 5.f, -2.f), Quaternionf(0.f, 1.f, 1.f, 1.f),
		shape->getVertices(), shape->getNumVertices());

	//quadrics
	Entity* quadric = new QuadricSphere(textureMap["bball.bmp"], materialMap["dull"], -5.0f, 5.0f, 0.0f, 1.5f, 8, 5, GLU_FILL, GLU_SMOOTH, GLU_OUTSIDE, GL_TRUE);
	scene->addSceneE(quadric);
	PhysicsMan::getInstance().addSphere(quadric, 0.05f, Vector3f(0.f, 0.f, 0.f), Vector3f(-5.f, 5.f, 0.f), Quaternionf(0.f, 1.f, 1.f, 1.f), 1.5f, 10.f);
	quadric = new QuadricSphere(textureMap["eyeball.bmp"], materialMap["slime"], -5.0f, 5.0f, 0.0f, 0.5f, 6, 4, GLU_FILL, GLU_SMOOTH, GLU_OUTSIDE, GL_TRUE);
	scene->addSceneE(quadric);
	PhysicsMan::getInstance().addSphere(quadric, 5.0f, Vector3f(0.f, 0.f, 0.f), Vector3f(2.f, 5.f, 0.f), Quaternionf(0.f, 0.5f, 0.7f, 0.2f), 0.5f, 0.3f);

	//Loaded Mesh
	LoadedGeometry* loadedGeom;
	std::string bobPath = findFileAbsolute("boblampclean.md5mesh");
	LoadMesh(bobPath.c_str(), loadedGeom);
	loadedGeom->scaleBy(0.1f);
	scene->addSceneE(loadedGeom);
	loadedGeom->setRelativeTranslation(Vector3f(0.f,0.f,30.f));
	PhysicsMan::getInstance().addBox(loadedGeom, 1.0f, Vector3f(0.f, 0.f, 0.f), Vector3f(2.f, 5.f, 0.f), Quaternionf(0.f, 0.5f, 0.7f, 0.2f), Vector3f(2.f,1.5f,2.f));

	std::string sinbadPath = findFileAbsolute("Sinbad.3ds");
	LoadMesh(sinbadPath.c_str(), loadedGeom);
	scene->addSceneE(loadedGeom);
	PhysicsMan::getInstance().addBox(loadedGeom, 1.0f, Vector3f(0.f, 0.f, 0.f), Vector3f(2.f, 5.f, 0.f), Quaternionf(0.f, 0.5f, 0.7f, 0.2f), Vector3f(1.5f, 1.5f, 4.5f));

	scene->addSceneE(new QuadricSphere(textureMap["blank.bmp"], materialMap["bShiny"], -7.0f,7.0f,7.0f,0.3f,6,6,GLU_FILL,GLU_SMOOTH,GLU_OUTSIDE,GL_TRUE));
	scene->addSceneE(new QuadricSphere(textureMap["blank.bmp"], materialMap["gShiny"], 0.0f,0.0f,-7.0f,0.3f,6,6,GLU_FILL,GLU_SMOOTH,GLU_OUTSIDE,GL_TRUE));
	scene->addSceneE(new QuadricSphere(textureMap["blank.bmp"], materialMap["rShiny"], 7.0f,-7.0f,3.0f,0.3f,6,6,GLU_FILL,GLU_SMOOTH,GLU_OUTSIDE,GL_TRUE));
		
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
	std::vector<Bone*> bonesIn = std::vector<Bone*>();		//Bones
	std::map<std::string, int> boneMap = std::map<std::string, int>();
	int numBones = 0;
	

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
		// Load this mesh's bones into an overall list. (i.e., not per-mesh)

		VertexBoneInfo* boneInfoIn = new VertexBoneInfo[myAiMesh->mNumVertices];	//bone weights
		int newBoneIdx = 0;

		//Loop through the bones and map them uniquely into our array
		for (unsigned int j = 0; j < myAiMesh->mNumBones; j++)
		{
			const std::string boneName = myAiMesh->mBones[j]->mName.data;

			//See if the current Bone is already there
			if(boneMap.find(boneName) == boneMap.end()) { //This is a new bone; make a new entry.
				newBoneIdx = numBones;
				numBones++;
				bonesIn.push_back(new Bone());
				boneMap[boneName] = newBoneIdx;
			}
			else { // The bone is already present
				newBoneIdx = boneMap[boneName];
			}
			
			//Copy bone name and inverse bind pose
			bonesIn[newBoneIdx]->setName(boneName);
			aiVector3D scaleVec, positionVec;
			aiQuaternion rotQuat;
			aiMatrix4x4 offset = myAiMesh->mBones[j]->mOffsetMatrix;
			bonesIn[newBoneIdx]->setInvOffset(new Matrix44f(offset.a1, offset.a2, offset.a3, offset.a4,
				offset.b1, offset.b2, offset.b3, offset.b4,
				offset.c1, offset.c2, offset.c3, offset.c4,
				offset.d1, offset.d2, offset.d3, offset.d4));
			//bonesIn[newBoneIdx]->setInvOffset(new Matrix44f(offset.a1, offset.b1, offset.c1, offset.d1,
			//	offset.a2, offset.b2, offset.c2, offset.d2,
			//	offset.a3, offset.b3, offset.c3, offset.d3,
			//	offset.a4, offset.b4, offset.c4, offset.d4));

			offset = myAiMesh->mBones[j]->mOffsetMatrix.Inverse();
			offset.Decompose(scaleVec, rotQuat, positionVec);
			bonesIn[newBoneIdx]->setScale(scaleVec.x,scaleVec.y,scaleVec.z);
			bonesIn[newBoneIdx]->setRotation(rotQuat.w, rotQuat.x, rotQuat.y, rotQuat.z);
			bonesIn[newBoneIdx]->setTranslation(positionVec.x, positionVec.y, positionVec.z);
			//offset.Inverse();
			//bonesIn[newBoneIdx]->setInvOffset(Matrix44f(offset.a1,offset.a2,offset.a3,offset.a4,
			//											offset.b1, offset.b2, offset.b3, offset.b4, 
			//											offset.c1, offset.c2, offset.c3, offset.c4, 
			//											offset.d1, offset.d2, offset.d3, offset.d4 ));

			//Get the bone weights per vertex
			for (unsigned int k = 0; k < myAiMesh->mBones[j]->mNumWeights; k++)
			{
				unsigned int vertexID = myAiMesh->mBones[j]->mWeights[k].mVertexId;
				float weight = myAiMesh->mBones[j]->mWeights[k].mWeight;
				boneInfoIn[vertexID].addBoneData(newBoneIdx, weight);
			}
		}

		TriMesh* newMesh = new TriMesh(myAiMesh->mNumVertices * 3, posIn, myAiMesh->mNumFaces * 3, indIn, normIn, uvIn);
		meshesIn[i] = newMesh;
		newMesh->setMatIndex(myAiMesh->mMaterialIndex);
		newMesh->setVBI(boneInfoIn);
	}
	Bone** boneArray = new Bone*[numBones];
	for (int i = 0; i < numBones; i++) {
		boneArray[i] = bonesIn.at(i);
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
				Vector3f** scalingKeys = new Vector3f*[currChannel->mNumScalingKeys];
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
					rotationKeys[k]->invertIn(); //Invert rotation keys for storage.
					rotationKeyTimes[k] = currChannel->mRotationKeys[k].mTime;
				}
				for (unsigned int k = 0; k < currChannel->mNumScalingKeys; k++)
				{
					aiVector3D* currScale = &currChannel->mScalingKeys[k].mValue;
					scalingKeys[k] = new Vector3f(currScale->x, currScale->y, currScale->z);
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

	//Get the scene graph for the loaded scene
	std::string rootName(myScene->mRootNode->mName.data);
	Node* rootNode = new Node(NULL, boneArray[boneMap[rootName]]);
	buildSceneGraph(myScene->mRootNode, rootNode, boneArray, &boneMap);
	meshOut = new LoadedGeometry(meshesIn, texturesIn, materialsIn, animationsIn, rootNode, boneArray, numMeshes, numTextures, numMaterials, numAnimations, numBones, gIT);
	return TRUE;
}

/*
* buildSceneGraph recursively traverses the aiScene's node structure and converts
* it to a local format.
*/
void ResourceMan::buildSceneGraph(aiNode* currAiNode, Node* currNode, Bone** bonesIn, std::map<std::string, int>* boneMap)
{
	currNode->setName(std::string(currAiNode->mName.data));

	aiVector3D scaleVec, positionVec;
	aiQuaternion rotQuat;
	currAiNode->mTransformation.Decompose(scaleVec, rotQuat, positionVec);
	currNode->setScale(scaleVec.x,scaleVec.y,scaleVec.z);
	currNode->setRotation(rotQuat.w, rotQuat.x, rotQuat.y, rotQuat.z);
	currNode->setTranslation(positionVec.x, positionVec.y, positionVec.z);

	//build graph recursively
	int numC = currAiNode->mNumChildren;
	for (int i = 0; i < numC; i++)
	{
		std::string boneName = currAiNode->mChildren[i]->mName.data;
		Node* newChild;
		if(boneMap->find(boneName) == boneMap->end())
			newChild = new Node(currNode, NULL);
		else
			newChild = new Node(currNode, bonesIn[(*boneMap)[boneName]]);
		currNode->attachChild(newChild);
		buildSceneGraph(currAiNode->mChildren[i], newChild, bonesIn, boneMap);
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