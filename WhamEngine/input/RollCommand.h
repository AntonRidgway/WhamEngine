#pragma once
#ifndef WE_ROLLCMD
#define WE_ROLLCMD

#include "Command.h"

class RollCommand : public Command {
public:
	RollCommand(float amt);
	void execute(Spatial& spatial);
private:
	float amount;
};
#endif