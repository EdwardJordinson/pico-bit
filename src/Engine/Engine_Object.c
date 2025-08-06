#include <Engine/Engine_Object.h>
#include <Engine/Engine_EventProcess.h>
#include <Engine/Engine_Coordinates.h>
#include <Engine/Engine_Physics.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>


Engine_Object Object_Initialise(int id)
{
    return(Engine_Object){id};
};

void Object_Setup(Engine_Object* object, float xPosition, float yPosition)
{
    object->Transform2D.Position = Vector2_Initialise(xPosition-50.0, yPosition-50.0);
    object->Velocity = Vector2_Initialise(0.0, 0.0);
    object->CollisionShape = AABB_Initialise();
	object->Restitution = 1.0;
	object->Mass = 10.0;

};

void Object_Event(Engine_Object* object, Engine_EventHandler* eventHandler)
{

};

void Object_SetPosition(Engine_Object* object, float xPosition, float yPosition)
{
    object->Transform2D.Position = Vector2_Initialise(xPosition-50.0, yPosition-50.0);
};

void Object_SetVelocity(Engine_Object* object, Vector2 vector)
{
    //REplace subtrace with Add
     object->Velocity = Vector2_ScalarMuliply(
        100, Vector2_Normailised(
            Vector2_VectorAdd(
                Vector2_VectorAdd(object->Transform2D.Position, Vector2_Initialise(50, 50)), vector)));//Vector2_VectorAdd(entity->Velocity, ); 

    //printf("%.2f : %.2f\n", vector.x, vector.y);
    printf("%.2f : %.2f\n", object->Velocity.x, object->Velocity.y);
    printf("%.2f : %.2f\n", object->Transform2D.Position.x, object->Transform2D.Position.y);
    
};

void Object_UpdateRigid(Engine_Object* object, float deltaTime)
{
    object->Transform2D.Position = Vector2_VectorAdd(Vector2_ScalarMuliply(deltaTime, object->Velocity), object->Transform2D.Position);
    AABB_AddPosition(&object->CollisionShape, object->Transform2D.Position);
}; 

void Object_UpdateStatic(Engine_Object* object, float deltaTime)
{

};

void Object_CollisionResolve(Engine_Object* object1, Engine_Object* object2, Engine_Manifold* manifold)
{
	Vector2 relativeVelocity = Vector2_VectorSubtract(object2->Velocity, object1->Velocity);

	float veloictyAlongNormal = Vector2_DotProduct(relativeVelocity, manifold->Normal);
	
	if (veloictyAlongNormal < 0)
	{
		return;
	}

	float e = fmin(object1->Restitution, object2->Restitution);

	float j = -(1 + e) * veloictyAlongNormal;
	j /= 1.0 / object1->Mass + 1.0 / object2->Mass;

	Vector2 impulse = Vector2_ScalarMuliply(j, manifold->Normal);
	object1->Velocity = Vector2_VectorSubtract(object1->Velocity, Vector2_ScalarMuliply(1.0/object1->Mass, impulse));
	object2->Velocity = Vector2_VectorAdd(object2->Velocity, Vector2_ScalarMuliply(1.0/object2->Mass, impulse));
};

Engine_Manifold Object_CollisionNormal(Engine_Object* object1, Engine_Object* object2)
{
	Engine_Manifold output;
	output.Hit = false;

	Vector2 mid_1 = Vector2_ScalarMuliply(0.5, Vector2_VectorAdd(object1->CollisionShape.minVector, object1->CollisionShape.maxVector));
	Vector2 mid_2 = Vector2_ScalarMuliply(0.5, Vector2_VectorAdd(object2->CollisionShape.minVector, object2->CollisionShape.maxVector));
	
	Vector2 e1 = Vector_ABS(Vector2_ScalarMuliply(0.5, Vector2_VectorSubtract(object1->CollisionShape.maxVector, object1->CollisionShape.minVector)));
	Vector2 e2 = Vector_ABS(Vector2_ScalarMuliply(0.5, Vector2_VectorSubtract(object2->CollisionShape.maxVector, object2->CollisionShape.minVector)));
	
	Vector2 direction = Vector2_VectorSubtract(mid_1, mid_2);

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
			normal = Vector2_Initialise(-1.0f, 0);
			p = Vector2_VectorSubtract(mid_1, Vector2_Initialise(e1.x, 0));
		}
		else
		{
			normal = Vector2_Initialise(1.0f, 0);
			p = Vector2_VectorAdd(mid_1, Vector2_Initialise(e1.x, 0));
		}
	}
	else
	{
		// y axis overlap is smaller
		depth = directiony;
		if (direction.y < 0) {
			normal = Vector2_Initialise(0, -1.0f);
			p = Vector2_VectorSubtract(mid_1, Vector2_Initialise(0, e1.y));
		}
		else
		{
			normal = Vector2_Initialise(0, 1.0f);
			p = Vector2_VectorAdd(mid_1, Vector2_Initialise(0, e1.y));
		}
	}

	output.Hit = true;
	output.HitSpot = p;
	output.Depth = depth;
	output.Normal = normal;
	return output;
};