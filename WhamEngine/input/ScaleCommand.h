#pragma once
#ifndef WE_SCALECMD
#define WE_SCALECMD

#include "Command.h"

class ScaleCommand : public Command {
public:
	ScaleCommand(float amt);
	void execute(Spatial& spatial);
private:
	float amount;
};
#endif