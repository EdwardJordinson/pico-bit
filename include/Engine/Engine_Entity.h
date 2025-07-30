#ifndef Engine_Entity_H
#define Engine_Entity_H

#include <Engine/Engine_Vector2.h>
#include <Engine/Engine_AABB.h>
#include <stdint.h>

//Forward declares
typedef struct Engine_EventHandler Engine_EventHandler;
//

typedef struct Engine_Entity
{
    int ID;
    int renderID;
    Vector2 Position;
    Vector2 Velocity;
    AABB BoundingBox;

    void (*update)(struct Engine_Entity*,float);

} Engine_Entity;


Engine_Entity Entity_Initialise(int id);

void Entity_Setup(Engine_Entity* entity, int xPosition, int yPosition);

void Entity_Event(Engine_Entity* entity, Engine_EventHandler* eventHandler);

void Entity_SetPosition(Engine_Entity* entity, int xPosition, int yPosition);

void Entity_SetVelocity(Engine_Entity* entity, Vector2 vector);

void Entity_UpdateRigid(Engine_Entity* entity, float deltaTime);

void Entity_UpdateStatic(Engine_Entity* entity, float deltaTime);

#endif //Engine_Entity_H