#include <Engine/Engine_Object.h>
#include <stdlib.h>


void ObjectManager_Initialise(Engine_ObjectManager* manager)
{
    manager->FreeCount = MAX_OBJECT_LIMIT;
    manager->ActiveCount = 0;

    for (int i = 0; i < MAX_OBJECT_LIMIT; ++i)
    {
        manager->FreeList[i] = MAX_OBJECT_LIMIT - 1 - i;
        manager->ActiveIndex[i] = false;
    }
};

int ObjectManager_Allocate(Engine_ObjectManager* manager)
{
    if (manager->FreeCount <= 0)
    {
        return -1;
    }

    int index = manager->FreeList[--manager->FreeCount];
    manager->ActiveIndex[index] = true;

    Engine_Object* newObject = &manager->ObjectList[index];
    Object_Setup(newObject, 0.0,0.0);
    //Entity_Setup(newEntity, 640/2,480/2);
    //memset(newEntity, 0, sizeof(Engine_Entity));
    newObject->ID = index;
    newObject->renderID = 0;

    manager->ActiveList[manager->ActiveCount++] = index;

    return index;
};

void ObjectManager_Free(Engine_ObjectManager* manager, int index)
{
    if (index < 0 || index >= MAX_OBJECT_LIMIT || !manager->ActiveList[index])
    {
        return;
    }

    manager->ActiveList[index] = false;
    manager->FreeList[manager->FreeCount++] = index;

    for (int i = 0; i < manager->ActiveCount; ++i) {
        if (manager->ActiveList[i] == index) {
            manager->ActiveList[i] = manager->ActiveList[--manager->ActiveCount];
            break;
        }
    }
};

Engine_Object* ObjectManager_Get(Engine_ObjectManager* manager, int index)
{
    if (index < 0 || index >= MAX_OBJECT_LIMIT || !manager->ActiveIndex[index]) 
    {
        return NULL;
    }

    return &manager->ObjectList[index];
};



void ObjectManagerTEST_Initialise(Engine_ObjectManagerTEST* manager, size_t objectSize, size_t objectCount, void* initFunc)
{
    manager->InitObject = initFunc;
    manager->ObjectSize = (objectSize > sizeof(void*)) ? objectSize : sizeof(void*);
    manager->ObjectCount = objectCount;
    manager->ObjectPool = malloc(manager->ObjectSize * objectCount);
    manager->FreeList = manager->ObjectPool;
    manager->FreeCount = objectCount;
    manager->ActiveCount = 0;
    manager->ActiveList = malloc(sizeof(int) * objectCount);
    manager->ActiveIndex = malloc(sizeof(bool) * objectCount);

    char *ptr = manager->ObjectPool;
    for (size_t i = 0; i < objectCount - 1; i++)
    {
        void **current = (void**)(ptr + i * manager->ObjectSize); 
        void *next = (void*)(ptr + (i + 1) * manager->ObjectSize);
        *current = next;
    }
    void **last = (void**)(ptr + (objectCount - 1) * manager->ObjectSize);
    *last = NULL;
};

void *ObjectManagerTEST_Allocate(Engine_ObjectManagerTEST* manager)
{
    if (manager->FreeList == NULL) return NULL;

    void *allocated = manager->FreeList;
    manager->FreeList = *(void **)manager->FreeList;//looking into that
    return allocated;
};

void ObjectManagerTEST_Free(Engine_ObjectManagerTEST* manager, void* object)
{
    *(void **)object = manager->FreeList;
    manager->FreeList = object;
};

Engine_Object* ObjectManagerTEST_Get(Engine_ObjectManagerTEST* manager, size_t index)
{
    if (index >= manager->ObjectCount) return NULL;

    char *base = (char *)manager->ObjectPool;
    return (void *)(base + index * manager->ObjectSize);
};