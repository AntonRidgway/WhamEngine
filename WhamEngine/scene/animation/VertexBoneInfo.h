#ifndef WE_BONEINFO_H
#define WE_BONEINFO_H

const int NUM_BONE_WEIGHTS = 4;

class VertexBoneInfo
{
public:
	VertexBoneInfo();
	~VertexBoneInfo();
	unsigned int boneIDs[NUM_BONE_WEIGHTS];
	float boneWeights[NUM_BONE_WEIGHTS];
	void addBoneData(unsigned int boneIndex, float weight);
};

#endif