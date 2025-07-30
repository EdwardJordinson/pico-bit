#include <Engine/Engine_AABB.h>


AABB AABB_Initialise()
{
    AABB newBox = {-50.0,-50.0,50.0,50.0};
    return newBox;
};

void AABB_AddPosition(AABB* box2D, Vector2 newPosition)
{
    box2D->minVector = Vector2_VectorAdd((Vector2){-50.0, -50.0}, newPosition);
    box2D->maxVector = Vector2_VectorAdd((Vector2){50.0, 50.0}, newPosition);
};

bool AABB_ClipLine(int dimention, AABB* aabbBox, Vector2 lineStart, Vector2 lineEnd, float f_low, float f_high)
{

};

bool AABB_IntersectionLine()
{

};

bool AABB_IntersectionAABB(AABB box1, AABB box2)
{
    if(box1.maxVector.x < box2.minVector.x || box1.minVector.x > box2.maxVector.x) return false;
    if(box1.maxVector.y < box2.minVector.y || box1.minVector.y > box2.maxVector.y) return false;
    
    return true;
};