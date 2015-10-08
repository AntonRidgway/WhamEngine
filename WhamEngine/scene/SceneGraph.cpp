#include "stdafx.h"

#include "SceneGraph.h"

SGRoot::SGRoot()
{
	sceneEList = new Entity*[10];//[S_LIST_MAX];
	hudEList = new Entity*[5];//[H_LIST_MAX];
	lightEList = new Light*[8];//[L_LIST_MAX];
	numSceneE = 0;
	numHudE = 0;
	numLightE = 0;
}
SGRoot::~SGRoot()
{
	//delete[] lightEList;
	//delete[] hudEList;
	//delete[] sceneEList;
}
Node SGRoot::getNode()
{
	return rootNode;
}
void SGRoot::attachChild( Geometry* c )
{
	rootNode.attachChild(c);
}
/**
	* Eventually, traverse the scene graph, and provide a list of all
	* Geometries to be rendered, with their rotations and such in absolute
	* coordinates.
	*/
void SGRoot::makeArray(Geometry** list, int& listLen)
{
	//rootNode.makeArray(list, listLen);
}

//-------------------------------------------------------------------------------------------------
//Entity List

void SGRoot::addSceneE( Entity* x )
{
	if( numSceneE < S_LIST_MAX )
	{
		sceneEList[numSceneE] = x;
		numSceneE++;
	}
}
void SGRoot::removeSceneE( unsigned int index )
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
Entity* SGRoot::getSceneE( unsigned int index )
{
	if(index >= 0 && index < numSceneE)
	{
		return sceneEList[index];
	}
	return NULL;
}
Entity** SGRoot::getSceneEList()
{
	return sceneEList;
}
unsigned int SGRoot::getNumSceneE()
{
	return numSceneE;
}

//-------------------------------------------------------------------------------------------------
//Hud List

void SGRoot::addHudE( Entity* x )
{
	if( numHudE < H_LIST_MAX )
	{
		hudEList[numHudE] = x;
		numHudE++;
	}
}
void SGRoot::removeHudE( unsigned int index )
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
Entity* SGRoot::getHudE( unsigned int index )
{
	if(index >= 0 && index < numHudE)
	{
		return hudEList[index];
	}
	return NULL;
}
Entity** SGRoot::getHudEList()
{
	return hudEList;
}
unsigned int SGRoot::getNumHudE()
{
	return numHudE;
}

//-------------------------------------------------------------------------------------------------
//Light List

void SGRoot::addLightE( Light* x )
{
	if( numLightE < L_LIST_MAX )
	{
		lightEList[numLightE] = x;
		numLightE++;
	}
}
void SGRoot::removeLightE( unsigned int index )
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
Light* SGRoot::getLightE( unsigned int index )
{
	if(index >= 0 && index < numLightE)
	{
		return lightEList[index];
	}
	return NULL;
}
Light** SGRoot::getLightEList()
{
	return lightEList;
}
unsigned int SGRoot::getNumLightE()
{
	return numLightE;
}