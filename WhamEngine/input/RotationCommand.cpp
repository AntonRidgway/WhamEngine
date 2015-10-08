#include "stdafx.h"
#include "RotationCommand.h"

RotationCommand::RotationCommand(Quaternionf rotQuatern) : rotation(rotQuatern) {}
void RotationCommand::execute(Spatial& spatial) {
	spatial.rotate(rotation);
}