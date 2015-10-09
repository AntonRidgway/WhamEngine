#include "stdafx.h"
#include "AnimChannel.h"

AnimChannel::AnimChannel( const char* nName, int prS, int poS, Vector3f** pK, Quaternionf** rK, float* sK, float* pT, float* rT, float* sT, unsigned int nP, unsigned int nR, unsigned int nS )
{
	nodeName = nName;
	preState = prS;
	postState = poS;
	positionKeys = pK;
	rotationKeys = rK;
	scaleKeys = sK;
	pKeyTimes = pT;
	rKeyTimes = rT;
	sKeyTimes = sT;
	numPKeys = nP;
	numRKeys = nR;
	numSKeys = nS;
}
AnimChannel::~AnimChannel()
{
}
std::string AnimChannel::getNodeName()
{
	return nodeName;
}
Matrix44f* AnimChannel::getPosition( float time )
{
	if(numPKeys < 1)
	{
		Matrix44f* posMat = new Matrix44f(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);
		return posMat;
	}
	else if (numPKeys == 1)
	{
		Matrix44f* posMat = new Matrix44f(1,0,0,0,0,1,0,0,0,0,1,0,
				positionKeys[0]->getEntry(0),positionKeys[0]->getEntry(1),positionKeys[0]->getEntry(2),1);
		return posMat;
	}

	float x,y,z;
	int i = 0;
	for(; i < numPKeys && pKeyTimes[i] < time; i++){}
	if(i == numPKeys) //after the last key, loop to first key
	{
		//a half-baked guess at the time-interval to get back to the first key (we have no access to total animation duration!)
		x = Mathf::lerp(time,pKeyTimes[i-2],pKeyTimes[i-1],positionKeys[i-1]->getEntry(0),positionKeys[0]->getEntry(0));
		y = Mathf::lerp(time,pKeyTimes[i-2],pKeyTimes[i-1],positionKeys[i-1]->getEntry(1),positionKeys[0]->getEntry(1));
		z = Mathf::lerp(time,pKeyTimes[i-2],pKeyTimes[i-1],positionKeys[i-1]->getEntry(2),positionKeys[0]->getEntry(2));
	}
	else
	{
		x = Mathf::lerp(time,pKeyTimes[i-1],pKeyTimes[i],positionKeys[i-1]->getEntry(0),positionKeys[i]->getEntry(0));
		y = Mathf::lerp(time,pKeyTimes[i-1],pKeyTimes[i],positionKeys[i-1]->getEntry(1),positionKeys[i]->getEntry(1));
		z = Mathf::lerp(time,pKeyTimes[i-1],pKeyTimes[i],positionKeys[i-1]->getEntry(2),positionKeys[i]->getEntry(2));
	}
	Matrix44f* posMat = new Matrix44f(1,0,0,0,0,1,0,0,0,0,1,0,x,y,z,1);
	return posMat;
}
Matrix44f* AnimChannel::getRotation( float time )
{
	if(numRKeys < 1)
	{
		Matrix44f* rotMat = new Matrix44f(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);
		return rotMat;
	}
	else if (numSKeys == 1)
	{
		float w,x,y,z;
		w = rotationKeys[0]->getW();
		x = rotationKeys[0]->getX();
		y = rotationKeys[0]->getY();
		z = rotationKeys[0]->getZ();
		Matrix44f* rotMat = new Matrix44f(	1-2*(y*y-z*z),	2*(x*y+w*z),	2*(x*z-w*y),	0,
											2*(x*y-w*z),	1-2*(x*x-z*z),	2*(y*z-w*x),	0,
											2*(x*z+w*y),	2*(y*z-w*z),	1-2*(x*x-y*y),	0,
											0,				0,				0,				1);
		return rotMat;
	}

	float w,x,y,z,w0,x0,y0,z0,w1,x1,y1,z1,t0,t1;
	int i = 0;
	for(; i < numRKeys && rKeyTimes[i] < time; i++){}
	if(i == numRKeys)//after last point
	{
		w0 = rotationKeys[i-1]->getW();	x0 = rotationKeys[i-1]->getX();	y0 = rotationKeys[i-1]->getY();	z0 = rotationKeys[i-1]->getZ();
		w1 = rotationKeys[0]->getW();	x1 = rotationKeys[0]->getX();	y1 = rotationKeys[0]->getY();	z1 = rotationKeys[0]->getZ();
		t0 = rKeyTimes[i-2];			t1 = rKeyTimes[i-1];
	}
	else
	{
		w0 = rotationKeys[i-1]->getW();	x0 = rotationKeys[i-1]->getX();	y0 = rotationKeys[i-1]->getY();	z0 = rotationKeys[i-1]->getZ();
		w1 = rotationKeys[i]->getW();	x1 = rotationKeys[i]->getX();	y1 = rotationKeys[i]->getY();	z1 = rotationKeys[i]->getZ();
		t0 = rKeyTimes[i-1];			t1 = rKeyTimes[i];
	}
	w = Mathf::lerp(time,t0,t1,w0,w1);	x = Mathf::lerp(time,t0,t1,x0,x1);	y = Mathf::lerp(time,t0,t1,y0,y1);	z = Mathf::lerp(time,t0,t1,z0,z1);
	Matrix44f* rotMat = new Matrix44f(	1-2*(y*y-z*z),	2*(x*y+w*z),	2*(x*z-w*y),	0,
											2*(x*y-w*z),	1-2*(x*x-z*z),	2*(y*z-w*x),	0,
											2*(x*z+w*y),	2*(y*z-w*z),	1-2*(x*x-y*y),	0,
											0,				0,				0,				1);
	return rotMat;
}
float AnimChannel::getScale( float time )
{
	if(numSKeys < 1)
	{
		return 1.0f;
	}
	else if (numSKeys == 1)
	{
		return scaleKeys[0];
	}
	int i = 0;
	for(; i < numSKeys && sKeyTimes[i] < time; i++){}
	if(i == numSKeys) //after the last key, loop to first key
	{
		//a half-baked guess at the time-interval to get back to the first key (we have no access to total animation duration!)
		return Mathf::lerp(time,sKeyTimes[i-2],sKeyTimes[i-1],scaleKeys[i-1],scaleKeys[0]);
	}
	else
	{
		return Mathf::lerp(time,sKeyTimes[i-1],sKeyTimes[i],scaleKeys[i-1],scaleKeys[i]);
	}
}