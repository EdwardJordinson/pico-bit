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
	//Linear Velocity
	Vector2_SetVector(&physicsBody->Velocity,
		Vector2_AddVector(physicsBody->Velocity,
			Vector2_MuliplyScalar(
				Vector2_MuliplyScalar(physicsBody->Force, physicsBody->MassData.InverseMass), deltaTime)));
	//Position
	Vector2_SetVector(&physicsBody->Transform2D.Position, 
		Vector2_AddVector(physicsBody->Transform2D.Position, 
			Vector2_AddVector(physicsBody->Velocity, 
				Vector2_MuliplyScalar(physicsBody->Velocity, deltaTime))));

	physicsBody->Force = (Vector2){0.0,0.0};
};

void Physics_ApplyForce(Engine_PhysicsBody* physicsBody, Vector2 forceVector)
{
	Vector2_SetVector(&physicsBody->Force, Vector2_AddVector(physicsBody->Force, forceVector));
	//physicsBody->Force = forceVector;

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
	
	if (veloictyAlongNormal < 0.0) return;

	float e = fmin(physicsBody1->Material.Restitution, physicsBody2->Material.Restitution);

	float j = -(1 + e) * veloictyAlongNormal;
	j /= physicsBody1->MassData.InverseMass + physicsBody2->MassData.InverseMass;

	Vector2 impulse = Vector2_MuliplyScalar(manifold->Normal, j);

    float massSum = physicsBody1->MassData.Mass + physicsBody2->MassData.Mass;
    float ratio = physicsBody1->MassData.Mass / massSum;
	//Physics_ApplyForce(physicsBody1, Vector2_SubtractVector(physicsBody1->Velocity, Vector2_MuliplyScalar(impulse, ratio)));
	Vector2_SetVector(&physicsBody1->Velocity, Vector2_SubtractVector(physicsBody1->Velocity, Vector2_MuliplyScalar(impulse, ratio)));
    ratio = physicsBody2->MassData.Mass / massSum;
	//Physics_ApplyForce(physicsBody2, Vector2_AddVector(physicsBody2->Velocity, Vector2_MuliplyScalar(impulse, ratio)));
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

void Physics_BoardPhase()
{
	
};


Engine_PhysicsPair PhysicsPair_Initialise()
{
	return (Engine_PhysicsPair){NULL, NULL};
};

void PhysicsPair_SetPairBodies(Engine_PhysicsPair* physicsPair, Engine_PhysicsBody* physicsBody1, Engine_PhysicsBody* physicsBody2)
{
	physicsPair->physicsBody1 = physicsBody1;
	physicsPair->physicsBody2 = physicsBody2;
};

void PhysicsPair_Clear(Engine_PhysicsPair* physicsPair)
{
	for (int i = 0; i != 3; i++)
	{
		physicsPair[i] = PhysicsPair_Initialise();
	}


};

void PhysicsPair_GenerateList(Engine_PhysicsPair* physicsPair, Engine_ObjectManager* entityManager)
{
	PhysicsPair_Clear(physicsPair);

	Engine_PhysicsBody allBodies[3];
	PhysicsBody_GetList(allBodies, entityManager);


	int end = 3;
	for (int i = 0; i != end; ++i)
	{
		int jStart = i;
		for (int j = ++jStart; j != end; ++j)
		{

			Engine_PhysicsBody* physicsBody1 = &allBodies[i];
			Engine_PhysicsBody* physicsBody2 = &allBodies[j];

			if (physicsBody1 == physicsBody2)
			{
				continue;
			}

			/*  
			https://allenchou.net/2013/12/game-physics-broadphase/
			
			      // add collider pair
      if (aabbA->Collides(aabbB))
        m_pairs.push_back(
          std::make_pair(aabbA->collider, aabbB->collider));
       
    } // end of inner loop
  } // end of outer loop
   
  return m_pairs;
			
			*/


		}



	}


};

void PhysicsBody_GetList(Engine_PhysicsBody* physicsBody, Engine_ObjectManager* entityManager)
{
    for (int i = 0; i < entityManager->ActiveCount; i++)
    {
        Engine_EntityObject* tempEntity = ObjectManager_Get(entityManager, i)->Data;
        Engine_GameEntity* tempGameE;
        if (tempEntity->EntityType == 1)
        {
            tempGameE = tempEntity->GetData(tempEntity);
            physicsBody = &tempGameE->PhysicsBody;
            physicsBody++;
        }
    }
};