#pragma once
#ifndef WE_GRAVCMD
#define WE_GRAVCMD

#include "Command.h"
#include "PhysicsMan.h"

/**
 * SetGravityCommand is a Command that sets the direction of gravity in the PhysicsMan
 * to that of the 'forward' vector in the passed-in Spatial.
 */
class SetGravityCommand : public Command {
public:
	SetGravityCommand();
	void execute(Spatial& spatial);
};

#endif