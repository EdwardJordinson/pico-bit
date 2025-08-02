#include <Engine/Engine_Object.h>


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