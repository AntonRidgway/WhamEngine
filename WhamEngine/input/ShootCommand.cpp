#include "stdafx.h"
#include "ShootCommand.h"

ShootCommand::ShootCommand() {}
void ShootCommand::execute(Spatial& spatial) {
	PhysicsMan::getInstance().shootBall(spatial.getTranslation().add(spatial.getForward().normalize()), spatial.getForward());
	active = false; //Don't trigger repeatedly on a single key-press.
}