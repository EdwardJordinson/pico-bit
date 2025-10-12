#ifndef Engine_Collision_H
#define Engine_Collision_H

#include <Engine/Engine_Coordinates.h>
#include <stdbool.h>

//Forward declares
typedef struct Engine_PhysicsManifold Engine_PhysicsManifold;
typedef struct Engine_PhysicsBody Engine_PhysicsBody;
//

typedef enum CollisionType
{
    AABB,
    OBB,
    CIRCLE
};

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


typedef struct Engine_OBB
{
    Vector2 sizeVector; //Half widths of the box
} Engine_OBB;

Engine_OBB OBB_Initialise();
void OBB_SetDefault(Engine_OBB* aabb);
void OBB_SetConfiguration(Engine_OBB* aabb, Engine_AABB configAABB);
void OBB_SetWidthHeight(Engine_OBB* aabb, float width, float height);
void OBB_SetTransform(Engine_OBB* aabb, Engine_Matrix3x2 bodyTransform);


typedef struct Engine_Circle
{
    float radius;
} Engine_Circle;

Engine_Circle Circle_Initialise();
void Circle_SetDefault(Engine_Circle* circle);
void Circle_SetConfiguration(Engine_Circle* circle, Engine_Circle configCircle);
void Circle_SetRadius(Engine_Circle* circle, float rad);
void Circle_SetTransform(Engine_Circle* circle, Engine_Matrix3x2 bodyTransform);


typedef struct Engine_Polgygon
{
    int vertCount;
    Vector2 vertexes[256];
} Engine_Polgygon;

Engine_Polgygon Polgygon_Initialise();
void Polgygon_SetDefault(Engine_Polgygon* polygon);


union CollisionData
{
    Engine_AABB AABB;
    Engine_OBB OBB;
    Engine_Circle Circle;
    Engine_Polgygon Polygon;
};

typedef struct Engine_CollisionShape
{
    enum CollisionType CollisionType;
    union CollisionData Data;

    void* (*GetData)(struct Engine_CollisionShape*);

} Engine_CollisionShape;

Engine_CollisionShape CollisionShape_Initialise();
void CollisionShape_SetShape(Engine_CollisionShape* collisionShape, int shapeType);
void CollisionShape_SetDefault(Engine_CollisionShape* collisionShape);
void CollisionShape_SetConfiguration(Engine_CollisionShape* collisionShape, Engine_CollisionShape configShape);
void* CollisionShape_GetData(Engine_CollisionShape* collisionShape);
bool CollisionShape_FindIntersection(Engine_PhysicsManifold* manifold, Engine_PhysicsBody* body1, Engine_PhysicsBody* body2);
Engine_PhysicsManifold CollisionShape_IntersectionAABBxAABB(Engine_AABB box1, Engine_Matrix3x2 bodyTransform1, Engine_AABB box2, Engine_Matrix3x2 bodyTransform2);
Engine_PhysicsManifold CollisionShape_IntersectionAABBxOBB(Engine_AABB box1, Engine_Matrix3x2 bodyTransform1, Engine_OBB box2, Engine_Matrix3x2 bodyTransform2);
Engine_PhysicsManifold CollisionShape_IntersectionOBBxOBB(Engine_OBB box1, Engine_Matrix3x2 bodyTransform1, Engine_OBB box2, Engine_Matrix3x2 bodyTransform2);

#endif //Engine_Collision_H