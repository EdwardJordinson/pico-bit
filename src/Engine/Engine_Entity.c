#include <Engine/Engine_Entity.h>
#include <Engine/Engine_Globals.h>
#include <Engine/Engine_Vector2.h>
#include <stdlib.h>
#include <stdio.h>


int InitEntity()
{

    return 0;
};

void AddEntity(int xPosition, int yPosition)
{
    int newID = Engine_Entity_Allocate(Engine->Loop->GameState->EntityManager);
    Engine_Entity* newEntity = Engine_Entity_Get(Engine->Loop->GameState->EntityManager, newID);
    SetupEntity(newEntity, xPosition, yPosition);

};

void UpdateEntity(int entityID, int xPosition, int yPosition)
{
    Engine_Entity* newEntity = Engine_Entity_Get(Engine->Loop->GameState->EntityManager, entityID);
    newEntity->Position = Vector2_Initialise(xPosition - (Engine->Loop->Renderer->RectsLoaded[0]->w/2), yPosition - (Engine->Loop->Renderer->RectsLoaded[0]->h/2));
};

void SetupEntity(Engine_Entity* entity, int xPosition, int yPosition)
{
    entity->Position = Vector2_Initialise(xPosition, yPosition);
    //entity->Position.x = xPosition - (Engine->Loop->Renderer->RectsLoaded[0]->w/2);
    //entity->Position.y = yPosition - (Engine->Loop->Renderer->RectsLoaded[0]->h/2);

    entity->Velocity = Vector2_Initialise(50.0, 0.0);
};

void SimulateEntity(Engine_Entity* entity, float deltaTime)
{
    Vector2 newVector = Vector2_ScalarMuliply(deltaTime, &entity->Velocity);
    entity->Position = Vector2_VectorAdd(&entity->Position, &newVector);
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