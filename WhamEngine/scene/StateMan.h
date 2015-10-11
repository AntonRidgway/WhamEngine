#ifndef WE_STATEMAN_H
#define WE_STATEMAN_H

#include <list>
#include <thread>
#include "Camera.h"
#include "Clock.h"
#include "input/Command.h"
#include "input/InputMan.h"
#include "physics/PhysicsMan.h"
#include "scene/Scene.h"

class StateMan
{
private:
	StateMan() {} //Make constructor private.
	StateMan(StateMan const&) = delete; //Disallow the copy constructor.
	void operator=(StateMan const&) = delete; //Disallow copies of the singleton.

	Clock* myClock;
	Camera* myCam;
	float playerMoveSpeed; //units-per-second
	float playerTurnSpeed; //units-per-second
	Scene* myScene;
	float currentFPS;

	//Set up FPS Debug text.
	bool debugText;
	HUDText* FPSCounter;

	void updateControl(double secsPassed);
	void updatePhysics(double secsPassed);
public:
	static StateMan& getInstance() {
		static StateMan instance;
		return instance; //Return a reference only.
	}
	void startUp(int wIn, int hIn);
	void shutDown();
	void updateState();
	Camera* getCamera();
	Scene* getScene();
	float getFPS();
};
#endif