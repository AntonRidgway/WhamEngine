#pragma once
#ifndef WE_ROTATCMD
#define WE_ROTATCMD

#include "Command.h"
#include "math\Quaternion.h"

/**
 * RotationCommand is a Command that rotates a passed-in Spatial according to
 * some Quaternion, as defined in the constructor.
 */
class RotationCommand : public Command {
public:
	RotationCommand(Quaternionf rotQuatern);
	void execute(Spatial& spatial);
private:
	Quaternionf rotation;
};

#endif