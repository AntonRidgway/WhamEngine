#ifndef WE_SCENE_H
#define WE_SCENE_H

#include "entities/Entity.h"
#include "lights/Light.h"
#include "hud/HUDText.h"

static const unsigned int S_LIST_MAX = 30;
static const unsigned int H_LIST_MAX = 5;
static const unsigned int L_LIST_MAX = 8;

class Scene
{
private:
	Entity** sceneEList;
	HUDText** hudEList;
	Light** lightEList;
	unsigned int numSceneE;
	unsigned int numHudE;
	unsigned int numLightE;

public:
	Scene();
	~Scene();

	void addSceneE( Entity* x );
	void removeSceneE( unsigned int index );
	Entity* getSceneE( unsigned int index );
	Entity** getSceneEList();
	unsigned int getNumSceneE();

	void addHudE(HUDText* x );
	void removeHudE( unsigned int index );
	HUDText* getHudE( unsigned int index );
	HUDText** getHudEList();
	unsigned int getNumHudE();

	void addLightE( Light* x );
	void removeLightE( unsigned int index );
	Light* getLightE( unsigned int index );
	Light** getLightEList();
	unsigned int getNumLightE();
};

#endif