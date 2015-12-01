#pragma once
#ifndef WE_RGTCMD
#define WE_RGTCMD

#include "Command.h"

/**
 * RightCommand is a Command that adds to the translation of any passed-in Spatial object,
 * in the direction of its 'right' vector, and by the amount defined in the RightCommand's constructor.
 */
class RightCommand : public Command {
public:
	RightCommand(float amt);
	void execute(Spatial& spatial);
private:
	float amount;
};
#endif