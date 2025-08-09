#ifndef Engine_Physics_H
#define Engine_Physics_H

#include <Engine/Engine_Coordinates.h>

//Forward declares
typedef struct Engine_GameObject Engine_GameObject;
//

typedef struct Engine_Manifold
{
    bool Hit;
    Vector2 HitSpot;
    float Depth;
    Vector2 Normal;

} Engine_Manifold;


void Physics_InverseMass();
void Physics_CollisionResolve();
void Physics_SetVelocity(Engine_GameObject* object, Vector2 vector);
void Physics_UpdateRigid(Engine_GameObject* object, float deltaTime);
void Physics_UpdateStatic(Engine_GameObject* object, float deltaTime);
void Physics_CollisionResolve(Engine_GameObject* object1, Engine_GameObject* object2, Engine_Manifold* manifold);
Engine_Manifold Physics_CollisionNormal(Engine_GameObject* object1, Engine_GameObject* object2);

#endif //Engine_Physics_H