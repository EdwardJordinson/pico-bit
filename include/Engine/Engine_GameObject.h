#ifndef Engine_GameObject_H
#define Engine_GameObject_H

#include <Engine/Engine_Coordinates.h>
#include <Engine/Engine_Collision.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

//Forward declares
typedef struct Engine_EventHandler Engine_EventHandler;
typedef struct Engine_Manifold Engine_Manifold;
typedef struct Vector2 Vector2;
typedef struct Engine_AABB Engine_AABB;
//

typedef struct Engine_GameObject
{
    int RenderID;
    Engine_Matrix3x2 Transform2D;
    Vector2 Velocity;
    Engine_AABB CollisionShape;
    float Restitution; //Bouncy-ness
    float Mass;

    void (*Update)(struct Engine_GameObject*,float);

} Engine_GameObject;


void GameObject_Initialise();
void GameObject_SetDefault(Engine_GameObject* gameObject);
void GameObject_SetConfiguration(Engine_GameObject* gameObject, Engine_GameObject configObject);
void GameObject_SetPositionXY(Engine_GameObject* gameObject, float xPosition, float yPosition);
void GameObject_SetPositionVector(Engine_GameObject* gameObject, Vector2 vector);
void GameObject_SetVelocity(Engine_GameObject* gameObject, Vector2 vector);

//Move these into physics code
void GameObject_UpdateRigid(Engine_GameObject* gameObject, float deltaTime);
void GameObject_UpdateStatic(Engine_GameObject* gameObject, float deltaTime);
void GameObject_CollisionResolve(Engine_GameObject* gameObject1, Engine_GameObject* gameObject2, Engine_Manifold* manifold);
Engine_Manifold GameObject_CollisionNormal(Engine_GameObject* gameObject1, Engine_GameObject* gameObject2);


#endif //Engine_GameObject_H