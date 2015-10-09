#include "stdafx.h"
#include "VertexBoneInfo.h"

VertexBoneInfo::VertexBoneInfo()
{
	for(int i = 0; i < NUM_BONE_WEIGHTS; i++)
	{
		boneIDs[i] = 0;
		boneWeights[i] = 0.f;
	}
}
VertexBoneInfo::~VertexBoneInfo()
{
}
void VertexBoneInfo::addBoneData(unsigned int boneIndex, float weight)
{
	for (unsigned int i = 0; i < NUM_BONE_WEIGHTS ; i++)
	{
		if (boneWeights[i] == 0.0f)
		{
			boneIDs[i] = boneIndex;
			boneWeights[i] = weight;
			return;
		} 
	}
}