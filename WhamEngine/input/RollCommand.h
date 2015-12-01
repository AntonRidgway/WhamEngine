#pragma once
#ifndef WE_ROLLCMD
#define WE_ROLLCMD

#include "Command.h"

/**
 * RollCommand is a Command that adds to the roll of any passed-in
 * Spatial object, by some amount defined in the constructor.
 */
class RollCommand : public Command {
public:
	RollCommand(float amt);
	void execute(Spatial& spatial);
private:
	float amount;
};
#endif