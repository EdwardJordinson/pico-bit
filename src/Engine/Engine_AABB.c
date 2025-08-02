#include <Engine/Engine_Collision.h>


Engine_AABB AABB_Initialise()
{
    Engine_AABB newBox = {-50.0,-50.0,50.0,50.0};
    return newBox;
};

void AABB_AddPosition(Engine_AABB* box2D, Vector2 newPosition)
{
    box2D->minVector = Vector2_VectorAdd((Vector2){-50.0, -50.0}, newPosition);
    box2D->maxVector = Vector2_VectorAdd((Vector2){50.0, 50.0}, newPosition);
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