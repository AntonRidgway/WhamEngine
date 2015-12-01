#pragma once
#ifndef WE_SCALECMD
#define WE_SCALECMD

#include "Command.h"

/**
 * ScaleCommand is a Command that multiplies the passed-in Spatial's
 * current scale by some fixed factor in each direction. The factor
 * is defined in the constructor.
 */
class ScaleCommand : public Command {
public:
	ScaleCommand(float amt);
	void execute(Spatial& spatial);
private:
	float amount;
};
#endif