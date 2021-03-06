#ifndef WE_LOADEDGEOM_H
#define WE_LOADEDGEOM_H

#include <assimp\anim.h>
#include "Material.h"
#include "Texture.h"
#include "scene/Clock.h"
#include "scene/animation/AnimClip.h"
#include "scene/animation/Bone.h"
#include "scene/animation/Node.h"
#include "scene/entities/Entity.h"
#include "scene/entities/TriMesh.h"

class LoadedGeometry : public Entity
{
private:
	TriMesh** myMeshes;
	Texture** myTextures;
	Material** myMaterials;
	AnimClip** myAnimations;
	Node* myGraph;
	Bone** myBones; //root node at index 0
	int numMeshes;
	int numTextures;
	int numMaterials;
	int numAnimations;
	int numBones;
	Matrix44f* globalInverseTransform;
	Clock myClock;
	AnimClip* currentAnimation;

	void setBoneTransformations(float realTime);
	void recurseBoneTransformations(float animTime, Node* currNode, const Matrix44f parentTransform);
public:
	LoadedGeometry(TriMesh** meshesIn, Texture** texturesIn, Material** materialsIn, AnimClip** animationsIn, Node* graphIn, Bone** bonesIn,
				   int nMe, int nT, int nMa, int nA, int nB, Matrix44f* gitIn);
	~LoadedGeometry();
	void renderSpecific();
};

#endif