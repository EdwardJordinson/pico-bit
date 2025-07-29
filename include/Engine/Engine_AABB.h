#ifndef Engine_AABB_H
#define Engine_AABB_H

#include <Engine/Engine_Vector2.h>
#include <stdbool.h>


typedef struct AABB
{
    Vector2 minVector;
    Vector2 maxVector;
}   AABB;


bool AABB_LineIntersection();

bool AABB_ClipLine();


#endif //Engine_AABB_H