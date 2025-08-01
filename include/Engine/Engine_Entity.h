#ifndef Engine_Entity_H
#define Engine_Entity_H

#include <Engine/Engine_Vector2.h>
#include <Engine/Engine_AABB.h>
#include <stdint.h>

//Forward declares
typedef struct Engine_EventHandler Engine_EventHandler;
typedef struct Engine_Manifold Engine_Manifold;
//

typedef struct Engine_Entity
{
    int ID;
    int renderID;
    Vector2 Position; //Origin
    BasisVector2 Basis; //Transform
    Vector2 Velocity; //Movement Direction/Speed
    AABB BoundingBox;
    float Restitution; //Bouncy-ness
    float Mass; //Mass

    void (*update)(struct Engine_Entity*,float);

} Engine_Entity;


Engine_Entity Entity_Initialise(int id);

void Entity_Setup(Engine_Entity* entity, int xPosition, int yPosition);

void Entity_Event(Engine_Entity* entity, Engine_EventHandler* eventHandler);

void Entity_SetPosition(Engine_Entity* entity, int xPosition, int yPosition);

void Entity_SetVelocity(Engine_Entity* entity, Vector2 vector);

void Entity_UpdateRigid(Engine_Entity* entity, float deltaTime);

void Entity_UpdateStatic(Engine_Entity* entity, float deltaTime);

void Entity_CollisionResolve(Engine_Entity* entity1, Engine_Entity* entity2, Engine_Manifold* manifold);

Engine_Manifold Entity_CollisionNormal(Engine_Entity* entity1, Engine_Entity* entity2);

#endif //Engine_Entity_H