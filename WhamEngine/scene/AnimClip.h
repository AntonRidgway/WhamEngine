#ifndef WE_ANIMCLIP_H
#define WE_ANIMCLIP_H

#include <string>
#include "AnimChannel.h"

class AnimClip
{
private:
	const char* myName;
	float duration;
	float tps;
	bool isLooping;

	AnimChannel** channels;
	int numChannels;
public:
	AnimClip ();
	AnimClip (const char* animName, float durIn, float tpsIn, AnimChannel** chIn, int nC, bool looping = 0);
	~AnimClip();
	void update();
	float getTPS();
	float getDuration();
	AnimChannel* getChannel(std::string nodeName);
};

#endif