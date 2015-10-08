#include "stdafx.h"
#include <Windows.h>
#include <gl\GL.h>
#include "LoadedGeometry.h"

LoadedGeometry::LoadedGeometry(TriMesh** meshesIn, Texture** texturesIn, Material** materialsIn, AnimClip** animationsIn, Bone** bonesIn,
							   int nMe, int nT, int nMa, int nA, int nB, Matrix44f* gitIn)
{
	myMeshes = meshesIn;
	myTextures = texturesIn;
	myMaterials = materialsIn;
	myAnimations = animationsIn;
	myBones = bonesIn;
	numMeshes = nMe;
	numTextures = nT;
	numMaterials = nMa;
	numAnimations = nA;
	numBones = nB;
	globalInverseTransform = gitIn;

	startTime = std::chrono::high_resolution_clock::now();
}
LoadedGeometry::~LoadedGeometry()
{
}
void LoadedGeometry::draw()
{
	for( int i = 0; i < numMeshes; i++ )
	{
		TriMesh* currMesh = myMeshes[i];
		Texture* currTex = myTextures[0];
		Material* currMat = myMaterials[0];

		std::chrono::high_resolution_clock::time_point currTime = std::chrono::high_resolution_clock::now();
		float currTimeInSeconds = std::chrono::duration_cast<std::chrono::seconds>(currTime - startTime).count();
		
		boneTransform(currTimeInSeconds);
		
		//Transform vertices to match now-correct skeletal positions
		VertexBoneInfo* currVBI = myMeshes[i]->getVBI();
		float* initialVertices = currMesh->getVertices();
		float* finalVertices = new float[currMesh->getNumVParts()];
		float* initialNormals = currMesh->getNormals();
		float* finalNormals = new float[currMesh->getNumNParts()];
		int numV = currMesh->getNumVertices();
		
		int i0 = 0; int i1 = 1; int i2 = 2;
		//Matrix44f* boneTransform;
		//Matrix44f* w0;	Matrix44f* w1;	Matrix44f* w2;	Matrix44f* w3;

		for(int i = 0; i < numV; i++)
		{
			finalVertices[i0] = initialVertices[i0];
			finalVertices[i1] = initialVertices[i1];
			finalVertices[i2] = initialVertices[i2];
			/*
			w0 = myBones[currVBI[i].boneIDs[0]]->getAnimTransform();
			w0->multiply(currVBI[i].boneWeights[0]);
			w1 = myBones[currVBI[i].boneIDs[1]]->getAnimTransform();
			w1->multiply(currVBI[i].boneWeights[1]);
			w2 = myBones[currVBI[i].boneIDs[2]]->getAnimTransform();
			w2->multiply(currVBI[i].boneWeights[2]);
			w3 = myBones[currVBI[i].boneIDs[3]]->getAnimTransform();
			w3->multiply(currVBI[i].boneWeights[3]);

			boneTransform = w0->add(*w1->add(*w2->add(*w3)));

			Vector4f oldPos(initialVertices[i0],initialVertices[i1],initialVertices[i2],1);
			Vector4f newPos = boneTransform->multiply(oldPos);
			finalVertices[i0] = newPos.getEntry(0);
			finalVertices[i1] = newPos.getEntry(1);
			finalVertices[i2] = newPos.getEntry(2);
			Vector4f oldNrm(initialNormals[i0],initialNormals[i1],initialNormals[i2],0.0f);
			Vector4f newNrm = boneTransform->multiply(newPos);
			finalNormals[i0] = newNrm.getEntry(0);
			finalNormals[i1] = newNrm.getEntry(1);
			finalNormals[i2] = newNrm.getEntry(2);
			*/
			i0 += 3;
			i1 += 3;
			i2 += 3;
		}
		
		//load in mesh properties
		glVertexPointer (3, GL_FLOAT, 0, finalVertices);
		glIndexPointer (GL_UNSIGNED_INT, 0, currMesh->getIndices());
		glNormalPointer (GL_FLOAT, 0, finalNormals);
		glTexCoordPointer(2, GL_FLOAT,0, currMesh->getUVs());

		int currMatIndex = currMesh->getMatIndex();
		if(currMatIndex < numMaterials)
		{
			currTex = myTextures[currMatIndex];
			currMat = myMaterials[currMatIndex];
		}

		float shininess [1] = {currMat->getShininess()};

		//Load in material properties
		glMaterialfv(GL_FRONT, GL_EMISSION, currMat->getEmissive());
		glMaterialfv(GL_FRONT, GL_AMBIENT, currMat->getAmbient());
		glMaterialfv(GL_FRONT, GL_DIFFUSE, currMat->getDiffuse());
		glMaterialfv(GL_FRONT, GL_SPECULAR, currMat->getSpecular());
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

		//Bind the current texture.
		GLuint temp = currTex->getGfxID();
		if( temp != 0 )
		{
			glBindTexture(GL_TEXTURE_2D, temp);
		}
		else
		{
			glGenTextures(1,&temp);
			currTex->setGfxID(temp);
			glBindTexture(GL_TEXTURE_2D,temp);
			glTexImage2D(GL_TEXTURE_2D,0,GL_RGB8,currTex->getWidth(),currTex->getHeight(),0,GL_RGB,GL_UNSIGNED_BYTE,currTex->getData());
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		}

		//make this faster by putting it in this format in the matrix class
		//the 4x4 matrix to adjust the position and rotation of this geometry
		Matrix44f rotation = getRotation();
		float rotMatrix[16] =
		{
			rotation.getEntry(0,0), rotation.getEntry(0,1), rotation.getEntry(0,2), 0.0f,
			rotation.getEntry(1,0), rotation.getEntry(1,1), rotation.getEntry(1,2), 0.0f,
			rotation.getEntry(2,0), rotation.getEntry(2,1), rotation.getEntry(2,2), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
		//float rotMatrix[16] =
		//{
		//	rotation.getEntry(0,0), rotation.getEntry(1,0), rotation.getEntry(2,0), 0.0f,
		//	rotation.getEntry(0,1), rotation.getEntry(1,1), rotation.getEntry(2,1), 0.0f,
		//	rotation.getEntry(0,2), rotation.getEntry(1,2), rotation.getEntry(2,2), 0.0f,
		//	0.0f, 0.0f, 0.0f, 1.0f
		//};
		Vector3f translation = getTranslation();
		float transMatrix[16] =
		{
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			translation.getEntry(0), translation.getEntry(1), translation.getEntry(2), 1.0f
		};

		// set the model-to-world transformation
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glMultMatrixf(transMatrix);
		glMultMatrixf(rotMatrix);
		
		glDrawElements(GL_TRIANGLES,currMesh->getNumIndices(),GL_UNSIGNED_INT,currMesh->getIndices());

		// restore the previous transformation
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();

		delete[] finalVertices;
		delete[] finalNormals;
	}
}

//realTime is the real time, to be measured in seconds
//Only call this once per frame per mesh.
void LoadedGeometry::boneTransform(float realTime)
{
	Matrix44f identity(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);

	float currTPS;
    if (myAnimations[0]->getTPS() != 0) currTPS = myAnimations[0]->getTPS();
	else currTPS = 25.0f;

    float timeInTicks = realTime * currTPS; //number of ticks into the animation
    float animationTime = fmod(timeInTicks, myAnimations[0]->getDuration());// get the time from the start of the animation with a float-modulus

	traverseSkeleton(animationTime, myBones[0], identity);

    for (int i = 0 ; i < numBones ; i++)
	{
       if(myBones[i]->getAnimTransform() == NULL)
		   myBones[i]->setAnimTransform(new Matrix44f(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1));
	}
}

//Note: this only supports a single animation for the geometry.  To support multiple animations,
//an animation name should be passed in to find the appropriate stored animation.
//Should only be called once per frame per mesh, from boneTransform.
void LoadedGeometry::traverseSkeleton(float animTime, Bone* currNode, const Matrix44f parentTransform)
{
	// first derive the correct animation position for the current node
	AnimClip* currAnim = myAnimations[0];
    std::string nodeName(currNode->getName());
    AnimChannel* currChannel = currAnim->getChannel(nodeName);

    Matrix44f* nodeTransformation;

    if (currChannel != NULL)
	{
        // Interpolate scaling and generate scaling transformation matrix
        float scale = currChannel->getScale(animTime);
        Matrix44f scaleMat(scale,0,0,0,0,scale,0,0,0,0,scale,0,0,0,0,1);

        // Interpolate rotation and generate rotation transformation matrix
        Matrix44f* rotMat = currChannel->getRotation(animTime);

        // Interpolate translation and generate translation transformation matrix
        Matrix44f* transMat = currChannel->getPosition(animTime);

        // Combine the above transformations
        nodeTransformation = new Matrix44f(transMat->multiply(rotMat->multiply(scaleMat)));
    }
	else
	{
		nodeTransformation  = new Matrix44f(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);
	}

    Matrix44f globalTransformation = currNode->getTransformation().multiply(*nodeTransformation);

	for(int i = 0; i < currNode->getNumMIndices() && currNode->getMIndex(i) != -1; i++)
	{
		TriMesh* currMesh = myMeshes[currNode->getMIndex(i)];
		Bone* currBone = currMesh->getBone(nodeName);
		if (currBone != NULL)
		{
			currBone->setAnimTransform(&(globalInverseTransform->multiply(globalTransformation).multiply(currBone->getTransformation())));
		}

		Bone* child = currNode->getChild(0);
		for (unsigned int j = 0; child != NULL; j++)
		{
			traverseSkeleton(animTime, child, globalTransformation);
		}
	}
}