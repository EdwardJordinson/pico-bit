#include <Engine/Engine_CollisionShape.h>
#include <Engine/Engine_Physics.h>
#include <Engine/Engine_Math.h>
#include <math.h>


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
	switch(collisionShape->CollisionType)
	{
	case 0: //AABB
        AABB_SetDefault(&collisionShape->Data.AABB);
		break;
	case 1: //OBB
        OBB_SetDefault(&collisionShape->Data.OBB);
		break;
    case 2: //Circle
        Circle_SetDefault(&collisionShape->Data.Circle);
        break;
    case 3: //Polygon
        //&collisionShape->Data.Polygon;
        break;
	}
};

void CollisionShape_SetConfiguration(Engine_CollisionShape* collisionShape, Engine_CollisionShape configShape)
{
    *collisionShape = configShape;
};

void* CollisionShape_GetData(Engine_CollisionShape* collisionShape)
{
	switch(collisionShape->CollisionType)
	{
	case 0: //AABB
		return &collisionShape->Data.AABB;
		break;
	case 1: //OBB
		return &collisionShape->Data.OBB;
		break;
    case 2: //Circle
        return &collisionShape->Data.Circle;
        break;
    case 3: //Polygon
        return &collisionShape->Data.Polygon;
        break;
	}
};

//This is completely awfull, basics first, better ideas later
bool CollisionShape_FindIntersection(Engine_PhysicsManifold* manifold, Engine_PhysicsBody* body1, Engine_PhysicsBody* body2)
{
    int shape1 = body1->CollisionShape.CollisionType;
    int shape2 = body2->CollisionShape.CollisionType;
    if (shape1 == 0 && shape2 == 0)
    {
        Engine_AABB* box1 = body1->CollisionShape.GetData(&body1->CollisionShape);
        Engine_AABB* box2 = body2->CollisionShape.GetData(&body2->CollisionShape);
        *manifold = CollisionShape_IntersectionAABBxAABB(*box1, body1->Transform2D, *box2, body2->Transform2D);
    }
    else if (shape1 == 0 && shape2 == 1)
    {
        Engine_AABB* box1 = body1->CollisionShape.GetData(&body1->CollisionShape);
        Engine_OBB* box2 = body2->CollisionShape.GetData(&body2->CollisionShape);
        *manifold = CollisionShape_IntersectionAABBxOBB(*box1, body1->Transform2D, *box2, body2->Transform2D);
    }
    else if (shape1 == 1 && shape2 == 0)
    {
        Engine_OBB* box1 = body1->CollisionShape.GetData(&body1->CollisionShape);
        Engine_AABB* box2 = body2->CollisionShape.GetData(&body2->CollisionShape);
        *manifold = CollisionShape_IntersectionAABBxOBB(*box2, body2->Transform2D, *box1, body1->Transform2D);
    }
    else if (shape1 == 1 && shape2 == 1)
    {
        Engine_OBB* box1 = body1->CollisionShape.GetData(&body1->CollisionShape);
        Engine_OBB* box2 = body2->CollisionShape.GetData(&body2->CollisionShape);
        *manifold = CollisionShape_IntersectionOBBxOBB(*box1, body1->Transform2D, *box2, body2->Transform2D);
    }
    else if (shape1 == 2 && shape2 == 0)
    {
        Engine_Circle* box1 = body1->CollisionShape.GetData(&body1->CollisionShape);
        Engine_AABB* box2 = body2->CollisionShape.GetData(&body2->CollisionShape);
        *manifold = CollisionShape_IntersectionAABBxCircle(*box2, body2->Transform2D, *box1, body1->Transform2D);
    }
    else if (shape1 == 0 && shape2 == 2)
    {
        Engine_AABB* box1 = body1->CollisionShape.GetData(&body1->CollisionShape);
        Engine_Circle* box2 = body2->CollisionShape.GetData(&body2->CollisionShape);
        *manifold = CollisionShape_IntersectionAABBxCircle(*box1, body1->Transform2D, *box2, body2->Transform2D);
    }
    return manifold->Hit;
};

Engine_PhysicsManifold CollisionShape_IntersectionAABBxAABB(Engine_AABB box1, Engine_Matrix3x2 bodyTransform1, Engine_AABB box2, Engine_Matrix3x2 bodyTransform2)
{
	Engine_AABB objectAABB1 = AABB_GetPosition(&box1, bodyTransform1);
	Engine_AABB objectAABB2 = AABB_GetPosition(&box2, bodyTransform2);

	Vector2 mid_1 = Vector2_MuliplyScalar(Vector2_AddVector(objectAABB1.minVector, objectAABB1.maxVector), 0.5);
	Vector2 mid_2 = Vector2_MuliplyScalar(Vector2_AddVector(objectAABB2.minVector, objectAABB2.maxVector), 0.5);
	
	Vector2 e1 = Vector2_ABS(Vector2_MuliplyScalar(Vector2_SubtractVector(objectAABB1.maxVector, objectAABB1.minVector), 0.5));
	Vector2 e2 = Vector2_ABS(Vector2_MuliplyScalar(Vector2_SubtractVector(objectAABB2.maxVector, objectAABB2.minVector), 0.5));
	
	Vector2 direction = Vector2_SubtractVector(mid_1, mid_2);

	float directionx = e1.x + e2.x - abs(direction.x);
	if (directionx < 0) return PhysicsManifold_Initialise(); 
	float directiony = e1.y + e2.y - abs(direction.y);
	if (directiony < 0) return PhysicsManifold_Initialise();

    return PhysicsManifold_AABBxAABB(mid_1, e1, direction, directionx, directiony);
};

Engine_PhysicsManifold CollisionShape_IntersectionAABBxOBB(Engine_AABB box1, Engine_Matrix3x2 bodyTransform1, Engine_OBB box2, Engine_Matrix3x2 bodyTransform2)
{

};

Engine_PhysicsManifold CollisionShape_IntersectionAABBxCircle(Engine_AABB box, Engine_Matrix3x2 bodyTransform1, Engine_Circle circle, Engine_Matrix3x2 bodyTransform2)
{
    Engine_AABB boxPos = AABB_GetPosition(&box, bodyTransform1);
	Vector2 distance = Math_ClampVector2(bodyTransform2.Position, boxPos.minVector, boxPos.maxVector);
	Vector2 ab = Vector2_SubtractVector(bodyTransform2.Position, distance);
	float d2 = Vector2_DotProduct(ab, ab);
	float r2 = circle.radius * circle.radius;

    if (d2 > r2) return PhysicsManifold_Initialise();
    
    return PhysicsManifold_CirclexAABB(&circle, bodyTransform2, &box, bodyTransform1);
};

Engine_PhysicsManifold CollisionShape_IntersectionOBBxOBB(Engine_OBB box1, Engine_Matrix3x2 bodyTransform1, Engine_OBB box2, Engine_Matrix3x2 bodyTransform2)
{

};

Engine_PhysicsManifold CollisionShape_IntersectionOBBxCircle(Engine_OBB box1, Engine_Matrix3x2 bodyTransform1, Engine_Circle box2, Engine_Matrix3x2 bodyTransform2)
{

};

Engine_PhysicsManifold CollisionShape_IntersectionCirclexCircle(Engine_Circle box1, Engine_Matrix3x2 bodyTransform1, Engine_Circle box2, Engine_Matrix3x2 bodyTransform2)
{

};