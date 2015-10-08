#include "stdafx.h"
#include "SetGravityCommand.h"

SetGravityCommand::SetGravityCommand() {}
void SetGravityCommand::execute(Spatial& spatial) {
	PhysicsMan::getInstance().setGravity(spatial.getForward());
}