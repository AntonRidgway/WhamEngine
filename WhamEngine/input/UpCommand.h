#pragma once
#ifndef WE_UPCMD
#define WE_UPCMD

#include "Command.h"

/**
 * UpCommand is a Command that adds to the translation of any passed-in Spatial object,
 * in the direction of its 'up' vector, and by the amount defined in the UpCommand's constructor.
 */
class UpCommand : public Command {
public:
	UpCommand(float amt);
	void execute(Spatial& spatial);
private:
	float amount;
};
#endif