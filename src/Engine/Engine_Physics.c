#include <Engine/Engine_Physics.h>
#include <Engine/Engine_Object.h>
#include <Engine/Engine_EntityObject.h>
#include <math.h>
#include <stdio.h>


void Physics_InverseMass()
{

};

void Physics_SetVelocity(Engine_PhysicsBody* physicsBody, float deltaTime)
{
	
};

void Physics_Integration(Engine_PhysicsBody* physicsBody, float deltaTime)
{
	Engine_Matrix3x2 tempMatrix3x2 = Matrix3x2_Inititialise();

	//Linear Velocity
	Vector2_SetVector(&physicsBody->Velocity,
		Vector2_AddVector(physicsBody->Velocity,
			Vector2_MuliplyScalar(
				Vector2_MuliplyScalar(physicsBody->Force, physicsBody->MassData.InverseMass), deltaTime)));
	//Angular Velocity
	physicsBody->AngularVelocity += physicsBody->Torque * (1.0f / physicsBody->MassData.Inertia) * deltaTime;

	//Position
	Vector2_SetVector(&physicsBody->Transform2D.Position, 
		Vector2_AddVector(physicsBody->Transform2D.Position, 
			Vector2_AddVector(physicsBody->Velocity, 
				Vector2_MuliplyScalar(physicsBody->Velocity, deltaTime))));
	//Orientation
	
				
	//Zero'ing forces
	Vector2_SetVector(&physicsBody->Force, (Vector2){0.0,0.0});

};

//Applies Velocity
void Physics_ApplyImpulse(Engine_PhysicsBody* physicsBody, Vector2 impulseVector)
{
	

};

//Applies Acceleration
void Physics_ApplyForce(Engine_PhysicsBody* physicsBody, Vector2 forceVector)
{
	Vector2_SetVector(&physicsBody->Force, Vector2_AddVector(physicsBody->Force, forceVector));

};

void Physics_UpdateRigid(Engine_PhysicsBody* physicsBody, float deltaTime)
{
	Physics_Integration(physicsBody, deltaTime);

};

void Physics_UpdateStatic(Engine_PhysicsBody* physicsBody, float deltaTime)
{

};

void Physics_CollisionResolve(Engine_PhysicsBody* physicsBody1, Engine_PhysicsBody* physicsBody2, Engine_PhysicsManifold* manifold)
{
    Vector2 relativeVelocity = Vector2_SubtractVector(physicsBody2->Velocity, physicsBody1->Velocity);
	float veloictyAlongNormal = Vector2_DotProduct(relativeVelocity, manifold->Normal);
	
	if (veloictyAlongNormal > 0.0) return;

	float e = fmin(physicsBody1->Material.Restitution, physicsBody2->Material.Restitution);

	float j = -(1 + e) * veloictyAlongNormal;
	j /= physicsBody1->MassData.InverseMass + physicsBody2->MassData.InverseMass;

	Vector2 impulse = Vector2_MuliplyScalar(manifold->Normal, j);

    float massSum = physicsBody1->MassData.Mass + physicsBody2->MassData.Mass;
    float ratio = physicsBody1->MassData.Mass / massSum;
	Vector2_SetVector(&physicsBody1->Velocity, Vector2_SubtractVector(physicsBody1->Velocity, Vector2_MuliplyScalar(impulse, ratio)));
    ratio = physicsBody2->MassData.Mass / massSum;
	Vector2_SetVector(&physicsBody2->Velocity, Vector2_AddVector(physicsBody2->Velocity, Vector2_MuliplyScalar(impulse, ratio)));
};

Engine_PhysicsManifold Physics_CollisionNormal(Vector2 mid_1, Vector2 e1, Vector2 direction, float directionx, float directiony)
{
    Engine_PhysicsManifold output = Manifold_Initialise();

	Vector2 normal;
	float depth;
	Vector2 p;

	if (directionx < directiony) 
	{
		depth = directionx;
		if (direction.x < 0)
		{
			normal = (Vector2){-1.0f, 0};
			p = Vector2_SubtractVector(mid_1, (Vector2){e1.x, 0.0});
		}
		else
		{
			normal = (Vector2){1.0f, 0};
			p = Vector2_AddVector(mid_1, (Vector2){e1.x, 0.0});
		}
	}
	else
	{
		depth = directiony;
		if (direction.y < 0) 
        {
			normal = (Vector2){0, -1.0f};
			p = Vector2_SubtractVector(mid_1, (Vector2){0, e1.y});
		}
		else
		{
			normal = (Vector2){0, 1.0f};
			p = Vector2_AddVector(mid_1, (Vector2){0, e1.y});
		}
	}

	output.Hit = true;
	output.HitSpot = p;
	output.Depth = depth;
	output.Normal = normal;
	return output;
};

