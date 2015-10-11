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
	if(numAnimations > 0)
		currentAnimation = myAnimations[0];
	else
		currentAnimation = NULL;
}
LoadedGeometry::~LoadedGeometry()
{
}
void LoadedGeometry::renderSpecific()
{
	//Transform vertices to match generated skeletal positions
	if (currentAnimation != NULL)
		setBoneTransformations(myClock.getTimeSinceStartTime());

	for( int i = 0; i < numMeshes; i++ )
	{
		TriMesh* currMesh = myMeshes[i];
		Texture* currTex = myTextures[0];
		Material* currMat = myMaterials[0];
		float* finalVertices;
		float* finalNormals;

		if (currentAnimation == NULL) {
			glVertexPointer(3, GL_FLOAT, 0, currMesh->getVertices());
			glIndexPointer(GL_UNSIGNED_INT, 0, currMesh->getIndices());
			glNormalPointer(GL_FLOAT, 0, currMesh->getNormals());
			glTexCoordPointer(2, GL_FLOAT, 0, currMesh->getUVs());
		} else {
			float* initialVertices = currMesh->getVertices();
			float* initialNormals = currMesh->getNormals();
			finalVertices = new float[currMesh->getNumVParts()];
			finalNormals = new float[currMesh->getNumNParts()];
			int numV = currMesh->getNumVertices();
			VertexBoneInfo* currVBI = myMeshes[i]->getVBI();
			int i0 = 0; int i1 = 1; int i2 = 2;
			for (int i = 0; i < numV; i++)
			{
				//Calculate the final transformation for the vertex by aggregating the weighted transforms from each connected bone.
				Matrix44f w0(myBones[currVBI[i].boneIDs[0]]->getAnimTransform()->multiply(currVBI[i].boneWeights[0]));
				Matrix44f w1(myBones[currVBI[i].boneIDs[1]]->getAnimTransform()->multiply(currVBI[i].boneWeights[1]));
				Matrix44f w2(myBones[currVBI[i].boneIDs[2]]->getAnimTransform()->multiply(currVBI[i].boneWeights[2]));
				Matrix44f w3(myBones[currVBI[i].boneIDs[3]]->getAnimTransform()->multiply(currVBI[i].boneWeights[3]));
				Matrix44f vTransform = w0.add(w1.add(w2.add(w3)));

				Vector4f oldPos(initialVertices[i0], initialVertices[i1], initialVertices[i2], 1.0f);
				Vector4f newPos = vTransform.multiply(oldPos);
				finalVertices[i0] = newPos.getEntry(0);
				finalVertices[i1] = newPos.getEntry(1);
				finalVertices[i2] = newPos.getEntry(2);
				Vector4f oldNrm(initialNormals[i0], initialNormals[i1], initialNormals[i2], 0.0f);
				//Vector4f newNrm = vTransform.multiply(newPos);
				//finalNormals[i0] = newNrm.getEntry(0);
				//finalNormals[i1] = newNrm.getEntry(1);
				//finalNormals[i2] = newNrm.getEntry(2);
				finalNormals[i0] = oldNrm.getEntry(0);
				finalNormals[i1] = oldNrm.getEntry(1);
				finalNormals[i2] = oldNrm.getEntry(2);

				i0 += 3;
				i1 += 3;
				i2 += 3;
			}
			//Load in transformed mesh data.
			glVertexPointer(3, GL_FLOAT, 0, finalVertices);
			glIndexPointer(GL_UNSIGNED_INT, 0, currMesh->getIndices());
			glNormalPointer(GL_FLOAT, 0, finalNormals);
			glTexCoordPointer(2, GL_FLOAT, 0, currMesh->getUVs());
		}
		
		int currMatIndex = currMesh->getMatIndex();
		if(currMatIndex < numMaterials)
		{
			currTex = myTextures[currMatIndex];
			currMat = myMaterials[currMatIndex];
		}
		float shininess[1] = {currMat->getShininess()};

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

		glDrawElements(GL_TRIANGLES,currMesh->getNumIndices(),GL_UNSIGNED_INT,currMesh->getIndices());
		if (currentAnimation != NULL) {
			delete finalVertices; delete finalNormals;
		}
	}
}

//realTime is the real time, to be measured in seconds
//Only call this once per frame per mesh.
void LoadedGeometry::setBoneTransformations(float realTime)
{
	float currTPS;
    if (currentAnimation->getTPS() != 0) currTPS = currentAnimation->getTPS();
	else currTPS = 25.0f;

    float timeInTicks = realTime * currTPS; //number of ticks into the animation
    float animationTime = Mathf::Fmod(timeInTicks, currentAnimation->getDuration()); // get the time from the start of the animation with a float-modulus

	recurseBoneTransformations(animationTime, myBones[0], Matrix44f::identity);
    for (int i = 0 ; i < numBones ; i++)
	{
       if(myBones[i]->getAnimTransform() == NULL)
		   myBones[i]->setAnimTransform(new Matrix44f(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1));
	}
}

void LoadedGeometry::recurseBoneTransformations(float animTime, Bone* currNode, Matrix44f parentTransform)
{
	// Derive the correct animation position for the current node.
    std::string nodeName(currNode->getName());
    AnimChannel* currChannel = currentAnimation->getChannel(nodeName);
	Matrix44f* globalTransformation;

    if (currChannel != NULL) {
        // Generate transformation matrix
        float scale = currChannel->getScale(animTime);
        Matrix44f scaleMat(scale,0,0,0,0,scale,0,0,0,0,scale,0,0,0,0,1);
		Matrix44f rotMat = currChannel->getRotation(animTime).transpose();
		Matrix44f transMat = currChannel->getPosition(animTime).transpose();

        // Combine the above transformations
        globalTransformation = new Matrix44f(parentTransform.multiply(transMat.multiply(rotMat.multiply(scaleMat))));
    }
	else {
		globalTransformation = new Matrix44f(parentTransform);
	}
	currNode->setAnimTransform(globalTransformation);
	for (int i = 0; i < currNode->getNumChildren(); i++)
		recurseBoneTransformations(animTime, currNode->getChild(i), *globalTransformation);
}