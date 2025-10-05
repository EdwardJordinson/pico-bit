#ifndef Engine_Collision_H
#define Engine_Collision_H

#include <Engine/Engine_Coordinates.h>
#include <stdbool.h>

//Forward declares
typedef struct Engine_PhysicsManifold Engine_PhysicsManifold;
//

//#######################################################//
// -----------------------AABB-------------------------- //
typedef struct Engine_AABB
{
    Vector2 maxVector;
    Vector2 minVector;
} Engine_AABB;


Engine_AABB AABB_Initialise();
void AABB_SetDefault(Engine_AABB* aabb);
void AABB_SetConfiguration(Engine_AABB* aabb, Engine_AABB configAABB);
void AABB_SetMaxMin(Engine_AABB* aabb, Vector2 maxVector, Vector2 minVector);
void AABB_SetTransform(Engine_AABB* aabb, Engine_Matrix3x2 bodyTransform);
float AABB_GetWidth(Engine_AABB* aabb);
float AABB_GetHeight(Engine_AABB* aabb);
Engine_AABB AABB_GetPosition(Engine_AABB* aabb, Engine_Matrix3x2 bodyTransform);
Engine_AABB AABB_GetUnion(Engine_AABB* aabb1, Engine_AABB* aabb2);
Engine_PhysicsManifold AABB_IntersectionAABB(Engine_AABB box1, Engine_Matrix3x2 bodyTransform1, Engine_AABB box2, Engine_Matrix3x2 bodyTransform2);
//bool AABB_IntersectionLine();


typedef struct Engine_OBB
{
    Vector2 sizeVector; //Half widths of the box
} Engine_OBB;

Engine_OBB OBB_Initialise();
void OBB_SetDefault(Engine_OBB* aabb);
void OBB_SetConfiguration(Engine_OBB* aabb, Engine_AABB configAABB);
void OBB_SetMaxMin(Engine_OBB* aabb, Vector2 maxVector, Vector2 minVector);
void OBB_SetTransform(Engine_OBB* aabb, Engine_Matrix3x2 bodyTransform);
float OBB_GetWidth(Engine_OBB* aabb);
float OBB_GetHeight(Engine_OBB* aabb);
Engine_OBB OBB_GetPosition(Engine_OBB* aabb, Engine_Matrix3x2 bodyTransform);
Engine_OBB OBB_GetUnion(Engine_OBB* aabb1, Engine_OBB* aabb2);
Engine_PhysicsManifold OBB_IntersectionOBB(Engine_OBB box1, Engine_Matrix3x2 bodyTransform1, Engine_OBB box2, Engine_Matrix3x2 bodyTransform2);
Engine_PhysicsManifold OBB_IntersectionAABB(Engine_OBB box1, Engine_Matrix3x2 bodyTransform1, Engine_OBB box2, Engine_Matrix3x2 bodyTransform2);

#endif //Engine_Collision_H