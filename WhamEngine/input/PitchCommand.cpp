#include "stdafx.h"
#include "PitchCommand.h"

PitchCommand::PitchCommand(float amt) {
	amount = amt;
}
void PitchCommand::execute(Spatial& spatial) {
	spatial.pitch(amount);
}