#ifndef WE_RENDER_H
#define WE_RENDER_H



#include <Windows.h>
#include <gl\GL.h>
#include "scene/Camera.h"
#include "scene/SceneGraph.h"
#include <sstream>

class RenderMan
{
private:
	RenderMan() {} //Make constructor private.
	RenderMan(RenderMan const&) = delete; //Disallow the copy constructor.
	void operator=(RenderMan const&) = delete; //Disallow copies of the singleton.

	//Pointers to variables allocated elsewhere
	Camera* myCam;
	SGRoot* sceneGraph;

	//various lists for rendering
	GLfloat* lightModel;			//lights
	Light** lightList;
	int lListLen;
	Entity** sceneEList;			//geometry
	int sEListLen;
	Entity** hudList;				//HUD geometries
	int hListLen;

	//Text rendering variables
	GLuint textBase;
	HFONT currentFont;
	HFONT oldFont;
	std::ostringstream sStream;
	bool debugText;

	//private functions to manage OpenGL's lights
	void createLights();
	void updateLights();

	/*
	A list of other items that might need to be added to the Render Manager later in engine development:
	GLshader** myShaders;
	Primitive** myPrimitivesToRender;
	Stuff** myDebugDrawing; with GL_LINE and GL_POINT
	GLfont** myFonts;
	std::string** textStrings;
	float** stringLocations;
	GLculler* myRenderingCuller;
	VFX** myVfx;
	Camera** otherCameras; //to render onto virtual screens
	*/

public:
	static RenderMan& getInstance() {
		static RenderMan instance;
		return instance; //Return a reference only.
	}
	void startUp(int width, int height);
	void shutDown();
	void renderScene();
	void reshape(int width, int height);
};

#endif