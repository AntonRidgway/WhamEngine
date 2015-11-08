#include "stdafx.h"
#include "AnimChannel.h"

AnimChannel::AnimChannel( const char* nName, int prS, int poS, Vector3f** pK, Quaternionf** rK, Vector3f** sK, float* pT, float* rT, float* sT, unsigned int nP, unsigned int nR, unsigned int nS )
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
Matrix44f AnimChannel::getPosition( float time )
{
	if(numPKeys < 1)
		return Matrix44f(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	
	else if (numPKeys == 1)
		return Matrix44f(1, 0, 0, positionKeys[0]->getEntry(0), 0, 1, 0, positionKeys[0]->getEntry(1), 0, 0, 1, positionKeys[0]->getEntry(2),
			0, 0, 0, 1);

	float x,y,z;
	int i = 0;
	for(; i < numPKeys && pKeyTimes[i] < time; i++){}
	if(i == 0 || i == numPKeys) //after the last key, loop to first key
	{
		//a half-baked guess at the time-interval to get back to the first key (we have no access to total animation duration!)
		x = Mathf::lerp(time,pKeyTimes[numPKeys-2],pKeyTimes[numPKeys-1],positionKeys[numPKeys-1]->getEntry(0),positionKeys[0]->getEntry(0));
		y = Mathf::lerp(time,pKeyTimes[numPKeys-2],pKeyTimes[numPKeys-1],positionKeys[numPKeys-1]->getEntry(1),positionKeys[0]->getEntry(1));
		z = Mathf::lerp(time,pKeyTimes[numPKeys-2],pKeyTimes[numPKeys-1],positionKeys[numPKeys-1]->getEntry(2),positionKeys[0]->getEntry(2));
	}
	else
	{
		x = Mathf::lerp(time,pKeyTimes[i-1],pKeyTimes[i],positionKeys[i-1]->getEntry(0),positionKeys[i]->getEntry(0));
		y = Mathf::lerp(time,pKeyTimes[i-1],pKeyTimes[i],positionKeys[i-1]->getEntry(1),positionKeys[i]->getEntry(1));
		z = Mathf::lerp(time,pKeyTimes[i-1],pKeyTimes[i],positionKeys[i-1]->getEntry(2),positionKeys[i]->getEntry(2));
	}
	return Matrix44f(1, 0, 0, x, 0, 1, 0, y, 0, 0, 1, z, 0, 0, 0, 1);
}
Matrix44f AnimChannel::getRotation( float time )
{
	if(numRKeys < 1)
	{
		return Matrix44f(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	}
	else if (numRKeys == 1)
	{
		return rotationKeys[0]->toMatrix();
	} //else interpolate

	float w,x,y,z,w0,x0,y0,z0,w1,x1,y1,z1,t0,t1;
	int i = 0;
	for(; i < numRKeys && rKeyTimes[i] < time; i++){}
	if(i == 0 || i == numRKeys)//after last point
	{
		w0 = rotationKeys[numRKeys - 1]->getW();	x0 = rotationKeys[numRKeys - 1]->getX();
		y0 = rotationKeys[numRKeys - 1]->getY();	z0 = rotationKeys[numRKeys - 1]->getZ();
		w1 = rotationKeys[0]->getW();	x1 = rotationKeys[0]->getX();	y1 = rotationKeys[0]->getY();	z1 = rotationKeys[0]->getZ();
		t0 = rKeyTimes[numRKeys-2];			t1 = rKeyTimes[numRKeys-1];
	}
	else
	{
		w0 = rotationKeys[i-1]->getW();	x0 = rotationKeys[i-1]->getX();	y0 = rotationKeys[i-1]->getY();	z0 = rotationKeys[i-1]->getZ();
		w1 = rotationKeys[i]->getW();	x1 = rotationKeys[i]->getX();	y1 = rotationKeys[i]->getY();	z1 = rotationKeys[i]->getZ();
		t0 = rKeyTimes[i-1];			t1 = rKeyTimes[i];
	}
	Quaternionf rotQuat(Mathf::lerp(time,t0,t1,w0,w1), Mathf::lerp(time,t0,t1,x0,x1), Mathf::lerp(time,t0,t1,y0,y1), Mathf::lerp(time,t0,t1,z0,z1));
	return rotQuat.toMatrix();
}
Vector3f AnimChannel::getScale( float time )
{
	if(numSKeys < 1)
	{
		return Vector3f(1.0f, 1.0f, 1.0f);
	}
	else if (numSKeys == 1)
	{
		return *scaleKeys[0];
	}
	int i = 0;
	for(; i < numSKeys && sKeyTimes[i] < time; i++){}
	if(i == 0 || i == numSKeys) //after the last key, loop to first key
	{
		//a half-baked guess at the time-interval to get back to the first key (we have no access to total animation duration!)
		Vector3f* scaleKey0 = scaleKeys[numSKeys - 1];	Vector3f* scaleKey1 = scaleKeys[0];
		return Vector3f(Mathf::lerp(time,sKeyTimes[numSKeys -2],sKeyTimes[numSKeys-1],scaleKey0->getEntry(0), scaleKey1->getEntry(0)),
			Mathf::lerp(time, sKeyTimes[numSKeys-2], sKeyTimes[numSKeys-1], scaleKey0->getEntry(1), scaleKey1->getEntry(1)),
			Mathf::lerp(time, sKeyTimes[numSKeys-2], sKeyTimes[numSKeys-1], scaleKey0->getEntry(2), scaleKey1->getEntry(2)));
	}
	else
	{
		Vector3f* scaleKey0 = scaleKeys[i-1];	Vector3f* scaleKey1 = scaleKeys[i];
		return Vector3f(Mathf::lerp(time, sKeyTimes[i - 1], sKeyTimes[i], scaleKey0->getEntry(0), scaleKey1->getEntry(0)),
			Mathf::lerp(time, sKeyTimes[i - 1], sKeyTimes[i], scaleKey0->getEntry(1), scaleKey1->getEntry(1)),
			Mathf::lerp(time, sKeyTimes[i - 1], sKeyTimes[i], scaleKey0->getEntry(2), scaleKey1->getEntry(2)));
	}
}