#ifndef Engine_Physics_H
#define Engine_Physics_H

#include <Engine/Engine_Coordinates.h>
#include <Engine/Engine_Collision.h>
#include <stdbool.h>

//Forward declares
typedef struct Engine_GameObject Engine_GameObject;
//

typedef struct Engine_PhysicsManifold
{
    bool Hit; 
    Vector2 HitSpot;
    float Depth;
    Vector2 Normal;

} Engine_PhysicsManifold;


Engine_PhysicsManifold Manifold_Initialise();


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
    Engine_AABB CollisionShape;
    Engine_PhysicsMass MassData;
    Engine_PhysicsMaterial Material;
    Engine_Matrix3x2 Transform2D;
    Vector2 Velocity;
    Vector2 Force;

 } Engine_PhysicsBody;


Engine_PhysicsBody PhysicsBody_Initialise();


typedef struct Engine_PhysicsPair
{
    Engine_PhysicsBody* physicsBody1;
    Engine_PhysicsBody* physicsBody2;

} Engine_PhysicsPair;


Engine_PhysicsPair PhysicsPair_Initialise();
void PhysicsPair_SetBodyAll(Engine_PhysicsPair* physicsPair, Engine_PhysicsBody* physicsBody1, Engine_PhysicsBody* physicsBody2);
void PhysicsPair_Clear();
void PhysicsPair_Generate();

void Physics_InverseMass();
void Physics_SetVelocity(Engine_PhysicsBody* physicsBody, float deltaTime);
void Physics_SetAcceleration(Engine_PhysicsBody* physicsBody, float deltaTime);
void Physics_UpdateRigid(Engine_PhysicsBody* physicsBody, float deltaTime);
void Physics_UpdateStatic(Engine_PhysicsBody* physicsBody, float deltaTime);
void Physics_CollisionResolve(Engine_PhysicsBody* physicsBody1, Engine_PhysicsBody* physicsBody2, Engine_PhysicsManifold* manifold);
Engine_PhysicsManifold Physics_CollisionNormal(Vector2 mid_1, Vector2 e1, Vector2 direction, float directionx, float directiony);
void Physics_BoardPhase();

#endif //Engine_Physics_H