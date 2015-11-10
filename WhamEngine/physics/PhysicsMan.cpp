#include "stdafx.h"

#include "PhysicsMan.h"

void PhysicsMan::startUp(Entity** SGEin)
{
	SGEntities = SGEin;

	//initialize the physics engine stuff
	myBroadphase = new btDbvtBroadphase();
	myClsnCfg = new btDefaultCollisionConfiguration();
	myClsnDpcr = new btCollisionDispatcher(myClsnCfg);
	mySICS = new btSequentialImpulseConstraintSolver;
	myCShapes = new btAlignedObjectArray<btCollisionShape*>();
	myWorld = new btDiscreteDynamicsWorld(myClsnDpcr,myBroadphase,mySICS,myClsnCfg);
	myWorld->setGravity(btVector3(0,-gravityStrength,0));
}
void PhysicsMan::shutDown()
{
	//Remove the rigid bodies from the dynamics world and delete them.
	for (int i = myWorld->getNumCollisionObjects()-1; i >= 0; i--)
	{
		btCollisionObject* obj = myWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		myWorld->removeCollisionObject( obj );
		delete obj;
	}
	
	//Delete collision shapes.
	for (int j = 0; j < myCShapes->size(); j++)
	{
		btCollisionShape* shape = (*myCShapes)[j];
		(*myCShapes)[j] = 0;
		delete shape;
	}
	
	delete myWorld;			//delete dynamics world
	myCShapes->clear();
	delete myCShapes;
	delete mySICS;			//delete solver
	delete myBroadphase;	//delete broadphase
	delete myClsnDpcr;		//delete dispatcher
	delete myClsnCfg;		//delete collision configuration

	hullData.clear();
}

void PhysicsMan::step(double secsPassed)
{
	myWorld->stepSimulation(secsPassed);
	
	for (int i = 0; i < myWorld->getNumCollisionObjects(); i++) {
		btCollisionObject* obj = myWorld->getCollisionObjectArray()[i];
		if (physSpatialMap[obj->getCollisionShape()])
		{
			btRigidBody* body = btRigidBody::upcast(obj);
			if (body && body->getMotionState())
			{
				btTransform trans;
				body->getMotionState()->getWorldTransform(trans);
				btVector3 locVec = trans.getOrigin();
				btQuaternion rotQuat = trans.getRotation().normalized();
				Spatial* spatial = physSpatialMap[obj->getCollisionShape()];
				spatial->setTranslation(locVec.getX(), locVec.getY(), locVec.getZ());
				spatial->setRotation(rotQuat.getW(), rotQuat.getX(), rotQuat.getY(), rotQuat.getZ());
			}
		}
	}
}
void PhysicsMan::setGravity(Vector3f newDir)
{
	btVector3 newGrav(newDir.getEntry(0),newDir.getEntry(1),newDir.getEntry(2));
	myWorld->setGravity(newGrav*10);
	for(int i = 0; i < myWorld->getNumCollisionObjects(); i++)
	{
		myWorld->getCollisionObjectArray()[i]->activate();
	}
}

