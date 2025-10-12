#include <Engine/Engine_Collision.h>





Engine_CollisionShape CollisionShape_Initialise()
{
    return (Engine_CollisionShape){
        .CollisionType = 0,
        .GetData = CollisionShape_GetData
    };
};

void CollisionShape_SetShape(Engine_CollisionShape* collisionShape, int shapeType)
{
    collisionShape->CollisionType = shapeType;
};

void CollisionShape_SetDefault(Engine_CollisionShape* collisionShape)
{

};

void CollisionShape_SetConfiguration(Engine_CollisionShape* collisionShape, Engine_CollisionShape configShape)
{
    *collisionShape = configShape;
};

void* CollisionShape_GetData(Engine_CollisionShape* collisionShape)
{
	switch(collisionShape->CollisionType)
	{
	case 1:
		return &collisionShape->Data.AABB;
		break;
	case 2:
		return &collisionShape->Data.OBB;
		break;
	}
};