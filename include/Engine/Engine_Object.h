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
    void* ObjectPool; //Memory block pointer
    
    int* ActiveList; // The ObjectPool index of the currently active objects - May not need this
    int ActiveCount; // Number of active objects

    void* FreeList; // First free object ptr
    int FreeCount; // Number of not-in-use objects

    size_t ObjectSize;
    size_t ObjectCount;

    void (*ConfigObject)(void*); // Object Setup function

} Engine_ObjectManager;


void ObjectManager_Initialise(Engine_ObjectManager* manager, size_t objectSize, size_t objectCount, void* configFunc);
Engine_Object* ObjectManager_Allocate(Engine_ObjectManager* manager);
void ObjectManager_Free(Engine_ObjectManager* manager, void* object);
Engine_Object* ObjectManager_Get(Engine_ObjectManager* manager, size_t index);
void ObjectManager_Shutdown(Engine_ObjectManager* manager);


#endif //Engine_Object_H