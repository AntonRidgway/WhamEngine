#include "stdafx.h"

#include "scene\StateMan.h"
#include "RenderMan.h"
#include <gl\GL.h>
#include <gl\freeglut.h>

/**
 * createLights sets the OpenGL lights to reflect the engine's own data structures, in lListLen.
 */
void RenderMan::createLights()
{
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	glDisable(GL_LIGHT3);
	glDisable(GL_LIGHT4);
	glDisable(GL_LIGHT5);
	glDisable(GL_LIGHT6);
	glDisable(GL_LIGHT7);
	if( lListLen >= 1 ) glEnable(GL_LIGHT0);
	if( lListLen >= 2 ) glEnable(GL_LIGHT1);
	if( lListLen >= 3 ) glEnable(GL_LIGHT2);
	if( lListLen >= 4 ) glEnable(GL_LIGHT3);
	if( lListLen >= 5 ) glEnable(GL_LIGHT4);
	if( lListLen >= 6 ) glEnable(GL_LIGHT5);
	if( lListLen >= 7 ) glEnable(GL_LIGHT6);
	if( lListLen >= 8 ) glEnable(GL_LIGHT7);
}

/**
 * updateLights updates the OpenGL lights; this should be run for each render.
 */
void RenderMan::updateLights()
{
	int lightFlag = GL_LIGHT0;
	for(int i = 0; i < lListLen; i++)
	{
		glLightfv(lightFlag,GL_AMBIENT,lightList[i]->getAmbient()->getData());
		glLightfv(lightFlag,GL_DIFFUSE,lightList[i]->getDiffuse()->getData());
		glLightfv(lightFlag,GL_SPECULAR,lightList[i]->getSpecular()->getData());
		glLightfv(lightFlag,GL_POSITION,lightList[i]->getPosition()->getArray()); // direction for directional light
		glLightf(lightFlag, GL_CONSTANT_ATTENUATION, lightList[i]->getAttenuation(0));
        glLightf(lightFlag, GL_LINEAR_ATTENUATION, lightList[i]->getAttenuation(1));
        glLightf(lightFlag, GL_QUADRATIC_ATTENUATION, lightList[i]->getAttenuation(2));

		if(lightList[i]->getLightType() == 3)
		{
			glLightfv(lightFlag,GL_SPOT_DIRECTION,lightList[i]->getDirection()->getArray());
			glLightf(lightFlag,GL_SPOT_EXPONENT,lightList[i]->getExponent());
			glLightf(lightFlag,GL_SPOT_CUTOFF,lightList[i]->getCutoff());
		}

		lightFlag += 1; //Go to the next light.
	}
}

/**
 * renderScene is used in the game loop to render the scene.
 */
void RenderMan::renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	StateMan::getInstance().updateState();
	updateLights();
	for (int i = 0; i < sEListLen; i++)
		sceneEList[i]->draw();

	// copy the back buffer into the front buffer
	glutSwapBuffers();
	glutPostRedisplay();
}
void RenderMan::reshape(int width, int height) {
	//Set up projection for the new window.
	myCam->setAspectRatio(((double)width) / height);
	glViewport(0, 0, width, height);
}
void renderWindow(void) {
	RenderMan::getInstance().renderScene();
}
void reshapeWindow(int width, int height) {
	RenderMan::getInstance().reshape(width, height);
}

void RenderMan::startUp(int width, int height)
{
	//start various rendering stuff
	sceneGraph = StateMan::getInstance().getSceneGraph();
	myCam = StateMan::getInstance().getCamera();
	debugText = true;

	//set up text rendering
	//textBase = glGenLists(96);
	//currentFont = CreateFont(-16,8,0,0,FW_BOLD,FALSE,FALSE,FALSE,ANSI_CHARSET,OUT_TT_PRECIS,CLIP_DEFAULT_PRECIS,
	//	ANTIALIASED_QUALITY,FF_DONTCARE|DEFAULT_PITCH,L"Arial");
	//oldFont = (HFONT)SelectObject(*dvcContext, currentFont);
	//wglUseFontBitmaps(*dvcContext, 32, 96, textBase);
	//SelectObject(*dvcContext, oldFont);
	//DeleteObject(currentFont);

	//Create lists of elements to be rendered.
	sceneEList = sceneGraph->getSceneEList();
	sEListLen = sceneGraph->getNumSceneE();
	hudList = sceneGraph->getHudEList();
	hListLen = sceneGraph->getNumHudE();
	lightList = sceneGraph->getLightEList();
	lListLen = sceneGraph->getNumLightE();

	//Enable triangle culling and nice perspective correction.
	glEnable(GL_CULL_FACE);				//only the front of triangles
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//Set up clear parameters for different buffer-clearing operations
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);	//clear the color buffer
	glClearDepth(1.0f);						//clear the depth buffer
	glClearIndex(1.0f);						//the index buffer
	glClearAccum(1.0f, 1.0f, 1.0f, 1.0f);		//the accumulation buffer
	glClearStencil(1);					//the stencil buffer

	glEnable(GL_DEPTH);					//Enable Depth Buffer
	glEnable(GL_DEPTH_TEST);			//Enable Depth Test
	glDepthMask(GL_TRUE);				//Use Depth Masking
	glDepthFunc(GL_LEQUAL);				//Render behind if less than or equal to the object in question
	glDepthRange(0.0f, 1.0f);			//The range of depths to consider.
	glViewport(0, 0, width, height);

	glEnable(GL_LIGHTING);				//Enable Lighting
	glEnable(GL_NORMALIZE);				//Enable Normalizing of normal vectors (could be done manually faster?)
	glShadeModel(GL_SMOOTH);			//Smooth Shading
	//glEnable(GL_FOG);					//Enable fog

	glEnable(GL_TEXTURE_2D);			//enable 2d textures
										//set up the texture environment
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glPolygonMode(GL_FRONT, GL_FILL);	//Enable filling front faces
	glPolygonMode(GL_BACK, GL_LINE);	//Enable outlining back faces
	

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_INDEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//set up light model
	lightModel = new GLfloat[4];
	lightModel[0] = 0.1f; lightModel[1] = 0.1f; lightModel[2] = 0.1f; lightModel[3] = 1.0f;
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightModel);

	//set up lights
	createLights();
	updateLights();

	//---------------------------------------------------------------------------------------------
	//Finally, set up the perspective projection matrix to begin.
	glutIdleFunc(NULL);
	glutDisplayFunc(&renderWindow);
	glutReshapeFunc(&reshapeWindow);
}

/**
* shutDown deletes all the RenderMan heap data and cleans up before the destructor is run.
*/
void RenderMan::shutDown()
{
	//clean up text stuff
	glDeleteLists(textBase, 96);
	delete[] lightModel;
}