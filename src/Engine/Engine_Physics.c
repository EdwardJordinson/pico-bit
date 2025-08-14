#include <Engine/Engine_Physics.h>
#include <Engine/Engine_GameObject.h>
#include <math.h>
#include <stdio.h>


void Physics_InverseMass()
{

};

void Physics_SetVelocity(Engine_PhysicsBody* physicsBody, float deltaTime)
{
	
};

void Physics_SetAcceleration(Engine_PhysicsBody* physicsBody, float deltaTime)
{
	//Velocity
	/*
	Vector2 tempForce = Vector2_MuliplyScalar(physicsBody->Force, physicsBody->MassData.InverseMass);
	Vector2 finalVel = Vector2_MuliplyScalar(tempForce, deltaTime);
	Vector2_SetVector(&physicsBody->Velocity, finalVel);

	Vector2_SetVector(&physicsBody->Velocity, 
		Vector2_MuliplyScalar(
			Vector2_MuliplyScalar(physicsBody->Force, physicsBody->MassData.InverseMass), deltaTime));
	*/

	//Position
	/*
	Vector2 tempVel = Vector2_MuliplyScalar(physicsBody->Velocity, deltaTime);
	Vector2 tempPos = Vector2_AddVector(physicsBody->Velocity, tempVel);
	Vector2 finalPos = Vector2_AddVector(physicsBody->Transform2D.Position, tempPos);
	Vector2_SetVector(&physicsBody->Transform2D.Position, finalPos);

	Vector2_SetVector(&physicsBody->Transform2D.Position, 
		Vector2_AddVector(physicsBody->Transform2D.Position, 
			Vector2_AddVector(physicsBody->Velocity, 
				Vector2_MuliplyScalar(physicsBody->Velocity, deltaTime))));
	*/

};

void Physics_UpdateRigid(Engine_PhysicsBody* physicsBody, float deltaTime)
{


    Vector2_SetVector(&physicsBody->Transform2D.Position, Vector2_AddVector(physicsBody->Transform2D.Position, Vector2_MuliplyScalar(physicsBody->Velocity, deltaTime)));
};

void Physics_UpdateStatic(Engine_PhysicsBody* physicsBody, float deltaTime)
{

};

void Physics_CollisionResolve(Engine_PhysicsBody* physicsBody1, Engine_PhysicsBody* physicsBody2, Engine_PhysicsManifold* manifold)
{
    Vector2 relativeVelocity = Vector2_SubtractVector(physicsBody2->Velocity, physicsBody1->Velocity);
	float veloictyAlongNormal = Vector2_DotProduct(relativeVelocity, manifold->Normal);
	
	if (veloictyAlongNormal < 0) return;

	float e = fmin(physicsBody1->Material.Restitution, physicsBody2->Material.Restitution);

	float j = -(1 + e) * veloictyAlongNormal;
	j /= physicsBody1->MassData.InverseMass + physicsBody2->MassData.InverseMass;

	Vector2 impulse = Vector2_MuliplyScalar(manifold->Normal, j);

    float massSum = physicsBody1->MassData.Mass + physicsBody2->MassData.Mass;
    float ratio = physicsBody1->MassData.Mass / massSum;
	physicsBody1->Velocity = Vector2_SubtractVector(physicsBody1->Velocity, Vector2_MuliplyScalar(impulse, ratio));
    ratio = physicsBody2->MassData.Mass / massSum;
	physicsBody2->Velocity = Vector2_AddVector(physicsBody2->Velocity, Vector2_MuliplyScalar(impulse, ratio));
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

void PhysicsPair_SetBodyAll(Engine_PhysicsPair* physicsPair, Engine_PhysicsBody* physicsBody1, Engine_PhysicsBody* physicsBody2)
{
	physicsPair->physicsBody1 = physicsBody1;
	physicsPair->physicsBody2 = physicsBody2;
};