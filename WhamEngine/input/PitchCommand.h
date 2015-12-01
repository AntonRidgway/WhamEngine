#pragma once
#ifndef WE_PITCHCMD
#define WE_PITCHCMD

#include "Command.h"

/**
 * PitchCommand is a Command that adds to the pitch of any passed-in
 * Spatial object, by some amount defined in the constructor.
 */
class PitchCommand : public Command {
public:
	PitchCommand(float amt);
	void execute(Spatial& spatial);
private:
	float amount;
};

#endif