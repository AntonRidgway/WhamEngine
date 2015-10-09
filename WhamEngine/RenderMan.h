#ifndef WE_RENDER_H
#define WE_RENDER_H

#include <Windows.h>
#include <gl\GL.h>
#include "scene/Camera.h"
#include "scene/Scene.h"
#include "scene/hud/HUDText.h"
#include <sstream>

class RenderMan
{
public:
	static RenderMan& getInstance() {
		static RenderMan instance;
		return instance; //Return a reference only.
	}
	void startUp(int width, int height);
	void shutDown();
	void renderScene();
	void reshape(int width, int height);
private:
	RenderMan() {} //Make constructor private.
	RenderMan(RenderMan const&) = delete; //Disallow the copy constructor.
	void operator=(RenderMan const&) = delete; //Disallow copies of the singleton.

	//Pointers to variables allocated elsewhere
	Camera* myCam;
	Scene* myScene;

	//various lists for rendering
	GLfloat* lightModel;			//lights
	Light** lightList;
	int lListLen;
	Entity** sceneEList;			//geometry
	int sEListLen;
	HUDText** hudList;				//HUD geometries
	int hListLen;
	HUDText* FPSCounter;				//Debug text

	//Text rendering variables
	bool debugText;

	//private functions to manage OpenGL's lights
	void createLights();
	void updateLights();
};

#endif