#include <Engine/Engine_CollisionShape.h>
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

void OBB_SetWidthHeight(Engine_OBB* aabb, float width, float height)
{
    aabb->sizeVector.x = width;
    aabb->sizeVector.y = height;
};

void OBB_SetTransform(Engine_OBB* aabb, Engine_Matrix3x2 bodyTransform)
{

};