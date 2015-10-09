#ifndef WE_LOADEDGEOM_H
#define WE_LOADEDGEOM_H

#include <chrono>
#include <assimp\anim.h>
#include "Material.h"
#include "Texture.h"
#include "scene/AnimClip.h"
#include "scene/Bone.h"
#include "scene/Entity.h"
#include "scene/TriMesh.h"

class LoadedGeometry : public Entity
{
private:
	TriMesh** myMeshes;
	Texture** myTextures;
	Material** myMaterials;
	AnimClip** myAnimations;
	Bone** myBones; //root node at index 0
	int numMeshes;
	int numTextures;
	int numMaterials;
	int numAnimations;
	int numBones;
	Matrix44f* globalInverseTransform;
	std::chrono::high_resolution_clock::time_point startTime;

	void boneTransform(float realTime);
	void traverseSkeleton(float animTime, Bone* currNode, const Matrix44f parentTransform);
	Quaternionf* interpolateRotation(float animTime, const aiNodeAnim* nodeAnim);
public:
	LoadedGeometry(TriMesh** meshesIn, Texture** texturesIn, Material** materialsIn, AnimClip** animationsIn, Bone** bonesIn,
				   int nMe, int nT, int nMa, int nA, int nB, Matrix44f* gitIn);
	~LoadedGeometry();
	void renderSpecific();
};

#endif