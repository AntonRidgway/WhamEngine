#include "stdafx.h"
#include "YawCommand.h"

YawCommand::YawCommand(float amt) {
	amount = amt;
}
void YawCommand::execute(Spatial& spatial) {
	spatial.yaw(amount);
}