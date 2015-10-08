#include "stdafx.h"
#include "RightCommand.h"

RightCommand::RightCommand(float amt) {
	amount = amt;
}
void RightCommand::execute(Spatial& spatial) {
	spatial.translateRight(amount);
}