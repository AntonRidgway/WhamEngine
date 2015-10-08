#pragma once
#ifndef WE_TRNSLCMD
#define WE_TRNSLCMD

#include "Command.h"
#include "math\Vector.h"

class TranslationCommand : public Command {
public:
	TranslationCommand(Vector3f transVector);
	void execute(Spatial& spatial);
private:
	Vector3f translation;
};

#endif