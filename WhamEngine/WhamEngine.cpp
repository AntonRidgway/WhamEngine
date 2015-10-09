// WhamEngine, by Anton Ridgway 2012.
// Revised for the modern day in 2015.
// Based on the Wild Magic Engine 3 by David Eberly

#include "stdafx.h"
#include "WhamEngine.h"
#include "RenderMan.h"
#include "filesys/FileSystemMan.h"
#include "input/InputMan.h"
#include "scene/StateMan.h"
#include <string>
#include <gl/freeglut.h>

const int windowWidth = 800;
const int windowHeight = 600;
const std::string roomFile = "TestRoom.xml";

/**
 * main - Sets up the GLUT window, and manages startup and shutdown
 * for the five main program components.
 */
int main(int argc, char **argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("WhamEngine Test");
	
	// Start main program components and register callbacks.
	InputMan::getInstance().startUp();
	StateMan::getInstance().startUp(windowWidth,windowHeight);
	FileSystemMan::getInstance().startUp();
	FileSystemMan::getInstance().loadLevel(roomFile, StateMan::getInstance().getSceneGraph());
	RenderMan::getInstance().startUp(windowWidth,windowHeight);

	glutMainLoop(); // enter GLUT event processing cycle

	//Shut down components in reverse order.
	RenderMan::getInstance().shutDown();
	FileSystemMan::getInstance().shutDown();
	StateMan::getInstance().shutDown();
	InputMan::getInstance().shutDown();
	
	return 1;
}