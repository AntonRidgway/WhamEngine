#include "stdafx.h"
#include "TransformationCommand.h"

TransformationCommand::TransformationCommand(Matrix44f tMatrix) : transformation(tMatrix) {}
void TransformationCommand::execute(Spatial& spatial) {
	spatial.setTransformation(transformation);
}