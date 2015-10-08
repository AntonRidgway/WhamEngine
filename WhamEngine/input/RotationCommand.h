#pragma once
#ifndef WE_ROTATCMD
#define WE_ROTATCMD

#include "Command.h"
#include "math\Quaternion.h"

class RotationCommand : public Command {
public:
	RotationCommand(Quaternionf rotQuatern);
	void execute(Spatial& spatial);
private:
	Quaternionf rotation;
};

#endif