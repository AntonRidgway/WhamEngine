#include "stdafx.h"

#include "scene\StateMan.h"
#include "RenderMan.h"
#include <gl\GL.h>
#include <gl\freeglut.h>

void renderWindow(void) {
	RenderMan::getInstance().renderScene();
}
void reshapeWindow(int width, int height) {
	RenderMan::getInstance().reshape(width, height);
}
void RenderMan::startUp(int width, int height)
{
	//start various rendering stuff
	myScene = StateMan::getInstance().getScene();
	myCam = StateMan::getInstance().getCamera();

	//Create lists of elements to be rendered.
	sceneEList = myScene->getSceneEList();
	sEListLen = myScene->getNumSceneE();
	hudList = myScene->getHudEList();
	hListLen = myScene->getNumHudE();
	lightList = myScene->getLightEList();
	lListLen = myScene->getNumLightE();

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
	enableGlLights();
	updateGlLightSpecs();

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
	delete[] lightModel;
}
/**
* renderScene is used in the game loop to render the scene.
*/
void RenderMan::renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	StateMan::getInstance().updateState();
	updateGlLightSpecs();
	for (int i = 0; i < sEListLen; i++)
		sceneEList[i]->render();
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	for (int i = 0; i < hListLen; i++)
		hudList[i]->render();
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	// copy the back buffer into the front buffer
	glutSwapBuffers();
	glutPostRedisplay();
}
void RenderMan::reshape(int width, int height) {
	//Set up projection for the new window.
	myCam->setAspectRatio(((double)width) / height);
	glViewport(0, 0, width, height);
}

/**
 * createLights sets the OpenGL lights to reflect the engine's own data structures, in lListLen.
 */
void RenderMan::enableGlLights()
{
	for (int i = 0; i < MAX_NUM_LIGHTS; i++) {
		if (lListLen > i) glEnable(LIGHT_CONSTS[i]);
		else glDisable(LIGHT_CONSTS[i]);
	}
}

/**
 * updateLights updates the OpenGL lights; this should be run for each render.
 */
void RenderMan::updateGlLightSpecs()
{
	for(int i = 0; i < lListLen; i++)
	{
		glLightfv(LIGHT_CONSTS[i],GL_AMBIENT,lightList[i]->getAmbient()->getData());
		glLightfv(LIGHT_CONSTS[i],GL_DIFFUSE,lightList[i]->getDiffuse()->getData());
		glLightfv(LIGHT_CONSTS[i],GL_SPECULAR,lightList[i]->getSpecular()->getData());
		glLightfv(LIGHT_CONSTS[i],GL_POSITION,lightList[i]->getPosition()->getArray()); // direction for directional light
		glLightf(LIGHT_CONSTS[i],GL_CONSTANT_ATTENUATION, lightList[i]->getAttenuation(0));
        glLightf(LIGHT_CONSTS[i],GL_LINEAR_ATTENUATION, lightList[i]->getAttenuation(1));
        glLightf(LIGHT_CONSTS[i],GL_QUADRATIC_ATTENUATION, lightList[i]->getAttenuation(2));

		if(lightList[i]->getLightType() == 3)
		{
			glLightfv(LIGHT_CONSTS[i],GL_SPOT_DIRECTION,lightList[i]->getDirection()->getArray());
			glLightf(LIGHT_CONSTS[i],GL_SPOT_EXPONENT,lightList[i]->getExponent());
			glLightf(LIGHT_CONSTS[i],GL_SPOT_CUTOFF,lightList[i]->getCutoff());
		}
	}
}