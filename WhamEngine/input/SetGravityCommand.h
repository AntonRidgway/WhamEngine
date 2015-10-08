#pragma once
#ifndef WE_GRAVCMD
#define WE_GRAVCMD

#include "Command.h"
#include "physics/PhysicsMan.h"

class SetGravityCommand : public Command {
public:
	SetGravityCommand();
	void execute(Spatial& spatial);
};

#endif