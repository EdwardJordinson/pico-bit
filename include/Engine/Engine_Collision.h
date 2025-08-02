#ifndef Engine_Collision_H
#define Engine_Collision_H

#include <Engine/Engine_Coordinates.h>
#include <stdbool.h>

//Forward declares
//

//#######################################################//
// -----------------------AABB-------------------------- //
typedef struct Engine_AABB
{
    Vector2 minVector;
    Vector2 maxVector;
} Engine_AABB;


Engine_AABB AABB_Initialise();
void AABB_AddPosition(Engine_AABB* box2D, Vector2 newPosition);
//bool AABB_ClipLine(int dimention, AABB* aabbBox, Vector2 lineStart, Vector2 lineEnd, float f_low, float f_high);
//bool AABB_IntersectionLine();
bool AABB_IntersectionAABB(Engine_AABB box1, Engine_AABB box2);


#endif //Engine_Collision_H