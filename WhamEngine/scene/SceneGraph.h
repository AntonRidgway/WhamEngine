#ifndef WE_SCENEGRAPH_H
#define WE_SCENEGRAPH_H

#include "Node.h"
#include "Light.h"

static const unsigned int S_LIST_MAX = 30;
static const unsigned int H_LIST_MAX = 5;
static const unsigned int L_LIST_MAX = 8;

class SGRoot
{
private:
	Node rootNode;
	Entity** sceneEList;
	Entity** hudEList;
	Light** lightEList;
	unsigned int numSceneE;
	unsigned int numHudE;
	unsigned int numLightE;

public:
	SGRoot();
	~SGRoot();
	Node getNode();
	void attachChild( Geometry* c );
	void makeArray(Geometry** list, int& listLen);

	void addSceneE( Entity* x );
	void removeSceneE( unsigned int index );
	Entity* getSceneE( unsigned int index );
	Entity** getSceneEList();
	unsigned int getNumSceneE();

	void addHudE( Entity* x );
	void removeHudE( unsigned int index );
	Entity* getHudE( unsigned int index );
	Entity** getHudEList();
	unsigned int getNumHudE();

	void addLightE( Light* x );
	void removeLightE( unsigned int index );
	Light* getLightE( unsigned int index );
	Light** getLightEList();
	unsigned int getNumLightE();
};

#endif