#pragma once
#ifndef WE_TRNSFCMD
#define WE_TRNSFCMD

#include "Command.h"
#include "math\Vector.h"

class TransformationCommand : public Command {
public:
	TransformationCommand(Matrix44f tMatrix);
	void execute(Spatial& spatial);
private:
	Matrix44f transformation;
};

#endif