#pragma once
#ifndef WE_COMMAND
#define WE_COMMAND

#include "scene\Spatial.h"

class Command {
public:
	Command() { active = false; }
	virtual void execute(Spatial& spatial) = 0;
	bool isActive() {
		return active;
	}
	void toggle(bool state) {
		active = state;
	}
protected:
	bool active;
};
#endif