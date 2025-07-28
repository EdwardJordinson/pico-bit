#ifndef Engine_RenderManager_H
#define Engine_RenderManager_H

#include <SDL3/SDL_rect.h>

//Forward declares
//

#define MAX_ENTITY_SIZE 512

typedef struct Engine_RenderManager
{
    SDL_FRect objects[MAX_ENTITY_SIZE];
    int freeList[MAX_ENTITY_SIZE];
    int freeCount;
    bool active[MAX_ENTITY_SIZE];
    int activeList[MAX_ENTITY_SIZE];
    int activeCount;

} Engine_RenderManager;


void RenderManager_Initialise(Engine_RenderManager* manager);

int RenderManager_Allocate(Engine_RenderManager* manager);

void RenderManager_Free(Engine_RenderManager* manager, int index);

SDL_FRect* RenderManager_Get(Engine_RenderManager* manager, int index);

#endif //Engine_RenderManager_H