#pragma once
#ifndef WE_YAWCMD
#define WE_YAWCMD

#include "Command.h"

class YawCommand : public Command {
public:
	YawCommand(float amt);
	void execute(Spatial& spatial);
private:
	float amount;
};
#endif