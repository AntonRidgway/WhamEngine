#include "stdafx.h"

#include "AnimClip.h"

void AnimClip::update()
{
}
AnimClip::AnimClip()
{
	//generate a default "null" animation
	myName = "NULL";
	duration = 0;
	tps = 0;
	channels = NULL;
	numChannels = 0;
	isLooping = false;
}
AnimClip::AnimClip(const char* animName, float durIn, float tpsIn, AnimChannel** chIn, int nC, bool looping)
{
	myName = animName;
	duration = durIn;
	if(tps > 0)	tps = tpsIn;
	else tps = 10.0f;

	channels = chIn;
	numChannels = nC;
	isLooping = looping;
}
AnimClip::~AnimClip()
{
	delete[] myName;
	delete[] channels;
}
float AnimClip::getTPS()
{
	return tps;
}
float AnimClip::getDuration()
{
	return duration;
}
AnimChannel* AnimClip::getChannel(std::string nodeName)
{
	for(int i = 0; i < numChannels; i++)
	{
		if(channels[i]->getNodeName() == nodeName)
			return channels[i];
	}
	return NULL;
}