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

	//Various lists for rendering
	GLfloat* lightModel;			//lights
	Light** lightList;
	int lListLen;
	Entity** sceneEList;			//geometry
	int sEListLen;
	HUDText** hudList;				//HUD geometries
	int hListLen;

	//Private functions to manage OpenGL's lights
	void enableGlLights();
	void updateGlLightSpecs();

	//Lighting constants
	const GLuint LIGHT_CONSTS[8] = { GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3, GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7 };
	const int MAX_NUM_LIGHTS = 8;
};

#endif