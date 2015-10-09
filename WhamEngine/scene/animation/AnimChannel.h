#ifndef WE_ANIMCHANNEL_H
#define WE_ANIMCHANNEL_H

#include <string>
#include "math/Math.h"
#include "math/Matrix.h"
#include "math/Quaternion.h"
#include "math/Vector.h"

class AnimChannel
{
private:
	std::string nodeName;
	int preState;
	int postState;
	/*
	preState and postState values
	aiAnimBehaviour_DEFAULT = 0 - The value from the default node transformation is taken.
	aiAnimBehaviour_CONSTANT = 1 - The nearest key value is used without interpolation.
	aiAnimBehaviour_LINEAR = 2 - The value of the nearest two keys is linearly extrapolated for the current time value.
	aiAnimBehaviour_REPEAT = 3 - The animation is repeated. If the animation key go from n to m and the current time is t, use the value at (t-n) % (|m-n|).
	*/

	Vector3f** positionKeys;
	Quaternionf** rotationKeys;
	float* scaleKeys;
	float* pKeyTimes;
	float* rKeyTimes;
	float* sKeyTimes;
	int numPKeys, numRKeys, numSKeys;
public:
	AnimChannel( const char* nName, int prS, int poS, Vector3f** pK, Quaternionf** rK, float* sK, float* pT, float* rT, float* sT, unsigned int nP, unsigned int nR, unsigned int nS );
	~AnimChannel();
	std::string getNodeName();
	Matrix44f* getPosition( float time );
	Matrix44f* getRotation( float time );
	float getScale( float time );
};

#endif