//Forgot what this does
void PhysicsBody_GetList(Engine_PhysicsBody* physicsBody, Engine_ObjectManager* entityManager)
{
	Engine_PhysicsBody* allBodies[3];
    for (int i = 0; i < entityManager->ActiveCount; i++)
    {
        Engine_EntityObject* tempEntity = ObjectManager_Get(entityManager, i)->Data;
        Engine_GameEntity* tempGameE;
        if (tempEntity->EntityType == 1)
        {
			tempGameE = EntityObject_GetData(tempEntity);
            allBodies[i] = &tempGameE->PhysicsBody;
        }
    }
	physicsBody = *allBodies;
};

Engine_PhysicsPair PhysicsPair_Initialise()
{
	return (Engine_PhysicsPair){NULL, NULL};
};

void PhysicsPair_Clear(Engine_PhysicsPair* physicsPair)
{
	for (int i = 0; i != 3; i++)
	{
		physicsPair[i] = PhysicsPair_Initialise();
	}
};

void PhysicsPair_SetPairBodies(Engine_PhysicsPair* physicsPair, Engine_PhysicsBody* physicsBody1, Engine_PhysicsBody* physicsBody2)
{
	physicsPair->physicsBody1 = physicsBody1;
	physicsPair->physicsBody2 = physicsBody2;
};

Engine_PhysicsBroadPhase PhysicsBroadPhase_Initialise()
{
	return(Engine_PhysicsBroadPhase){0, NULL};
};

void PhysicsBroadPhase_GeneratePairList(Engine_PhysicsBroadPhase* physicsBroadPhase, Engine_ObjectManager* entityManager)
{
	PhysicsPair_Clear(physicsBroadPhase->PairList);

	Engine_PhysicsBody* allBodies[3];
	PhysicsBody_GetList(*allBodies, entityManager);

	physicsBroadPhase->count = 0;
	int end = 3;
	for (int i = 0; i != end; ++i)
	{
		int jStart = i;
		for (int j = ++jStart; j != end; ++j)
		{

			Engine_PhysicsBody* physicsBody1 = allBodies[i];
			Engine_PhysicsBody* physicsBody2 = allBodies[j];

			if (i == j)
			{
				continue;
			}

			//Engine_AABB* tempAABB1 = physicsBody1->CollisionShape.GetData(&physicsBody1->CollisionShape);
			//Engine_AABB* tempAABB2 = physicsBody2->CollisionShape.GetData(&physicsBody1->CollisionShape);

			//Engine_PhysicsManifold collisionData = AABB_IntersectionAABB(*tempAABB1, physicsBody1->Transform2D, *tempAABB2, physicsBody2->Transform2D);
			/*
			if (collisionData.Hit == true)
			{
				physicsBroadPhase->PairList[physicsBroadPhase->count].physicsBody1 = physicsBody1;
				physicsBroadPhase->PairList[physicsBroadPhase->count].physicsBody2 = physicsBody2;
				physicsBroadPhase->count++;
			}
			*/
		}
	}
};

void PhysicsBroadPhase_CullDupicatesPairList(Engine_PhysicsBroadPhase* physicsBroadPhase)
{
	//Sorted list
	Engine_PhysicsPair PairList[6];


	int count = 0;
	while (count < physicsBroadPhase->count)
	{
		/* code */

		int checkCount = count + 1;

	}
	

};

void PhysicsBroadPhase_AddPair(Engine_PhysicsBroadPhase* physicsBroadPhase)
{

};

void PhysicsBroadPhase_Update(Engine_PhysicsBroadPhase* physicsBroadPhase)
{

};

void PhysicsBroadPhase_Query(Engine_PhysicsBroadPhase* physicsBroadPhase)
{

};

//Only checking collision for one object
void PhysicsBroadPhase_TEMPPairList(Engine_PhysicsBroadPhase* physicsBroadPhase, Engine_ObjectManager* entityManager)
{
	PhysicsPair_Clear(physicsBroadPhase->PairList);

	Engine_PhysicsBody* allBodies[5];
    for (int i = 0; i < entityManager->ActiveCount; i++)
    {
        Engine_EntityObject* tempEntity = ObjectManager_Get(entityManager, i)->Data;
        Engine_GameEntity* tempGameE;
        if (tempEntity->EntityType == 1)
        {
			tempGameE = EntityObject_GetData(tempEntity);
            allBodies[i] = &tempGameE->PhysicsBody;
        }
    }
	//PhysicsBody_GetList(*allBodies, entityManager);

	physicsBroadPhase->count = 0;
	int end = entityManager->ActiveCount-1;
	for (int i = 0; i != end; ++i)
	{
		Engine_PhysicsBody* targetBox = allBodies[0];
		Engine_PhysicsBody* checkBox = allBodies[i];

		if (i == 0)
		{
			continue;
		}

		Engine_PhysicsManifold tempManifold = Manifold_Initialise();
		if (CollisionShape_FindIntersection(&tempManifold, targetBox, checkBox) == true)
		{
			physicsBroadPhase->PairList[physicsBroadPhase->count].physicsBody1 = targetBox;
			physicsBroadPhase->PairList[physicsBroadPhase->count].physicsBody2 = checkBox;
			physicsBroadPhase->PairList[physicsBroadPhase->count].manifold = tempManifold;
			physicsBroadPhase->count++;
		}	

	}
};