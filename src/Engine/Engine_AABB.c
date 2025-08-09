#include <Engine/Engine_Collision.h>


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
    //box2D->minVector = Vector2_VectorAdd((Vector2){-50.0, -50.0}, newPosition);
    //box2D->maxVector = Vector2_VectorAdd((Vector2){50.0, 50.0}, newPosition);
    //return (Engine_AABB){box2D->maxVector.x, box2D->maxVector.y, box2D->minVector.x, box2D->minVector.y};
    return (Engine_AABB){Vector2_AddVector(box2D->maxVector, newPosition), Vector2_AddVector(box2D->minVector, newPosition)};
};

bool AABB_IntersectionLine()
{
 
};

bool AABB_IntersectionAABB(Engine_AABB box1, Engine_AABB box2)
{
    if(box1.maxVector.x < box2.minVector.x || box1.minVector.x > box2.maxVector.x) return false;
    if(box1.maxVector.y < box2.minVector.y || box1.minVector.y > box2.maxVector.y) return false;
    
    return true;
};