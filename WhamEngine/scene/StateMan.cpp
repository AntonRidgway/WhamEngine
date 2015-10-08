#include "stdafx.h"
#include "StateMan.h"

void StateMan::startUp(int wIn, int hIn)
{
	lastUpdateTime = std::chrono::high_resolution_clock::now();
	myCam = new Camera(wIn,hIn);
	mySceneGraph = new SGRoot();
	PhysicsMan::getInstance().startUp(mySceneGraph->getSceneEList());
}
void StateMan::shutDown()
{
	PhysicsMan::getInstance().shutDown();
	delete mySceneGraph;
	delete myCam;
}

void StateMan::updateState( )
{
	//Calculate the time since the last update, and update the world accordingly.
	std::chrono::high_resolution_clock::time_point newTime = std::chrono::high_resolution_clock::now();
	double secs = std::chrono::duration_cast<std::chrono::seconds>(newTime - lastUpdateTime).count();
	updateControl(secs);
	updatePhysics(secs);
}
Camera* StateMan::getCamera()
{
	return myCam;
}
SGRoot* StateMan::getSceneGraph()
{
	return mySceneGraph;
}

void StateMan::updateControl(double secsPassed)
{
	for (std::list<Command*>::const_iterator iterator = InputMan::getInstance().commandList.begin(),
											end = InputMan::getInstance().commandList.end(); iterator != end; ++iterator) {
		if ((*iterator)->isActive()) (*iterator)->execute(*myCam);
	}
	myCam->updateGLCam();
}
void StateMan::updatePhysics(double secsPassed)
{
	PhysicsMan::getInstance().step(secsPassed);
}