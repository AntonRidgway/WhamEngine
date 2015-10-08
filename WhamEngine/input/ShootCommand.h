#pragma once
#ifndef WE_SHOOTCMD
#define WE_SHOOTCMD

#include "Command.h"
#include "physics/PhysicsMan.h"

class ShootCommand : public Command {
public:
	ShootCommand();
	void execute(Spatial& spatial);
};

#endif