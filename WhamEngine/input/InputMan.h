//Input manager needed for camera controls
#ifndef WE_INPMAN_H
#define WE_INPMAN_H

#include <cstdint>
#include <list>
#include <map>
#include "Command.h"
#include "ForwardCommand.h"
#include "PitchCommand.h"
#include "RightCommand.h"
#include "RollCommand.h"
#include "SetGravityCommand.h"
#include "YawCommand.h"

/**
 * InputMan is a singleton class that manages keyboard and mouse input from the user.
 * It maintains the mapping between specific keys and reified Command objects, and 
 * contains the callback functions for input that are used by GLUT.
 */
class InputMan
{
	public:
		static InputMan& getInstance() {
			static InputMan instance;
			return instance; //Return a reference only.
		}
		void startUp();
		void shutDown();
		std::map<unsigned char, Command*> keyMapping;
		std::list<Command*> commandList;
	private:
		InputMan() {} //Make constructor private.
		InputMan(InputMan const&) = delete; //Disallow the copy constructor.
		void operator=(InputMan const&) = delete; //Disallow copies of the singleton.
		const float playerMoveSpeed = 0.2f;
		const float playerTurnSpeed = 0.04f;
};

#endif
