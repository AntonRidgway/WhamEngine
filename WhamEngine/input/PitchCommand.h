#pragma once
#ifndef WE_PITCHCMD
#define WE_PITCHCMD

#include "Command.h"

class PitchCommand : public Command {
public:
	PitchCommand(float amt);
	void execute(Spatial& spatial);
private:
	float amount;
};

#endif