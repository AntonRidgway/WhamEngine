#include "stdafx.h"
#include "UpCommand.h"

UpCommand::UpCommand(float amt) {
	amount = amt;
}
void UpCommand::execute(Spatial& spatial) {
	spatial.translateUp(amount);
}