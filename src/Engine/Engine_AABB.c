#include <Engine/Engine_CollisionShape.h>
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

void AABB_SetTransform(Engine_AABB* aabb, Engine_Matrix3x2 bodyTransform)
{

};

float AABB_GetWidth(Engine_AABB* aabb)
{
    return (float){aabb->maxVector.x - aabb->minVector.x};
};

float AABB_GetHeight(Engine_AABB* aabb)
{
    return (float){aabb->maxVector.y - aabb->minVector.y};
};

Vector2 AABB_GetCenter(Engine_AABB* aabb)
{
    return Vector2_MuliplyScalar(Vector2_AddVector(aabb->maxVector, aabb->minVector), 0.5f);
};

Engine_AABB AABB_GetUnion(Engine_AABB* aabb1, Engine_AABB* aabb2)
{
    //Need to create a min/max method for vector positions in space itself

};

Engine_AABB AABB_GetPosition(Engine_AABB* box2D, Engine_Matrix3x2 bodyTransform)
{
    return (Engine_AABB){Vector2_AddVector(box2D->maxVector, bodyTransform.Position), Vector2_AddVector(box2D->minVector, bodyTransform.Position)};
};

bool AABB_IntersectionLine()
{
 
};