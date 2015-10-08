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
#include "ShootCommand.h"
#include "YawCommand.h"

// add abstraction for eventual key-mapping capability
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
		const float playerMoveSpeed = 0.02f;
		const float playerTurnSpeed = 0.004f;
};

#endif
