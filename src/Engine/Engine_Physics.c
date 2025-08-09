#include <Engine/Engine_Physics.h>
#include <Engine/Engine_GameObject.h>
#include <math.h>


Engine_Manifold Manifold_Initialise()
{
    return (Engine_Manifold){false, (Vector2){0.0,0.0}, 0.0, (Vector2){0.0,0.0}};
};

void Physics_InverseMass()
{

};

void Physics_SetVelocity(Engine_GameObject* gameObject, Vector2 vector)
{
    //Replace subtrace with Add
    /*
     object->Velocity = Vector2_ScalarMuliply(
        100, Vector2_Normailised(
            Vector2_VectorAdd(
                Vector2_VectorAdd(object->Transform2D.Position, (Vector2){50,50}), vector)));//Vector2_VectorAdd(entity->Velocity, ); 

    printf("%.2f : %.2f\n", vector.x, vector.y);
    printf("%.2f : %.2f\n", object->Velocity.x, object->Velocity.y);
    printf("%.2f : %.2f\n", object->Transform2D.Position.x, object->Transform2D.Position.y);
    */
    
};

void Physics_UpdateRigid(Engine_GameObject* gameObject, float deltaTime)
{
    Vector2_SetVector(&gameObject->Transform2D.Position, Vector2_AddVector(gameObject->Transform2D.Position, Vector2_MuliplyScalar(gameObject->Velocity, deltaTime)));
};

void Physics_UpdateStatic(Engine_GameObject* gameObject, float deltaTime)
{

};

void Physics_CollisionResolve(Engine_GameObject* gameObject1, Engine_GameObject* gameObject2, Engine_Manifold* manifold)
{
    Vector2 relativeVelocity = Vector2_SubtractVector(gameObject2->Velocity, gameObject1->Velocity);
	float veloictyAlongNormal = Vector2_DotProduct(relativeVelocity, manifold->Normal);
	
	if (veloictyAlongNormal < 0) return;

	float e = fmin(gameObject1->Restitution, gameObject2->Restitution);

	float j = -(1 + e) * veloictyAlongNormal;
	j /= 1.0 / gameObject1->Mass + 1.0 / gameObject2->Mass;

	Vector2 impulse = Vector2_MuliplyScalar(manifold->Normal, j);
	gameObject1->Velocity = Vector2_SubtractVector(gameObject1->Velocity, Vector2_MuliplyScalar(impulse, 1.0/gameObject1->Mass));
	gameObject2->Velocity = Vector2_AddVector(gameObject2->Velocity, Vector2_MuliplyScalar(impulse, 1.0/gameObject2->Mass));
};

Engine_Manifold Physics_CollisionNormal(Vector2 mid_1, Vector2 e1, Vector2 direction, float directionx, float directiony)
{
    Engine_Manifold output = Manifold_Initialise();

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