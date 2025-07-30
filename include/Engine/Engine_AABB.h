#ifndef Engine_AABB_H
#define Engine_AABB_H

#include <Engine/Engine_Vector2.h>
#include <stdbool.h>


typedef struct AABB
{
    Vector2 minVector;
    Vector2 maxVector;
} AABB;


AABB AABB_Initialise();

void AABB_AddPosition(AABB* box2D, Vector2 newPosition);

bool AABB_ClipLine(int dimention, AABB* aabbBox, Vector2 lineStart, Vector2 lineEnd, float f_low, float f_high);

bool AABB_IntersectionLine();

bool AABB_IntersectionAABB(AABB box1, AABB box2);


#endif //Engine_AABB_H