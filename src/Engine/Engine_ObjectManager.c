#include <Engine/Engine_Object.h>
#include <stdlib.h>


void ObjectManager_Initialise(Engine_ObjectManager* manager, size_t objectSize, size_t objectCount, void* configFunc)
{
    manager->ConfigObject = configFunc; //Will need another file to be loaded for engine defaults this functions will use deafult config provided
    manager->ObjectSize = (sizeof(Engine_Object) + objectSize);
    manager->ObjectCount = objectCount;
    manager->ObjectPool = malloc(manager->ObjectSize * objectCount);
    manager->FreeList = manager->ObjectPool;
    manager->FreeCount = objectCount;
    manager->ActiveCount = 0;
    manager->ActiveList = malloc(sizeof(int) * objectCount);

    char* base = manager->ObjectPool;
    for (size_t i = 0; i < objectCount - 1; i++)
    { 
        Engine_Object* currentObjectBase = (void*)(base + i * manager->ObjectSize);
        Object_Initialise(currentObjectBase, i);
        currentObjectBase->Data = (char*)currentObjectBase + sizeof(Engine_Object);

        void** current = (void**)(base + i * manager->ObjectSize);
        void* next = (void*)(base + (i + 1) * manager->ObjectSize);
        *current = next;
    }
    void** last = (void**)(base + (objectCount - 1) * manager->ObjectSize);
    *last = NULL;
};

Engine_Object* ObjectManager_Allocate(Engine_ObjectManager* manager)
{
    if (manager->FreeList == NULL) return NULL;

    Engine_Object* allocated = manager->FreeList;
    manager->FreeList = *(void**)manager->FreeList;
    manager->ConfigObject(allocated->Data);
    manager->ActiveCount += 1;
    return allocated;
};

void ObjectManager_Free(Engine_ObjectManager* manager, void* object)
{
    *(void**)object = manager->FreeList;
    manager->FreeList = object;
    manager->ActiveCount -= 1;
};

Engine_Object* ObjectManager_Get(Engine_ObjectManager* manager, size_t index)
{
    if (index >= manager->ObjectCount) return NULL;

    char* base = (char*)manager->ObjectPool;
    return (void*)(base + index * manager->ObjectSize);
};

void ObjectManager_Shutdown(Engine_ObjectManager* manager)
{
    free(manager->FreeList);
    free(manager->ObjectPool);

};