#include "stdafx.h"

#include "PhysicsMan.h"

void PhysicsMan::startUp(Entity** SGEin)
{
	//initialize the physics engine stuff
	myBroadphase = new btDbvtBroadphase();
	myClsnCfg = new btDefaultCollisionConfiguration();
	myClsnDpcr = new btCollisionDispatcher(myClsnCfg);
	mySICS = new btSequentialImpulseConstraintSolver;
	myCShapes = new btAlignedObjectArray<btCollisionShape*>();
	myWorld = new btDiscreteDynamicsWorld(myClsnDpcr,myBroadphase,mySICS,myClsnCfg);
	myWorld->setGravity(btVector3(0,-10,0));
	
	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0.0f,1.0f,0.0f),btScalar(-15));
	myCShapes->push_back(groundShape);
	btTransform groundTransform;
	groundTransform.setIdentity();
	{
		btScalar mass(0.);
		bool isDynamic = (mass != 0.f);	//rigidbody is dynamic if and only if mass is non zero, otherwise static
		btVector3 localInertia(0,0,0);
		if (isDynamic)
			groundShape->calculateLocalInertia(mass,localInertia);

		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,groundShape,localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		//add the body to the dynamics world
		myWorld->addRigidBody(body);
	}
	groundShape = new btStaticPlaneShape(btVector3(0.0f,-1.0f,0.0f),btScalar(-15));
	myCShapes->push_back(groundShape);
	{
		btScalar mass(0.);
		bool isDynamic = (mass != 0.f);	//rigidbody is dynamic if and only if mass is non zero, otherwise static
		btVector3 localInertia(0,0,0);
		if (isDynamic)
			groundShape->calculateLocalInertia(mass,localInertia);

		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,groundShape,localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		//add the body to the dynamics world
		myWorld->addRigidBody(body);
	}
	groundShape = new btStaticPlaneShape(btVector3(-1.0f,0.0f,0.0f),btScalar(-15));
	myCShapes->push_back(groundShape);
	{
		btScalar mass(0.);
		bool isDynamic = (mass != 0.f);	//rigidbody is dynamic if and only if mass is non zero, otherwise static
		btVector3 localInertia(0,0,0);
		if (isDynamic)
			groundShape->calculateLocalInertia(mass,localInertia);

		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,groundShape,localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		//add the body to the dynamics world
		myWorld->addRigidBody(body);
	}
	groundShape = new btStaticPlaneShape(btVector3(1.0f,0.0f,0.0f),btScalar(-15));
	myCShapes->push_back(groundShape);
	{
		btScalar mass(0.);
		bool isDynamic = (mass != 0.f);	//rigidbody is dynamic if and only if mass is non zero, otherwise static
		btVector3 localInertia(0,0,0);
		if (isDynamic)
			groundShape->calculateLocalInertia(mass,localInertia);

		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,groundShape,localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		//add the body to the dynamics world
		myWorld->addRigidBody(body);
	}
	groundShape = new btStaticPlaneShape(btVector3(0.0f,0.0f,-1.0f),btScalar(-15));
	myCShapes->push_back(groundShape);
	{
		btScalar mass(0.);
		bool isDynamic = (mass != 0.f);	//rigidbody is dynamic if and only if mass is non zero, otherwise static
		btVector3 localInertia(0,0,0);
		if (isDynamic)
			groundShape->calculateLocalInertia(mass,localInertia);

		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,groundShape,localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		//add the body to the dynamics world
		myWorld->addRigidBody(body);
	}
	groundShape = new btStaticPlaneShape(btVector3(0.0f,0.0f,1.0f),btScalar(-15));
	myCShapes->push_back(groundShape);
	{
		btScalar mass(0.);
		bool isDynamic = (mass != 0.f);	//rigidbody is dynamic if and only if mass is non zero, otherwise static
		btVector3 localInertia(0,0,0);
		if (isDynamic)
			groundShape->calculateLocalInertia(mass,localInertia);

		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,groundShape,localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		//add the body to the dynamics world
		myWorld->addRigidBody(body);
	}






	{//create a dynamic rigidbody
		btCollisionShape* colShape = new btBoxShape(btVector3(1.0,1.5,0.75));
		myCShapes->push_back(colShape);
		/// Create Dynamic Objects
		btTransform startTransform;
		startTransform.setIdentity();
		btScalar	mass(1.f);
		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);
		btVector3 localInertia(0,0,0);
		if (isDynamic)
			colShape->calculateLocalInertia(mass,localInertia);
		startTransform.setOrigin(btVector3(5,3,0));
		startTransform.setRotation(btQuaternion(0,1,1,1));
		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,colShape,localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		myWorld->addRigidBody(body);
	}
	{//create a dynamic rigidbody
		btCollisionShape* colShape = new btBoxShape(btVector3(0.5,0.5,0.5));
		myCShapes->push_back(colShape);
		/// Create Dynamic Objects
		btTransform startTransform;
		startTransform.setIdentity();
		btScalar	mass(0.3f);
		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);
		btVector3 localInertia(0,0,0);
		if (isDynamic)
			colShape->calculateLocalInertia(mass,localInertia);
		startTransform.setOrigin(btVector3(-3,10,0));
		startTransform.setRotation(btQuaternion(0,0,0,1));
		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,colShape,localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		myWorld->addRigidBody(body);
	}
	{//create a dynamic rigidbody
		btCollisionShape* colShape = new btBoxShape(btVector3(1,1,1));
		myCShapes->push_back(colShape);
		/// Create Dynamic Objects
		btTransform startTransform;
		startTransform.setIdentity();
		btScalar	mass(5.f);
		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);
		btVector3 localInertia(0,0,0);
		if (isDynamic)
			colShape->calculateLocalInertia(mass,localInertia);
		startTransform.setOrigin(btVector3(2,10,0));
		startTransform.setRotation(btQuaternion(0,1,1,1));
		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,colShape,localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		myWorld->addRigidBody(body);
	}
	{//create a dynamic rigidbody
		points = new btScalar[15];
		points[0] = -1; points[1] = 0; points[2]=1;
		points[3]=1; points[4]=0; points[5]=1;
		points[6]=1; points[7]=0; points[8]=-1;
		points[9]=-1; points[10]=0; points[11]=-1;
		points[12] = 0; points[13]=2; points[14]=0;
		btCollisionShape* colShape = new btConvexHullShape(points,5,sizeof(btScalar)*3);
		myCShapes->push_back(colShape);
		/// Create Dynamic Objects
		btTransform startTransform;
		startTransform.setIdentity();
		btScalar	mass(1.f);
		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);
		btVector3 localInertia(0,0,0);
		if (isDynamic)
			colShape->calculateLocalInertia(mass,localInertia);
		startTransform.setOrigin(btVector3(10,5,2));
		startTransform.setRotation(btQuaternion(0,1,1,1));
		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,colShape,localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		myWorld->addRigidBody(body);
	}
	{//create a dynamic rigidbody
		points2 = new btScalar[15];
		points2[0] = -1; points2[1] = 0; points2[2]=1;
		points2[3]=1; points2[4]=0; points2[5]=1;
		points2[6]=1; points2[7]=0; points2[8]=-1;
		points2[9]=-1; points2[10]=0; points2[11]=-1;
		points2[12] = 0; points2[13]=3; points2[14]=0;
		btCollisionShape* colShape = new btConvexHullShape(points2,5,sizeof(btScalar)*3);
		myCShapes->push_back(colShape);
		/// Create Dynamic Objects
		btTransform startTransform;
		startTransform.setIdentity();
		btScalar	mass(1.f);
		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);
		btVector3 localInertia(0,0,0);
		if (isDynamic)
			colShape->calculateLocalInertia(mass,localInertia);
		startTransform.setOrigin(btVector3(10,5,-2));
		startTransform.setRotation(btQuaternion(0,1,1,1));
		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,colShape,localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		myWorld->addRigidBody(body);
	}
	{//create a dynamic rigidbody
		btCollisionShape* colShape = new btSphereShape(btScalar(1.5f));
		myCShapes->push_back(colShape);
		/// Create Dynamic Objects
		btTransform startTransform;
		startTransform.setIdentity();
		btScalar	mass(0.1f);
		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);
		btVector3 localInertia(0,0,0);
		if (isDynamic)
			colShape->calculateLocalInertia(mass,localInertia);
		startTransform.setOrigin(btVector3(-5,5,0));
		startTransform.setRotation(btQuaternion(0,1,1,1));
		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,colShape,localInertia);
		rbInfo.m_restitution = 0.3f; //make more "bouncy"
		btRigidBody* body = new btRigidBody(rbInfo);

		myWorld->addRigidBody(body);
	}
	{//create a dynamic rigidbody
		btCollisionShape* colShape = new btSphereShape(btScalar(0.5f));
		myCShapes->push_back(colShape);
		/// Create Dynamic Objects
		btTransform startTransform;
		startTransform.setIdentity();
		btScalar	mass(0.05f);
		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);
		btVector3 localInertia(0,0,0);
		if (isDynamic)
			colShape->calculateLocalInertia(mass,localInertia);
		startTransform.setOrigin(btVector3(2,5,0));
		startTransform.setRotation(btQuaternion(0.0f,0.5f,0.7f,0.2f));
		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,colShape,localInertia);
		rbInfo.m_restitution = 0.3f; //make more "bouncy"
		btRigidBody* body = new btRigidBody(rbInfo);

		myWorld->addRigidBody(body);
	}
	{//create a dynamic rigidbody
		btCollisionShape* colShape = new btBoxShape(btVector3(3.0f,3.0f,3.0f));
		myCShapes->push_back(colShape);
		/// Create Dynamic Objects
		btTransform startTransform;
		startTransform.setIdentity();
		btScalar	mass(1.0f);
		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);
		btVector3 localInertia(0,0,0);
		if (isDynamic)
			colShape->calculateLocalInertia(mass,localInertia);
		startTransform.setOrigin(btVector3(2,5,0));
		startTransform.setRotation(btQuaternion(0.0f,0.5f,0.7f,0.2f));
		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,colShape,localInertia);
		//rbInfo.m_restitution = 0.3f; //make more "bouncy"
		btRigidBody* body = new btRigidBody(rbInfo);

	myWorld->addRigidBody(body);
	}
		{//create a dynamic rigidbody
		btCollisionShape* colShape = new btBoxShape(btVector3(3.0f,3.0f,3.0f));
		myCShapes->push_back(colShape);
		/// Create Dynamic Objects
		btTransform startTransform;
		startTransform.setIdentity();
		btScalar	mass(1.0f);
		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);
		btVector3 localInertia(0,0,0);
		if (isDynamic)
			colShape->calculateLocalInertia(mass,localInertia);
		startTransform.setOrigin(btVector3(2,5,0));
		startTransform.setRotation(btQuaternion(0.0f,0.5f,0.7f,0.2f));
		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,colShape,localInertia);
		//rbInfo.m_restitution = 0.3f; //make more "bouncy"
		btRigidBody* body = new btRigidBody(rbInfo);

		myWorld->addRigidBody(body);
	}

	SGEntities = SGEin;
	physIDs = new int[15];
	for(int i = 0; i < 6; i++) physIDs[i]=-1;
	for(int i = 6; i < 15; i++) physIDs[i]=i;

}
void PhysicsMan::shutDown()
{
	delete[] points2;
	delete[] points;
	SGEntities = NULL;
	
	//remove the rigidbodies from the dynamics world and delete them
	for (int i=myWorld->getNumCollisionObjects()-1; i>=0 ;i--)
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
	
	//delete collision shapes
	for (int j=0;j<myCShapes->size();j++)
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
}


void PhysicsMan::step(double secsPassed)
{
	myWorld->stepSimulation(10);
	
	for(int i = 6; i < 15; i++)
	{
		if(physIDs[i] != -1)
		{
			Entity* currEntity = SGEntities[i];
	
			btCollisionObject* obj = myWorld->getCollisionObjectArray()[physIDs[i]];
			btRigidBody* body = btRigidBody::upcast(obj);

			if (body && body->getMotionState())
			{
				btTransform trans;
				body->getMotionState()->getWorldTransform(trans);

				float newRot[16];
				trans.getOpenGLMatrix(newRot);
				newRot[15] = 1;
				currEntity->setTransformation(newRot);
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
void PhysicsMan::shootBall(Vector3f loc, Vector3f dir)
{
}