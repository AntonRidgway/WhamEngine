#pragma once
#ifndef WE_FWDCMD
#define WE_FWDCMD

#include "Command.h"

class ForwardCommand : public Command {
public:
	ForwardCommand(float amt);
	void execute(Spatial& spatial);
private:
	float amount;
};
#endif