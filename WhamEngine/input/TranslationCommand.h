#pragma once
#ifndef WE_TRNSLCMD
#define WE_TRNSLCMD

#include "Command.h"
#include "math\Vector.h"

/**
 * TranslationCommand is a Command that adds some vector to a
 * passed-in Spatial's current translation. The vector is defined
 * in the constructor.
 */
class TranslationCommand : public Command {
public:
	TranslationCommand(Vector3f transVector);
	void execute(Spatial& spatial);
private:
	Vector3f translation;
};

#endif