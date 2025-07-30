#include <Engine/Engine_EntityManager.h>


void EntityManager_Initialise(Engine_EntityManager* manager)
{
    manager->freeCount = MAX_ENTITY_SIZE;
    manager->activeCount = 0;

    for (int i = 0; i < MAX_ENTITY_SIZE; ++i)
    {
        manager->freeList[i] = MAX_ENTITY_SIZE - 1 - i;
        manager->active[i] = false;
    }
};

int EntityManager_Allocate(Engine_EntityManager* manager)
{
    if (manager->freeCount <= 0)
    {
        return -1;
    }

    int index = manager->freeList[--manager->freeCount];
    manager->active[index] = true;

    Engine_Entity* newEntity = &manager->entities[index];
    Entity_Setup(newEntity, 0.0,0.0);
    //Entity_Setup(newEntity, 640/2,480/2);
    //memset(newEntity, 0, sizeof(Engine_Entity));
    newEntity->ID = index;
    newEntity->renderID = 0;

    manager->activeList[manager->activeCount++] = index;

    return index;
};

void EntityManager_Free(Engine_EntityManager* manager, int index)
{
    if (index < 0 || index >= MAX_ENTITY_SIZE || !manager->active[index])
    {
        return;
    }

    manager->active[index] = false;
    manager->freeList[manager->freeCount++] = index;

    for (int i = 0; i < manager->activeCount; ++i) {
        if (manager->activeList[i] == index) {
            manager->activeList[i] = manager->activeList[--manager->activeCount];
            break;
        }
    }
};

Engine_Entity* EntityManager_Get(Engine_EntityManager* manager, int index)
{
    if (index < 0 || index >= MAX_ENTITY_SIZE || !manager->active[index]) 
    {
        return NULL;
    }

    return &manager->entities[index];
};