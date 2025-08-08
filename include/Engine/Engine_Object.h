#ifndef Engine_Object_H
#define Engine_Object_H

#include <stdint.h>

//Forward declares
//

typedef enum ObjectType
{
    GAME,
    RENDER
};

typedef struct Engine_Object
{
    int ObjectID;
    enum ObjectType Type;
    void* Data;

} Engine_Object;


void Object_Initialise(Engine_Object* object, int id);


//#######################################################//
// -------------------Manager Systems------------------- //
typedef struct Engine_ObjectManager
{
    void *ObjectPool; //Memory block pointer
    
    int *ActiveList; // The ObjectPool index of the currently active objects
    int ActiveCount; // Number of active objects

    void *FreeList; // First free object ptr
    int FreeCount; // Number of not-in-use objects

    size_t ObjectSize;
    size_t ObjectCount;

    void (*InitObject)(void*, int); // Object Initialiser function
    void (*ConfigObject)(void*, int, int); // Object Setup function

} Engine_ObjectManager;


void ObjectManager_Initialise(Engine_ObjectManager *manager, size_t objectSize, size_t objectCount, void *initFunc, void *configFunc);

void* ObjectManager_Allocate(Engine_ObjectManager *manager);

void ObjectManager_Free(Engine_ObjectManager *manager, void *object);

Engine_Object* ObjectManager_Get(Engine_ObjectManager *manager, size_t index);


/*
#define MAX_OBJECT_LIMIT 512

typedef struct Engine_ObjectManager
{
    Engine_Object ObjectList[MAX_OBJECT_LIMIT];
    int FreeList[MAX_OBJECT_LIMIT];
    int FreeCount;
    bool ActiveIndex[MAX_OBJECT_LIMIT];
    int ActiveList[MAX_OBJECT_LIMIT];
    int ActiveCount;

    void (*InitObject);

} Engine_ObjectManager;


void ObjectManager_Initialise(Engine_ObjectManager* manager);
int ObjectManager_Allocate(Engine_ObjectManager* manager);
void ObjectManager_Free(Engine_ObjectManager* manager, int index);
Engine_Object* ObjectManager_Get(Engine_ObjectManager* manager, int index);
*/

#endif //Engine_Object_H