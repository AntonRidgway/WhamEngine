#include "stdafx.h"
#include "TranslationCommand.h"

TranslationCommand::TranslationCommand(Vector3f transVector) : translation(transVector) {}
void TranslationCommand::execute(Spatial& spatial) {
	spatial.translate(translation);
}