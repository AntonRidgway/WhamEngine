#ifndef WE_STATEMAN_H
#define WE_STATEMAN_H

#include <chrono>
#include <list>
#include <thread>
#include "Camera.h"
#include "input/Command.h"
#include "input/InputMan.h"
#include "physics/PhysicsMan.h"
#include "scene/SceneGraph.h"

class StateMan
{
private:
	StateMan() {} //Make constructor private.
	StateMan(StateMan const&) = delete; //Disallow the copy constructor.
	void operator=(StateMan const&) = delete; //Disallow copies of the singleton.

	std::chrono::high_resolution_clock::time_point lastUpdateTime;
	Camera* myCam;
	float playerMoveSpeed; //units-per-second
	float playerTurnSpeed; //units-per-second
	SGRoot* mySceneGraph;
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
	SGRoot* getSceneGraph();
};
#endif