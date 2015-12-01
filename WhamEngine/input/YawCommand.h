#pragma once
#ifndef WE_YAWCMD
#define WE_YAWCMD

#include "Command.h"

/**
 * YawCommand is a Command that adds to the yaw of any passed-in
 * Spatial object, by some amount defined in the constructor.
 */
class YawCommand : public Command {
public:
	YawCommand(float amt);
	void execute(Spatial& spatial);
private:
	float amount;
};
#endif