#include <Engine/Engine_RenderState.h>
#include <Engine/Engine_GameState.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>


void RenderState_Draw(Engine_RenderState* rendererState, Engine_GameState* gameState)
{
    SDL_SetRenderDrawColor(rendererState->SDLRenderer, 0x80, 0x80, 0x80, 0x80);
    SDL_RenderClear(rendererState->SDLRenderer);
    Draw_Entities(rendererState, gameState->EntityManager);
    SDL_RenderPresent(rendererState->SDLRenderer);
};

void Draw_Entities(Engine_RenderState* rendererState, Engine_EntityManager* entityManager)
{
    for (int i = 0; i < entityManager->activeCount; i++)
    {   
        Engine_Entity* tempEntity = EntityManager_Get(entityManager, i);
        SDL_FRect* tempFRect = RenderManager_Get(rendererState->RenderManager, tempEntity->ID);
        SDL_SetRenderDrawColor(rendererState->SDLRenderer, 0xff, 0xff, 0xff, 0xff);
        tempFRect->x = tempEntity->Position.x;
        tempFRect->y = tempEntity->Position.y;
        SDL_RenderFillRect(rendererState->SDLRenderer, tempFRect);
    }
};
