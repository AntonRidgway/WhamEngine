#include "stdafx.h"
#include <string>
#include <fstream>
#include <streambuf>
#include <RapidXML\rapidxml.hpp>
#include "FileSystemMan.h"
#include "resources/ResourceMan.h"
#include "scene/Box.h"
#include "scene/Pyramid.h"
#include "scene/Quad.h"
#include "scene/Quadric.h"
#include "scene/SceneGraph.h"
#include "scene/StateMan.h"

void FileSystemMan::startUp()
{
	//Load Textures from Files
	boxTex = ResourceMan::getInstance().getTexture("box.bmp");
	blankTex = ResourceMan::getInstance().getTexture("blank.bmp");
	brickTex = ResourceMan::getInstance().getTexture("brick.bmp");
	carpetTex = ResourceMan::getInstance().getTexture("carpet.bmp");
	eyeTex = ResourceMan::getInstance().getTexture("eyeball.bmp");
	skyTex = ResourceMan::getInstance().getTexture("sky.bmp");
	wallTex = ResourceMan::getInstance().getTexture("wall.bmp");
	wallPicTex = ResourceMan::getInstance().getTexture("wallpic.bmp");

	dullMat = new Material();
	slimeMat = new Material(0.0f,0.0f,0.0f,1.0f,0.2f,0.2f,0.2f,1.0f,0.8f,0.8f,0.8f,1.0f,0.3f,0.3f,0.3f,0.1f,100.0f);
	shinyMat = new Material(0.8f,0.8f,0.8f,1.0f,0.8f,0.8f,0.8f,1.0f,0.2f,0.2f,0.2f,1.0f,0.1f,0.1f,0.1f,1.0f,0.0f);
	rShinyMat = new Material(0.8f,0.0f,0.0f,1.0f,0.8f,0.8f,0.8f,1.0f,0.2f,0.2f,0.2f,1.0f,0.1f,0.1f,0.1f,1.0f,0.0f);
	gShinyMat = new Material(0.0f,0.8f,0.0f,1.0f,0.8f,0.8f,0.8f,1.0f,0.2f,0.2f,0.2f,1.0f,0.1f,0.1f,0.1f,1.0f,0.0f);
	bShinyMat = new Material(0.0f,0.0f,0.8f,1.0f,0.8f,0.8f,0.8f,1.0f,0.2f,0.2f,0.2f,1.0f,0.1f,0.1f,0.1f,1.0f,0.0f);

	std::string fileName("level1.lvl");
	loadLevel(fileName);
}
void FileSystemMan::shutDown()
{
	delete dullMat;
	delete slimeMat;
	delete shinyMat;
	delete rShinyMat;
	delete gShinyMat;
	delete bShinyMat;

	//clean up Stuff
	/*
	Light** lightList = StateMan::getInstance().getSceneGraph()->getLightEList();
	int lLen = StateMan::getInstance().getSceneGraph()->getNumLightE();
	for(int i = 0; i < lLen; i++) 
	{
		if(lightList[i] != NULL) delete lightList[i];
	}
	
	Entity** hudList = StateMan::getInstance().getSceneGraph()->getHudEList();
	int hLen = StateMan::getInstance().getSceneGraph()->getNumHudE();
	for(int i = 0; i < hLen; i++) delete hudList[i];

	Entity** geomList = StateMan::getInstance().getSceneGraph()->getSceneEList();
	int gLen = StateMan::getInstance().getSceneGraph()->getNumSceneE();
	for(int i = 0; i < gLen; i++) delete geomList[i];*/
}
void FileSystemMan::loadLevel( std::string fileName )
{
	//Eventually, this should be read in from a file; for now it is hard-coded.
	//std::ifstream reader("scene.xml");
	//reader.seekg(0, std::ios::end);
	//int fileLen = reader.tellg();
	//reader.seekg(0, std::ios::beg);
	//char* text = new char[fileLen];
	//reader.read(text, fileLen);
	//reader.close();
	//rapidxml::xml_document<> doc;
	//doc.parse<0>(text);
	//rapidxml::xml_node<>* nextNode = doc.first_node("Entity");
	//while (nextNode != 0) {
	//	//Construct the entity
	//	nextNode = nextNode->next_sibling();
	//}


	//---------------------------------------------------------------------------------------------
	//Load Scene Entities (Geometries & Quadrics)
	
	//First, create the walls of our bounding box
	//floor
	
	TriMesh* shape = new Quad(30.0f,30.0f);
	Geometry* simpleGeom = new Geometry(shape, carpetTex, dullMat);
	simpleGeom->rotateX(1.571f);
	simpleGeom->translate(0.0f,-15.0f,15.0f);
	StateMan::getInstance().getSceneGraph()->addSceneE(simpleGeom);
	
	//north wall
	shape = new Quad(30.0f,30.0f);
	simpleGeom = new Geometry(shape, wallTex, dullMat);
	simpleGeom->translate(0.0f,-15.0f,-15.0f);
	StateMan::getInstance().getSceneGraph()->addSceneE(simpleGeom);

	//south wall
	shape = new Quad(30.0f,30.0f);
	simpleGeom = new Geometry(shape, wallTex, dullMat);
	simpleGeom->rotateY(3.1415f);
	simpleGeom->translate(0.0f,-15.0f,15.0f);
	StateMan::getInstance().getSceneGraph()->addSceneE(simpleGeom);

	//west wall
	shape = new Quad(30.0f,30.0f);
	simpleGeom = new Geometry(shape, wallTex, dullMat);
	simpleGeom->rotateY(-1.571f);
	simpleGeom->translate(-15.0f,-15.0f,0.0f);
	StateMan::getInstance().getSceneGraph()->addSceneE(simpleGeom);

	//east wall
	shape = new Quad(30.0f,30.0f);
	simpleGeom = new Geometry(shape, wallPicTex, dullMat);
	simpleGeom->rotateY(1.571f);
	simpleGeom->translate(15.0f,-15.0f,0.0f);
	StateMan::getInstance().getSceneGraph()->addSceneE(simpleGeom);

	//sky
	shape = new Quad(30.0f,30.0f);
	simpleGeom = new Geometry(shape, skyTex, dullMat);
	simpleGeom->rotateX(-1.571f);
	simpleGeom->translate(0.0f,15.0f,-15.0f);
	StateMan::getInstance().getSceneGraph()->addSceneE(simpleGeom);

	//tall box
	shape = new Box(2.0f,1.5f,3.0f);
	simpleGeom = new Geometry(shape, boxTex, dullMat);
	simpleGeom->translate(2.3f,0.0f,-7.5f);
	simpleGeom->rotateY(0.3f);
	StateMan::getInstance().getSceneGraph()->addSceneE(simpleGeom);
	
	//Tiny Box
	shape = new Box(1.0f,1.0f,1.0f);
	simpleGeom = new Geometry(shape, brickTex, dullMat);
	simpleGeom->translate(3.3f, 0.0f, -7.5f);
	simpleGeom->rotateY(0.6f);
	StateMan::getInstance().getSceneGraph()->addSceneE(simpleGeom);
	
	//Mid Box
	shape = new Box(2.0f,2.0f,2.0f);
	simpleGeom = new Geometry(shape, brickTex, dullMat);
	simpleGeom->translate(4.3f, 0.0f, -7.5f);
	simpleGeom->rotateY(0.9f);
	StateMan::getInstance().getSceneGraph()->addSceneE(simpleGeom);

	//Regular Pyramid
	shape = new Pyramid(1.0f,2.0f);
	simpleGeom = new Geometry(shape, brickTex, dullMat);
	simpleGeom->translate(5.3f, 0.0f, -7.5f);
	simpleGeom->rotateY(1.2f);
	StateMan::getInstance().getSceneGraph()->addSceneE(simpleGeom);
	
	//tall pyramid
	shape = new Pyramid(1.0f, 3.0f);
	simpleGeom = new Geometry(shape, wallTex, dullMat);
	simpleGeom->translate(6.3f, 0.0f, -7.5f);
	simpleGeom->rotateY(1.5f);
	StateMan::getInstance().getSceneGraph()->addSceneE(simpleGeom);

	//quadrics
	StateMan::getInstance().getSceneGraph()->addSceneE(new QuadricSphere(eyeTex, slimeMat,-5.0f,5.0f,0.0f, 1.5f,8,5, GLU_FILL,GLU_SMOOTH,GLU_OUTSIDE,GL_TRUE));
	StateMan::getInstance().getSceneGraph()->addSceneE(new QuadricSphere(eyeTex, slimeMat,-5.0f,5.0f,0.0f, 0.5f,6,4, GLU_FILL,GLU_SMOOTH,GLU_OUTSIDE,GL_TRUE));

	//Loaded Mesh
	LoadedGeometry* loadedGeom = NULL;
	ResourceMan::getInstance().LoadMesh("C:\\Users\\Anton\\Desktop\\hm1\\HelloMagicv1\\Debug\\boblampclean.md5mesh", loadedGeom);
	if(loadedGeom!=NULL)
	{
		StateMan::getInstance().getSceneGraph()->addSceneE(loadedGeom);
		loadedGeom->translateY(-1.5);
		loadedGeom->rotateX(1.7);
		loadedGeom->setScale(0.1f);
	}
	else
	{
		shape = new Box(1.0f, 1.0f, 1.0f);
		simpleGeom = new Geometry(shape, blankTex, shinyMat);
		StateMan::getInstance().getSceneGraph()->addSceneE(simpleGeom);
	}

	/*loadedGeom = NULL;
	ResourceMan::getInstance().LoadMesh("C:\\Users\\Anton\\Desktop\\hm1\\HelloMagicv1\\Debug\\Sinbad.3ds", loadedGeom);
	StateMan::getInstance().getSceneGraph()->addSceneE(loadedGeom);*/

	
	StateMan::getInstance().getSceneGraph()->addSceneE(new QuadricSphere(blankTex, bShinyMat, -7.0f,7.0f,7.0f,0.3f,6,6,GLU_FILL,GLU_SMOOTH,GLU_OUTSIDE,GL_TRUE));
	StateMan::getInstance().getSceneGraph()->addSceneE(new QuadricSphere(blankTex, gShinyMat, 0.0f,0.0f,-7.0f,0.3f,6,6,GLU_FILL,GLU_SMOOTH,GLU_OUTSIDE,GL_TRUE));
	StateMan::getInstance().getSceneGraph()->addSceneE(new QuadricSphere(blankTex, rShinyMat, 7.0f,-7.0f,3.0f,0.3f,6,6,GLU_FILL,GLU_SMOOTH,GLU_OUTSIDE,GL_TRUE));

	//---------------------------------------------------------------------------------------------
	//Load HUD Entities
	
	//---------------------------------------------------------------------------------------------
	//Load Lights
	StateMan::getInstance().getSceneGraph()->addLightE(new Light(1.0f, 1.0f, 1.0f, 1.0f,
									0.0f, 0.0f, 0.0f, 1.0f,
									0.0f, 0.0f, 0.0f, 1.0f,
									0.0f, 0.0f, 0.0f,
									0.0f, 0.0f, 0.0f));
	StateMan::getInstance().getSceneGraph()->addLightE(new PointLight(0.0f,0.0f,0.8f,1.0f,
									0.0f,0.0f,3.2f,1.0f,
									0.5f,0.5f,0.5f,1.0f,
									-7.0f,7.0f,7.0f,
									0.9f,0.1f,0.01f));
	StateMan::getInstance().getSceneGraph()->addLightE(new PointLight(0.0f,0.8f,0.0f,1.0f,
									0.0f,3.2f,0.0f,1.0f,
									0.5f,0.5f,0.5f,1.0f,
									0.0f,0.0f,-7.0f,
									0.9f,0.1f,0.01f));
	StateMan::getInstance().getSceneGraph()->addLightE(new PointLight(0.8f,0.0f,0.0f,1.0f,
									3.2f,0.0f,0.0f,1.0f,
									0.5f,0.5f,0.5f,1.0f,
									7.0f,-7.0f,3.0f,
									0.9f,0.1f,0.01f));
	StateMan::getInstance().getSceneGraph()->addLightE(new DirLight(0.01f,0.0f,0.04f,1.0f,
									0.16f,0.14f,0.06f,1.0f,
									0.04f,0.038f,0.014f,1.0f,
									-1.0f,-1.0f,-1.0f));
}