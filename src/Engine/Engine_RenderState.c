#include <Engine/Engine_RenderState.h>
#include <Engine/Engine_Globals.h>
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
        int tID = entityManager->entities[entityManager->activeList[i]].ID;
        SDL_SetRenderDrawColor(rendererState->SDLRenderer, 0xff, 0xff, 0xff, 0xff);
        rendererState->RectsLoaded[tID]->x = entityManager->entities[entityManager->activeList[i]].Position.x;
        rendererState->RectsLoaded[tID]->y = entityManager->entities[entityManager->activeList[i]].Position.y;
        SDL_RenderFillRect(rendererState->SDLRenderer, rendererState->RectsLoaded[tID]);
    }
};
