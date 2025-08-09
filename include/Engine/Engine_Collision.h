#ifndef Engine_Collision_H
#define Engine_Collision_H

#include <Engine/Engine_Coordinates.h>
#include <stdbool.h>

//Forward declares
typedef struct Engine_Manifold Engine_Manifold;
//

//#######################################################//
// -----------------------AABB-------------------------- //
typedef struct Engine_AABB
{
    Vector2 maxVector; Vector2 minVector;
} Engine_AABB;


Engine_AABB AABB_Initialise();
void AABB_SetDefault(Engine_AABB* aabb);
void AABB_SetConfiguration(Engine_AABB* aabb, Engine_AABB configAABB);
void AABB_SetMaxMin(Engine_AABB* aabb, Vector2 maxVector, Vector2 minVector);
float AABB_GetWidth(Engine_AABB* aabb);
float AABB_GetHeight(Engine_AABB* aabb);
Engine_AABB AABB_GetPosition(Engine_AABB* aabb, Vector2 newPosition);
Engine_Manifold AABB_IntersectionAABB(Engine_AABB aabb1, Vector2 position1, Engine_AABB aabb2, Vector2 position2);
//bool AABB_ClipLine(int dimention, AABB* aabbBox, Vector2 lineStart, Vector2 lineEnd, float f_low, float f_high);
//bool AABB_IntersectionLine();


#endif //Engine_Collision_H