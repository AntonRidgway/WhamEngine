#pragma once
#ifndef WE_UPCMD
#define WE_UPCMD

#include "Command.h"

class UpCommand : public Command {
public:
	UpCommand(float amt);
	void execute(Spatial& spatial);
private:
	float amount;
};
#endif