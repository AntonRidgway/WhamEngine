#include "stdafx.h"
#include "StateMan.h"

void StateMan::startUp(int wIn, int hIn)
{
	lastUpdateTime = std::chrono::high_resolution_clock::now();
	myCam = new Camera(wIn,hIn);
	myScene = new Scene();
	PhysicsMan::getInstance().startUp(myScene->getSceneEList());
}
void StateMan::shutDown()
{
	PhysicsMan::getInstance().shutDown();
	delete myScene;
	delete myCam;
}

void StateMan::updateState( )
{
	//Calculate the time since the last update, and update the world accordingly.
	std::chrono::high_resolution_clock::time_point newTime = std::chrono::high_resolution_clock::now();
	double secs = (std::chrono::duration_cast<std::chrono::nanoseconds>(newTime - lastUpdateTime).count())/1000000000.;
	updateControl(secs);
	updatePhysics(secs);
	currentFPS = 1./secs;
	lastUpdateTime = newTime;
}
Camera* StateMan::getCamera() {
	return myCam;
}
Scene* StateMan::getScene() {
	return myScene;
}
float StateMan::getFPS() {
	return currentFPS;
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