#pragma once
#ifndef WE_FWDCMD
#define WE_FWDCMD

#include "Command.h"

/**
* ForwardCommand is a Command that adds to the translation of any passed-in Spatial object,
* in the direction of its 'forward' vector, and by the amount defined in the ForwardCommand's constructor.
*/
class ForwardCommand : public Command {
public:
	ForwardCommand(float amt);
	void execute(Spatial& spatial);
private:
	float amount;
};
#endif