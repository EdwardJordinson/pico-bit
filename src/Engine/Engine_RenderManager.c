#include <Engine/Engine_RenderManager.h>


void RenderManager_Initialise(Engine_RenderManager* manager)
{
    manager->freeCount = MAX_ENTITY_SIZE;
    manager->activeCount = 0;

    for (int i = 0; i < MAX_ENTITY_SIZE; ++i)
    {
        manager->freeList[i] = MAX_ENTITY_SIZE - 1 - i;
        manager->active[i] = false;
    }
};

int RenderManager_Allocate(Engine_RenderManager* manager)
{
    if (manager->freeCount <= 0)
    {
        return -1;
    }

    int index = manager->freeList[--manager->freeCount];
    manager->active[index] = true;

    //Need creation pipeline
    SDL_FRect* newObject = &manager->objects[index];
    newObject->h = 100.0;
    newObject->w = 100.0;
    newObject->x = 0.0;
    newObject->y = 0.0;

    manager->activeList[manager->activeCount++] = index;

    return index;
};

void RenderManager_Free(Engine_RenderManager* manager, int index)
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

SDL_FRect* RenderManager_Get(Engine_RenderManager* manager, int index)
{
    if (index < 0 || index >= MAX_ENTITY_SIZE || !manager->active[index]) 
    {
        return NULL;
    }

    return &manager->objects[index];
};