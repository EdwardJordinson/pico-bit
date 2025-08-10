#ifndef Engine_Physics_H
#define Engine_Physics_H

#include <Engine/Engine_Coordinates.h>
#include <stdbool.h>

//Forward declares
typedef struct Engine_GameObject Engine_GameObject;
//

typedef struct Physics_Manifold
{
    bool Hit;
    Vector2 HitSpot;
    float Depth;
    Vector2 Normal;

} Physics_Manifold;

typedef struct Physics_Mass
{
    float Mass;
    float InverseMass;

    float Inertia;
    float InverseInertia;
} Physics_Mass;

typedef struct Physics_Material
{
    float Density;
    float Restitution;
} Physics_Material;

typedef struct Physics_Body
{
    void* CollisionShape;
    Physics_Mass MassData;
    Physics_Material Material;
    Vector2 Velocity;
    Vector2 Force;

};

Physics_Manifold Manifold_Initialise();

void Physics_InverseMass();
void Physics_SetVelocity(Engine_GameObject* gameObject, Vector2 vector);
void Physics_UpdateRigid(Engine_GameObject* gameObject, float deltaTime);
void Physics_UpdateStatic(Engine_GameObject* gameObject, float deltaTime);
void Physics_CollisionResolve(Engine_GameObject* gameObject1, Engine_GameObject* gameObject2, Physics_Manifold* manifold);
Physics_Manifold Physics_CollisionNormal(Vector2 mid_1, Vector2 e1, Vector2 direction, float directionx, float directiony);


#endif //Engine_Physics_H