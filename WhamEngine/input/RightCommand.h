#pragma once
#ifndef WE_RGTCMD
#define WE_RGTCMD

#include "Command.h"

class RightCommand : public Command {
public:
	RightCommand(float amt);
	void execute(Spatial& spatial);
private:
	float amount;
};
#endif