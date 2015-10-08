#include "stdafx.h"
#include "ScaleCommand.h"

ScaleCommand::ScaleCommand(float amt) : amount(amt) {}
void ScaleCommand::execute(Spatial& spatial) {
	spatial.scaleBy(amount);
}