#ifndef WE_PHYSICSMAN_H
#define WE_PHYSICSMAN_H

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include "scene/entities/Entity.h"
#include <map>
#include <vector>

static const float DEF_RESTITUTION = -1;

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
	std::map<btCollisionShape*, Spatial*> physSpatialMap;
	std::vector<btScalar*> hullData;

	float gravityStrength = 10;

public:
	static PhysicsMan& getInstance() {
		static PhysicsMan instance;
		return instance; //Return a reference only.
	}
	void startUp(Entity** SGEin);
	void shutDown();
	void step(double secsPassed);
	void setGravity(Vector3f newDir);
	void addBox(Spatial* spatial, float mass, Vector3f inertia, Vector3f location, Quaternionf rotation, Vector3f halfExtents, float restitution = DEF_RESTITUTION);
	void addCapsule(Spatial* spatial, float mass, Vector3f inertia, Vector3f location, Quaternionf rotation, float radius, float height, float restitution = DEF_RESTITUTION);
	void addCone(Spatial* spatial, float mass, Vector3f inertia, Vector3f location, Quaternionf rotation, float radius, float height, float restitution = DEF_RESTITUTION);
	void addCylinder(Spatial* spatial, float mass, Vector3f inertia, Vector3f location, Quaternionf rotation, Vector3f halfExtents, float restitution = DEF_RESTITUTION);
	void addSphere(Spatial* spatial, float mass, Vector3f inertia, Vector3f location, Quaternionf rotation, float radius, float restitution = DEF_RESTITUTION);
	void addConvexHull(Spatial* spatial, float mass, Vector3f inertia, Vector3f location, Quaternionf rotation, GLfloat* points, int numPoints, float restitution = DEF_RESTITUTION);
	void addPlane(Spatial* spatial, float mass, Vector3f inertia, Vector3f normal, float offset, float restitution = DEF_RESTITUTION);
	void addBody(Spatial* spatial, btCollisionShape* physShape, float mass, Vector3f inertia, Vector3f* location, Quaternionf* rotation, float restitution = DEF_RESTITUTION);
	bool removeBody(Spatial* spatial);
};

#endif