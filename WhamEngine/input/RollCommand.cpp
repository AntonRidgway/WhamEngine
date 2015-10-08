#include "stdafx.h"
#include "RollCommand.h"

RollCommand::RollCommand(float amt) {
	amount = amt;
}
void RollCommand::execute(Spatial& spatial) {
	spatial.roll(amount);
}