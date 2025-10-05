#include <Engine/Engine_Collision.h>
#include <Engine/Engine_Physics.h>
#include <math.h>




Engine_OBB OBB_Initialise()
{

};

void OBB_SetDefault(Engine_OBB* aabb)
{

};

void OBB_SetConfiguration(Engine_OBB* aabb, Engine_AABB configAABB)
{

};

void OBB_SetMaxMin(Engine_OBB* aabb, Vector2 maxVector, Vector2 minVector)
{

};

void OBB_SetTransform(Engine_OBB* aabb, Engine_Matrix3x2 bodyTransform)
{

};

float OBB_GetWidth(Engine_OBB* aabb)
{

};

float OBB_GetHeight(Engine_OBB* aabb)
{

};

Engine_OBB OBB_GetPosition(Engine_OBB* aabb, Engine_Matrix3x2 bodyTransform)
{

};

Engine_OBB OBB_GetUnion(Engine_OBB* aabb1, Engine_OBB* aabb2)
{

};

Engine_PhysicsManifold OBB_IntersectionOBB(Engine_OBB box1, Engine_Matrix3x2 bodyTransform1, Engine_OBB box2, Engine_Matrix3x2 bodyTransform2)
{

};

Engine_PhysicsManifold OBB_IntersectionAABB(Engine_OBB box1, Engine_Matrix3x2 bodyTransform1, Engine_OBB box2, Engine_Matrix3x2 bodyTransform2)
{

};