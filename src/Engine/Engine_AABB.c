#include <Engine/Engine_Collision.h>
#include <Engine/Engine_Physics.h>
#include <math.h>


Engine_AABB AABB_Initialise()
{
    return (Engine_AABB){(Vector2){0.0,0.0},(Vector2){0.0,0.0}};
};

void AABB_SetDefault(Engine_AABB* aabb)
{
    *aabb = (Engine_AABB){(Vector2){50.0,50.0},(Vector2){-50.0,-50.0}};
};

void AABB_SetConfiguration(Engine_AABB* aabb, Engine_AABB configAABB)
{
    *aabb = configAABB;
};

void AABB_SetMaxMin(Engine_AABB* aabb, Vector2 maxVector, Vector2 minVector)
{
    aabb->maxVector = maxVector; aabb->minVector = minVector;
};

Engine_AABB AABB_FindPosition(Engine_AABB* box2D, Vector2 newPosition)
{
    return (Engine_AABB){Vector2_AddVector(box2D->maxVector, newPosition), Vector2_AddVector(box2D->minVector, newPosition)};
};

bool AABB_IntersectionLine()
{
 
};

Engine_Manifold AABB_IntersectionAABB(Engine_AABB box1, Vector2 position1, Engine_AABB box2, Vector2 position2)
{
    //if(box1.maxVector.x < box2.minVector.x || box1.minVector.x > box2.maxVector.x) return false;
    //if(box1.maxVector.y < box2.minVector.y || box1.minVector.y > box2.maxVector.y) return false;

	Engine_AABB objectAABB1 = AABB_FindPosition(&box1, position1);
	Engine_AABB objectAABB2 = AABB_FindPosition(&box2, position2);

	Vector2 mid_1 = Vector2_MuliplyScalar(Vector2_AddVector(objectAABB1.minVector, objectAABB1.maxVector), 0.5);
	Vector2 mid_2 = Vector2_MuliplyScalar(Vector2_AddVector(objectAABB2.minVector, objectAABB2.maxVector), 0.5);
	
	Vector2 e1 = Vector_ABS(Vector2_MuliplyScalar(Vector2_SubtractVector(objectAABB1.maxVector, objectAABB1.minVector), 0.5));
	Vector2 e2 = Vector_ABS(Vector2_MuliplyScalar(Vector2_SubtractVector(objectAABB2.maxVector, objectAABB2.minVector), 0.5));
	
	Vector2 direction = Vector2_SubtractVector(mid_1, mid_2);

	float directionx = e1.x + e2.x - abs(direction.x);
	if (directionx < 0) return Manifold_Initialise(); 
	float directiony = e1.y + e2.y - abs(direction.y);
	if (directiony < 0) return Manifold_Initialise();

    return Physics_CollisionNormal(mid_1, e1, direction, directionx, directiony);
};