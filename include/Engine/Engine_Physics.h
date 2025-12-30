#ifndef Engine_Physics_H
#define Engine_Physics_H

#include <Engine/Engine_Coordinates.h>
#include <Engine/Engine_CollisionShape.h>
#include <stdbool.h>

//Forward declares
typedef struct Engine_EntityObject Engine_EntityObject;
typedef struct Engine_ObjectManager Engine_ObjectManager;
//

typedef struct Engine_PhysicsManifold
{
    bool Hit; 
    Vector2 HitSpot;
    float Depth;
    Vector2 Normal;

} Engine_PhysicsManifold;

Engine_PhysicsManifold PhysicsManifold_Initialise();
Engine_PhysicsManifold PhysicsManifold_AABBxAABB(Vector2 mid_1, Vector2 e1, Vector2 direction, float directionx, float directiony); //Needs a rebuild

Engine_PhysicsManifold PhysicsManifold_CirclexAABB(Engine_Circle* circle, Engine_Matrix3x2 bodyTransform1, Engine_AABB* aabb, Engine_Matrix3x2 bodyTransform2);
Engine_PhysicsManifold PhysicsManifold_AABBxOBB(Engine_AABB box1, Engine_Matrix3x2 bodyTransform1, Engine_OBB box2, Engine_Matrix3x2 bodyTransform2);
Engine_PhysicsManifold PhysicsManifold_OBBxOBB(Engine_OBB box1, Engine_Matrix3x2 bodyTransform1, Engine_OBB box2, Engine_Matrix3x2 bodyTransform2);
Engine_PhysicsManifold PhysicsManifold_OBBxCircle(Engine_AABB box1, Engine_Matrix3x2 bodyTransform1, Engine_OBB box2, Engine_Matrix3x2 bodyTransform2);
Engine_PhysicsManifold PhysicsManifold_CirclexCircle(Engine_AABB box1, Engine_Matrix3x2 bodyTransform1, Engine_OBB box2, Engine_Matrix3x2 bodyTransform2);


typedef struct Engine_PhysicsMass
{
    float Mass;
    float InverseMass;

    float Inertia;
    float InverseInertia;
} Engine_PhysicsMass;


Engine_PhysicsMass PhysicsMass_Initialise();


typedef struct Engine_PhysicsMaterial
{
    float Density;
    float Restitution;
} Engine_PhysicsMaterial;

/*
Rock       Density : 0.6  Restitution : 0.1
Wood       Density : 0.3  Restitution : 0.2
Metal      Density : 1.2  Restitution : 0.05
BouncyBall Density : 0.3  Restitution : 0.8
SuperBall  Density : 0.3  Restitution : 0.95
Pillow     Density : 0.1  Restitution : 0.2
Static     Density : 0.0  Restitution : 0.4
*/

Engine_PhysicsMaterial PhysicsMaterial_Initialise();


typedef struct Engine_PhysicsBody
{
    Engine_CollisionShape CollisionShape;
    Engine_PhysicsMass MassData;
    Engine_PhysicsMaterial Material;
    Engine_Matrix3x2 Transform2D;
    Vector2 Velocity;
    float AngularVelocity;
    Vector2 Force; //Acceleration
    float Torque;

} Engine_PhysicsBody;


Engine_PhysicsBody PhysicsBody_Initialise();

void PhysicsBody_SetTransform(Engine_PhysicsBody* body, Engine_Matrix3x2 newTransform);
void PhysicsBody_GetList(Engine_PhysicsBody* aabb, Engine_ObjectManager* entityManager);


typedef struct Engine_PhysicsPair
{
    Engine_PhysicsBody* physicsBody1;
    Engine_PhysicsBody* physicsBody2;
    Engine_PhysicsManifold manifold;

} Engine_PhysicsPair;

Engine_PhysicsPair PhysicsPair_Initialise();
void PhysicsPair_Clear(Engine_PhysicsPair* physicsPair);
void PhysicsPair_SetPairBodies(Engine_PhysicsPair* physicsPair, Engine_PhysicsBody* physicsBody1, Engine_PhysicsBody* physicsBody2);


typedef struct Engine_PhysicsBroadPhase
{
    int count;
    Engine_PhysicsPair PairList[6]; //Testing now: Need to implement pointer arith/stretchy array later.


} Engine_PhysicsBroadPhase;

Engine_PhysicsBroadPhase PhysicsBroadPhase_Initialise();
void PhysicsBroadPhase_GeneratePairList(Engine_PhysicsBroadPhase* physicsBroadPhase, Engine_ObjectManager* entityManager);
void PhysicsBroadPhase_CullDupicatesPairList(Engine_PhysicsBroadPhase* physicsBroadPhase);
void PhysicsBroadPhase_AddPair(Engine_PhysicsBroadPhase* physicsBroadPhase);
void PhysicsBroadPhase_Update(Engine_PhysicsBroadPhase* physicsBroadPhase);
void PhysicsBroadPhase_Query(Engine_PhysicsBroadPhase* physicsBroadPhase);


void Physics_InverseMass();
void Physics_SetVelocity(Engine_PhysicsBody* physicsBody, float deltaTime);
void Physics_Integration(Engine_PhysicsBody* physicsBody, float deltaTime);
void Physics_ApplyImpulse(Engine_PhysicsBody* physicsBody, Vector2 impulseVector);
void Physics_ApplyForce(Engine_PhysicsBody* physicsBody, Vector2 forceVector);
void Physics_UpdateRigid(Engine_PhysicsBody* physicsBody, float deltaTime);
void Physics_UpdateStatic(Engine_PhysicsBody* physicsBody, float deltaTime);
void Physics_CollisionResolve(Engine_PhysicsBody* physicsBody1, Engine_PhysicsBody* physicsBody2, Engine_PhysicsManifold* manifold);
Engine_PhysicsManifold Physics_CollisionNormal(Vector2 mid_1, Vector2 e1, Vector2 direction, float directionx, float directiony);
//Engine_PhysicsManifold Physics_Intersection( bodyTransform1, Engine_Matrix3x2 bodyTransform2);

#endif //Engine_Physics_H