#ifndef WE_RENDER_H
#define WE_RENDER_H

// support for multitexturing
#define GL_TEXTURE0_ARB 0x84C0
#define GL_TEXTURE1_ARB 0x84C1
#define GL_COMBINE 0x8570
#define GL_COMBINE_RGB 0x8571
#define GL_COMBINE_ALPHA 0x8572
#define GL_RGB_SCALE 0x8573
#define GL_INTERPOLATE 0x8575
#define GL_CONSTANT 0x8576
#define GL_PRIMARY_COLOR 0x8577
#define GL_PREVIOUS 0x8578
#define GL_SOURCE0_RGB 0x8580
#define GL_SOURCE1_RGB 0x8581
#define GL_SOURCE2_RGB 0x8582
#define GL_SOURCE0_ALPHA 0x8588
#define GL_SOURCE1_ALPHA 0x8589
#define GL_SOURCE2_ALPHA 0x858A
#define GL_OPERAND0_RGB 0x8590
#define GL_OPERAND1_RGB 0x8591
#define GL_OPERAND2_RGB 0x8592
#define GL_OPERAND0_ALPHA 0x8598
#define GL_OPERAND1_ALPHA 0x8599
#define GL_OPERAND2_ALPHA 0x859A

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