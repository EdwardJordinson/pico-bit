#include <Engine/Engine_Entity.h>
#include <Engine/Engine_Globals.h>
#include <stdlib.h>
#include <stdio.h>


int InitEntity()
{
    Engine_Entity* newEntity = malloc(sizeof(Engine_Entity));
    newEntity->Position.x = 0;
    newEntity->Position.y = 0;

    newEntity->Shape[0].x = 100;
    newEntity->Shape[0].y = -100;

    newEntity->Shape[1].x = 100;
    newEntity->Shape[1].y = 100;

    newEntity->Shape[2].x = -100;
    newEntity->Shape[2].y = 100;

    newEntity->Shape[3].x = -100;
    newEntity->Shape[3].y = -100;

    newEntity->ID = 0;

    //Engine->Loop->GameState->EntitiesLoaded[0] = newEntity;

    return 0;
};

void AddEntity(int xPosition, int yPosition)
{
    int newID = Engine_Entity_Allocate(Engine->Loop->GameState->EntityManager);
    Engine_Entity* newEntity = Engine_Entity_Get(Engine->Loop->GameState->EntityManager, newID);
    newEntity->Position.x = xPosition - (Engine->Loop->Renderer->RectsLoaded[0]->w/2);
    newEntity->Position.y = yPosition - (Engine->Loop->Renderer->RectsLoaded[0]->h/2);

};

void UpdateEntity(int entityID, int xPosition, int yPosition)
{
    Engine_Entity* newEntity = Engine_Entity_Get(Engine->Loop->GameState->EntityManager, entityID);
    newEntity->Position.x = xPosition - (Engine->Loop->Renderer->RectsLoaded[0]->w/2);
    newEntity->Position.y = yPosition - (Engine->Loop->Renderer->RectsLoaded[0]->h/2);
};

int Engine_Entity_Allocate(Engine_EntityManager* manager)
{
    if (manager->freeCount <= 0)
    {
        return -1;
    }

    int index = manager->freeList[--manager->freeCount];
    manager->active[index] = true;

    Engine_Entity* newEntity = &manager->entities[index];
    memset(newEntity, 0, sizeof(Engine_Entity));
    newEntity->ID = index;

    manager->activeList[manager->activeCount++] = index;

    return index;
};

void Engine_Entity_Free(Engine_EntityManager* manager, int index)
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

Engine_Entity* Engine_Entity_Get(Engine_EntityManager* manager, int index)
{
    if (index < 0 || index >= MAX_ENTITY_SIZE || !manager->active[index]) 
    {
        return NULL;
    }

    return &manager->entities[index];
};