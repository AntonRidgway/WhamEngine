#include "stdafx.h"
#include "StateMan.h"

void StateMan::startUp(int wIn, int hIn)
{
	myClock = new Clock();
	myCam = new Camera(wIn,hIn);
	myScene = new Scene();
	PhysicsMan::getInstance().startUp(myScene->getSceneEList());

	//Set up FPS Debug text.
	debugText = true;
	FPSCounter = new HUDText("", ColorA(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, 0.02f);
	myScene->addHudE(FPSCounter);
}
void StateMan::shutDown()
{
	delete FPSCounter;
	PhysicsMan::getInstance().shutDown();
	delete myScene;
	delete myCam;
	delete myClock;
}

void StateMan::updateState( )
{
	float secs = myClock->getTimeSinceLastCall();
	updateControl(secs);
	updatePhysics(secs);
	currentFPS = 1./secs;
	FPSCounter->setText("FPS: " + std::to_string(currentFPS));
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