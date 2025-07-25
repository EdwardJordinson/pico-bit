#ifndef Engine_Entity_Manager_H
#define Engine_Entity_Manager_H

#include <Engine/Engine_Entity.h>
#include <stdbool.h>
#include <stddef.h>

//Forward declares
//

#define MAX_ENTITY_SIZE 512

typedef struct Engine_EntityManager
{
    Engine_Entity entities[MAX_ENTITY_SIZE];
    int freeList[MAX_ENTITY_SIZE];
    int freeCount;
    bool active[MAX_ENTITY_SIZE];
    int activeList[MAX_ENTITY_SIZE];
    int activeCount;

} Engine_EntityManager;


int EntityManager_Allocate(Engine_EntityManager* manager);

void EntityManager_Free(Engine_EntityManager* manager, int index);

Engine_Entity* EntityManager_Get(Engine_EntityManager* manager, int index);

#endif // Engine_Entity_Manager_H
