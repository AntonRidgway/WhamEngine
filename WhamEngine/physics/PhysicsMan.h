#ifndef WE_PHYSICSMAN_H
#define WE_PHYSICSMAN_H

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include "scene\Entity.h"

class PhysicsMan
{
private:
	PhysicsMan() {} //Make constructor private.
	PhysicsMan(PhysicsMan const&) = delete; //Disallow the copy constructor.
	void operator=(PhysicsMan const&) = delete; //Disallow copies of the singleton.

	btBroadphaseInterface* myBroadphase;
	btDefaultCollisionConfiguration* myClsnCfg;
	btCollisionDispatcher* myClsnDpcr;
	btSequentialImpulseConstraintSolver* mySICS;
	btDiscreteDynamicsWorld* myWorld;
	
	btAlignedObjectArray<btCollisionShape*>* myCShapes;
	Entity** SGEntities;
	int* physIDs;
	btScalar* points;
	btScalar* points2;

public:
	static PhysicsMan& getInstance() {
		static PhysicsMan instance;
		return instance; //Return a reference only.
	}
	void startUp(Entity** SGEin);
	void shutDown();
	void step(double secsPassed);
	void setGravity(Vector3f newDir);
	void shootBall(Vector3f loc, Vector3f dir);
};

#endif