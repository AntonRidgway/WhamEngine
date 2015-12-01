#pragma once
#ifndef WE_COMMAND
#define WE_COMMAND

#include "scene\Spatial.h"

/**
 * The Command class is an abstract class that reifies specific game actions,
 * to help abstract key bindings for the input manager.
 */
class Command {
public:
	Command() { active = false; }
	/**
	* execute carries out the action reified by the command.
	*/
	virtual void execute(Spatial& spatial) = 0;
	/**
	 * isActive indicates whether the command is currently being executed.
	 */
	bool isActive() {
		return active;
	}
	/**
	* toggle alters whether or not the command is current considered active (i.e., is executing).
	*/
	void toggle(bool state) {
		active = state;
	}
protected:
	bool active;
};
#endif