void PhysicsMan::addBox(Spatial* spatial, float mass, Vector3f inertia, Vector3f location, Quaternionf rotation, Vector3f halfExtents, float restitution)
{
	btCollisionShape* boxShape = new btBoxShape(btVector3(halfExtents.getEntry(0), halfExtents.getEntry(1), halfExtents.getEntry(2)));
	addBody(spatial, boxShape, mass, inertia, &location, &rotation, restitution);
}
void PhysicsMan::addCapsule(Spatial* spatial, float mass, Vector3f inertia, Vector3f location, Quaternionf rotation, float radius, float height, float restitution)
{
	btCollisionShape* capsShape = new btCapsuleShape(radius, height);
	addBody(spatial, capsShape, mass, inertia, &location, &rotation, restitution);
}
void PhysicsMan::addCone(Spatial* spatial, float mass, Vector3f inertia, Vector3f location, Quaternionf rotation, float radius, float height, float restitution)
{
	btCollisionShape* coneShape = new btConeShape(radius, height);
	addBody(spatial, coneShape, mass, inertia, &location, &rotation, restitution);
}
void PhysicsMan::addCylinder(Spatial* spatial, float mass, Vector3f inertia, Vector3f location, Quaternionf rotation, Vector3f halfExtents, float restitution)
{
	btCollisionShape* cylShape = new btCylinderShape(btVector3(halfExtents.getEntry(0), halfExtents.getEntry(1), halfExtents.getEntry(2)));
	addBody(spatial, cylShape, mass, inertia, &location, &rotation, restitution);
}
void PhysicsMan::addSphere(Spatial* spatial, float mass, Vector3f inertia, Vector3f location, Quaternionf rotation, float radius, float restitution)
{
	btCollisionShape* sphereShape = new btSphereShape(radius);
	addBody(spatial, sphereShape, mass, inertia, &location, &rotation, restitution);
}
void PhysicsMan::addConvexHull(Spatial* spatial, float mass, Vector3f inertia, Vector3f location, Quaternionf rotation, GLfloat* points, int numPoints, float restitution)
{
	btScalar* sPoints = new btScalar[numPoints*3];
	for (int i = 0; i < numPoints * 3; i++)
		sPoints[i] = points[i];
	btCollisionShape* hullShape = new btConvexHullShape(sPoints, numPoints, sizeof(btScalar) * 3);
	addBody(spatial, hullShape, mass, inertia, &location, &rotation, restitution);
	hullData.push_back(sPoints);
}
void PhysicsMan::addPlane(Spatial* spatial, float mass, Vector3f inertia, Vector3f normal, float offset, float restitution)
{
	btCollisionShape* planeShape = new btStaticPlaneShape(
		btVector3(normal.getEntry(0), normal.getEntry(1), normal.getEntry(2)), btScalar(offset));
	addBody(spatial, planeShape, mass, inertia, NULL, NULL, restitution);
}
/*
 * 	The rigid body added is static if mass is 0.
 */
void PhysicsMan::addBody(Spatial* spatial, btCollisionShape* physShape, float mass, Vector3f inertia, Vector3f* location, Quaternionf* rotation, float restitution)
{
	myCShapes->push_back(physShape);
	btTransform myTransform;
	myTransform.setIdentity();
	btScalar myMass(mass);
	bool isDynamic = (myMass != 0.f);
	btVector3 localInertia(inertia.getEntry(0), inertia.getEntry(1), inertia.getEntry(2));
	if (isDynamic)
		physShape->calculateLocalInertia(myMass, localInertia);

	if (location != NULL && rotation != NULL)
	{
		myTransform.setOrigin(btVector3(location->getEntry(0), location->getEntry(1), location->getEntry(2)));
		myTransform.setRotation(btQuaternion(rotation->getW(), rotation->getX(), rotation->getY(), rotation->getZ()));
	}

	btDefaultMotionState* myMotionState = new btDefaultMotionState(myTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(myMass, myMotionState, physShape, localInertia);
	if(restitution >= 0) rbInfo.m_restitution = restitution;
	btRigidBody* body = new btRigidBody(rbInfo);
	myWorld->addRigidBody(body);

	physSpatialMap[physShape] = spatial;
}
bool PhysicsMan::removeBody(Spatial* spatial)
{
	for (int i = 0; i < myWorld->getNumCollisionObjects(); i++) {
		btCollisionObject* obj = myWorld->getCollisionObjectArray()[i];
		if (physSpatialMap[obj->getCollisionShape()] == spatial) {
			btCollisionShape* shape = obj->getCollisionShape();
			myWorld->removeCollisionObject(obj);
			delete obj;
			delete shape;
			return TRUE;
		}
	}
	return FALSE;
}