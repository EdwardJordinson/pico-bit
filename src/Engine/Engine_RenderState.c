#include <Engine/Engine_RenderState.h>
#include <Engine/Engine_Globals.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>


void Draw_Call(Engine_RenderState* rendererState, Engine_GameState* gameState)
{
    SDL_SetRenderDrawColor(Engine->Window->SDLRenderer, 0x80, 0x80, 0x80, 0x80);
    SDL_RenderClear(Engine->Window->SDLRenderer);
    Draw_Entities(rendererState, gameState->EntityManager);
    SDL_RenderPresent(Engine->Window->SDLRenderer);
};

void Draw_Entities(Engine_RenderState* rendererState, Engine_EntityManager* entityManager)
{
    for (int i = 0; i < entityManager->activeCount; i++)
    {
        int tID = entityManager->entities[entityManager->activeList[i]].ID;
        SDL_SetRenderDrawColor(Engine->Window->SDLRenderer, 0xff, 0xff, 0xff, 0xff);
        rendererState->RectsLoaded[tID]->x = entityManager->entities[entityManager->activeList[i]].Position.x;
        rendererState->RectsLoaded[tID]->y = entityManager->entities[entityManager->activeList[i]].Position.y;
        SDL_RenderFillRect(Engine->Window->SDLRenderer, rendererState->RectsLoaded[tID]);
    }
};
