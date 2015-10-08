#include "stdafx.h"
#include <gl/freeglut.h>
#include "InputMan.h"

void keyUpCallback(unsigned char key, int x, int y)
{
	std::map<unsigned char, Command*>* keyMap = &InputMan::getInstance().keyMapping;
	if (keyMap->find(key) != keyMap->end()) {
		keyMap->find(key)->second->toggle(false);
	}
}
void keyDownCallback(unsigned char key, int x, int y)
{
	std::map<unsigned char, Command*>* keyMap = &InputMan::getInstance().keyMapping;
	if (keyMap->find(key) != keyMap->end()) {
		keyMap->find(key)->second->toggle(true);
	}
};
void mouseBtnCallback(int button, int state, int x, int y) {
	//Nothing, for now.
};
void mouseMoveCallback(int x, int y) {
	//Nothing, for now.
};
void mousePassiveMoveCallback(int x, int y) {
	//Nothing, for now.
};
void InputMan::startUp(){
	glutIgnoreKeyRepeat(true);
	glutKeyboardFunc(&keyDownCallback);
	glutKeyboardUpFunc(&keyUpCallback);
	glutMouseFunc(&mouseBtnCallback);
	glutMotionFunc(&mouseMoveCallback);
	glutPassiveMotionFunc(&mousePassiveMoveCallback);

	Command* forward = new ForwardCommand(playerMoveSpeed);
	commandList.push_back(forward);
	keyMapping['w'] = forward;
	keyMapping['W'] = forward;
	Command* backward = new ForwardCommand(-playerMoveSpeed);
	commandList.push_back(backward);
	keyMapping['s'] = backward;
	keyMapping['S'] = backward;
	Command* bankRight = new RightCommand(-playerMoveSpeed);
	commandList.push_back(bankRight);
	keyMapping['d'] = bankRight;
	keyMapping['D'] = bankRight;
	Command* bankLeft = new RightCommand(playerMoveSpeed);
	commandList.push_back(bankLeft);
	keyMapping['a'] = bankLeft;
	keyMapping['A'] = bankLeft;

	Command* pitchUp = new PitchCommand(playerTurnSpeed);
	commandList.push_back(pitchUp);
	keyMapping['i'] = pitchUp;
	keyMapping['I'] = pitchUp;
	Command* pitchDown = new PitchCommand(-playerTurnSpeed);
	commandList.push_back(pitchDown);
	keyMapping['k'] = pitchDown;
	keyMapping['K'] = pitchDown;
	Command* yawLeft = new YawCommand(playerTurnSpeed);
	commandList.push_back(yawLeft);
	keyMapping['j'] = yawLeft;
	keyMapping['J'] = yawLeft;
	Command* yawRight = new YawCommand(-playerTurnSpeed);
	commandList.push_back(yawRight);
	keyMapping['l'] = yawRight;
	keyMapping['L'] = yawRight;
	Command* rollLeft = new RollCommand(-playerTurnSpeed);
	commandList.push_back(rollLeft);
	keyMapping['u'] = rollLeft;
	keyMapping['U'] = rollLeft;
	Command* rollRight = new RollCommand(playerTurnSpeed);
	commandList.push_back(rollRight);
	keyMapping['o'] = rollRight;
	keyMapping['O'] = rollRight;

	Command* shootBall = new ShootCommand();
	commandList.push_back(shootBall);
	keyMapping['b'] = shootBall;
	keyMapping['B'] = shootBall;
	Command* setGravity = new ShootCommand();
	commandList.push_back(setGravity);
	keyMapping['g'] = setGravity;
	keyMapping['G'] = setGravity;
};
void InputMan::shutDown(){
	//Clean up command objects.
	for (std::list<Command*>::const_iterator iterator = commandList.begin(), end = commandList.end(); iterator != end; ++iterator) {
		delete *iterator;
	}
};