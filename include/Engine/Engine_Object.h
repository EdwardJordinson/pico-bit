#ifndef Engine_Object_H
#define Engine_Object_H

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

typedef struct Engine_Object
{
    int ID;
    int renderID;
    Engine_Matrix3x2 Transform2D;
    Vector2 Velocity; //Movement Direction/Speed
    Engine_AABB CollisionShape;
    float Restitution; //Bouncy-ness
    float Mass; //Mass

    void (*update)(struct Engine_Object*,float);

} Engine_Object;


Engine_Object Object_Initialise(int id);

void Object_Setup(Engine_Object* object, int xPosition, int yPosition);

void Object_Event(Engine_Object* object, Engine_EventHandler* eventHandler);

void Object_SetPosition(Engine_Object* object, int xPosition, int yPosition);

void Object_SetVelocity(Engine_Object* object, Vector2 vector);

void Object_UpdateRigid(Engine_Object* object, float deltaTime);

void Object_UpdateStatic(Engine_Object* object, float deltaTime);

void Object_CollisionResolve(Engine_Object* object1, Engine_Object* object2, Engine_Manifold* manifold);

Engine_Manifold Object_CollisionNormal(Engine_Object* object1, Engine_Object* object2);


//#######################################################//
// -------------------Manager Systems------------------- //
#define MAX_OBJECT_LIMIT 512

typedef struct Engine_ObjectManager
{
    Engine_Object ObjectList[MAX_OBJECT_LIMIT];
    int FreeList[MAX_OBJECT_LIMIT];
    int FreeCount;
    bool ActiveIndex[MAX_OBJECT_LIMIT];
    int ActiveList[MAX_OBJECT_LIMIT];
    int ActiveCount;

} Engine_ObjectManager;


void ObjectManager_Initialise(Engine_ObjectManager* manager);

int ObjectManager_Allocate(Engine_ObjectManager* manager);

void ObjectManager_Free(Engine_ObjectManager* manager, int index);

Engine_Object* ObjectManager_Get(Engine_ObjectManager* manager, int index);

#endif //Engine_Object_H