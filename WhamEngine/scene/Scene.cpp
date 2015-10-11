#include "stdafx.h"

#include "Scene.h"

Scene::Scene()
{
	sceneEList = new Entity*[10];//[S_LIST_MAX];
	hudEList = new HUDText*[5];//[H_LIST_MAX];
	lightEList = new Light*[8];//[L_LIST_MAX];
	numSceneE = 0;
	numHudE = 0;
	numLightE = 0;
}
Scene::~Scene()
{
	delete[] lightEList;
	delete[] hudEList;
	delete[] sceneEList;
}

//-------------------------------------------------------------------------------------------------
//Entity List

void Scene::addSceneE( Entity* x )
{
	if( numSceneE < S_LIST_MAX )
	{
		sceneEList[numSceneE] = x;
		numSceneE++;
	}
}
void Scene::removeSceneE( unsigned int index )
{
	if(numSceneE > 0 && index >= 0 && index < numSceneE)
	{
		for(unsigned int i = index; i < numSceneE-1; i++)
		{
			sceneEList[i] = sceneEList[i+1];
		}
		sceneEList[numSceneE-1] = NULL;
		numSceneE--;
	}
}
Entity* Scene::getSceneE( unsigned int index )
{
	if(index >= 0 && index < numSceneE)
	{
		return sceneEList[index];
	}
	return NULL;
}
Entity** Scene::getSceneEList()
{
	return sceneEList;
}
unsigned int Scene::getNumSceneE()
{
	return numSceneE;
}

//-------------------------------------------------------------------------------------------------
//Hud List

void Scene::addHudE( HUDText* x )
{
	if( numHudE < H_LIST_MAX )
	{
		hudEList[numHudE] = x;
		numHudE++;
	}
}
void Scene::removeHudE( unsigned int index )
{
	if(numHudE > 0 && index >= 0 && index < numHudE)
	{
		for(unsigned int i = index; i < numHudE-1; i++)
		{
			hudEList[i] = hudEList[i+1];
		}
		hudEList[numHudE-1] = NULL;
		numHudE--;
	}
}
HUDText* Scene::getHudE( unsigned int index )
{
	if(index >= 0 && index < numHudE)
	{
		return hudEList[index];
	}
	return NULL;
}
HUDText** Scene::getHudEList()
{
	return hudEList;
}
unsigned int Scene::getNumHudE()
{
	return numHudE;
}

//-------------------------------------------------------------------------------------------------
//Light List

void Scene::addLightE( Light* x )
{
	if( numLightE < L_LIST_MAX )
	{
		lightEList[numLightE] = x;
		numLightE++;
	}
}
void Scene::removeLightE( unsigned int index )
{
	if(numLightE > 0 && index >= 0 && index < numLightE)
	{
		for(unsigned int i = index; i < numLightE-1; i++)
		{
			lightEList[i] = lightEList[i+1];
		}
		lightEList[numLightE-1] = NULL;
		numLightE--;
	}
}
Light* Scene::getLightE( unsigned int index )
{
	if(index >= 0 && index < numLightE)
	{
		return lightEList[index];
	}
	return NULL;
}
Light** Scene::getLightEList()
{
	return lightEList;
}
unsigned int Scene::getNumLightE()
{
	return numLightE;
}