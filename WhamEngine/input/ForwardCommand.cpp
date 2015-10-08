#include "stdafx.h"
#include "ForwardCommand.h"

ForwardCommand::ForwardCommand(float amt) {
	amount = amt;
}
void ForwardCommand::execute(Spatial& spatial) {
	spatial.translateForward(amount);
}