#include <Engine/Engine_GameObject.h>
#include <Engine/Engine_EventProcess.h>
#include <Engine/Engine_Coordinates.h>
#include <Engine/Engine_Physics.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>


void GameObject_Initialise()
{ //Set values to defaults -> Creation pipeline
    //return(Engine_GameObject){};
};

void GameObject_SetDefault(Engine_GameObject* gameObject)
{
    Vector2_SetXY(&gameObject->Transform2D.Position, 0.0,0.0);
    Vector2_SetXY(&gameObject->Velocity, 0.0,0.0);
    AABB_SetMaxMin(&gameObject->CollisionShape,(Vector2){50.0,50.0},(Vector2){-50.0,-50.0});
	gameObject->Restitution = 1.0;
	gameObject->Mass = 10.0;

};

void GameObject_SetConfiguration(Engine_GameObject* gameObject, Engine_GameObject configObject)
{

};

void GameObject_SetPositionXY(Engine_GameObject* gameObject, float xPosition, float yPosition)
{
    Vector2_SetXY(&gameObject->Transform2D.Position, xPosition+gameObject->CollisionShape.minVector.x, yPosition+gameObject->CollisionShape.minVector.y);
};

void GameObject_SetPositionVector(Engine_GameObject* gameObject, Vector2 vector)
{
    //Vector2_SetXY(&object->Transform2D.Position, xPosition+object->CollisionShape.minVector.x, yPosition+object->CollisionShape.minVector.y);
};

void GameObject_SetVelocity(Engine_GameObject* gameObject, Vector2 vector)
{
    //REplace subtrace with Add
    /*
     object->Velocity = Vector2_ScalarMuliply(
        100, Vector2_Normailised(
            Vector2_VectorAdd(
                Vector2_VectorAdd(object->Transform2D.Position, (Vector2){50,50}), vector)));//Vector2_VectorAdd(entity->Velocity, ); 

    //printf("%.2f : %.2f\n", vector.x, vector.y);
    printf("%.2f : %.2f\n", object->Velocity.x, object->Velocity.y);
    printf("%.2f : %.2f\n", object->Transform2D.Position.x, object->Transform2D.Position.y);
    */
    
};

void GameObject_UpdateRigid(Engine_GameObject* gameObject, float deltaTime)
{
    Vector2_SetVector(&gameObject->Transform2D.Position, Vector2_AddVector(gameObject->Transform2D.Position, Vector2_MuliplyScalar(gameObject->Velocity, deltaTime)));
    AABB_FindPosition(&gameObject->CollisionShape, gameObject->Transform2D.Position);
};

void GameObject_UpdateStatic(Engine_GameObject* gameObject, float deltaTime)
{

};

void GameObject_CollisionResolve(Engine_GameObject* object1, Engine_GameObject* object2, Engine_Manifold* manifold)
{
	Vector2 relativeVelocity = Vector2_SubtractVector(object2->Velocity, object1->Velocity);

	float veloictyAlongNormal = Vector2_DotProduct(relativeVelocity, manifold->Normal);
	
	if (veloictyAlongNormal < 0)
	{
		return;
	}

	float e = fmin(object1->Restitution, object2->Restitution);

	float j = -(1 + e) * veloictyAlongNormal;
	j /= 1.0 / object1->Mass + 1.0 / object2->Mass;

	Vector2 impulse = Vector2_MuliplyScalar(manifold->Normal, j);
	object1->Velocity = Vector2_SubtractVector(object1->Velocity, Vector2_MuliplyScalar(impulse, 1.0/object1->Mass));
	object2->Velocity = Vector2_AddVector(object2->Velocity, Vector2_MuliplyScalar(impulse, 1.0/object2->Mass));
};

Engine_Manifold GameObject_CollisionNormal(Engine_GameObject* object1, Engine_GameObject* object2)
{
	Engine_Manifold output;
	output.Hit = false;

	Engine_AABB objectAABB1 = AABB_FindPosition(&object1->CollisionShape, object1->Transform2D.Position);
	Engine_AABB objectAABB2 = AABB_FindPosition(&object2->CollisionShape, object2->Transform2D.Position);

	Vector2 mid_1 = Vector2_MuliplyScalar(Vector2_AddVector(objectAABB1.minVector, objectAABB1.maxVector), 0.5);
	Vector2 mid_2 = Vector2_MuliplyScalar(Vector2_AddVector(objectAABB2.minVector, objectAABB2.maxVector), 0.5);
	
	Vector2 e1 = Vector_ABS(Vector2_MuliplyScalar(Vector2_SubtractVector(objectAABB1.maxVector, objectAABB1.minVector), 0.5));
	Vector2 e2 = Vector_ABS(Vector2_MuliplyScalar(Vector2_SubtractVector(objectAABB2.maxVector, objectAABB2.minVector), 0.5));
	
	Vector2 direction = Vector2_SubtractVector(mid_1, mid_2);

	float directionx = e1.x + e2.x - abs(direction.x);
	if (directionx < 0) return output;
	float directiony = e1.y + e2.y - abs(direction.y);
	if (directiony < 0) return output;

	Vector2 normal;
	float depth;
	Vector2 p;

	if (directionx < directiony) 
	{
		// x axis overlap is smaller
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
		// y axis overlap is smaller
		depth = directiony;
		if (direction.y < 0) {
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