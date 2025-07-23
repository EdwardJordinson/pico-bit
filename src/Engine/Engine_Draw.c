#include <Engine/Engine_Draw.h>
#include <Engine/Engine_Globals.h>



void DrawCall(Engine_Renderer* renderer, Engine_GameState* gamestate)
{
    SDL_SetRenderDrawColor(Engine->Window->SDLRenderer, 0x80, 0x80, 0x80, 0x80);
    SDL_RenderClear(Engine->Window->SDLRenderer);
    DrawEntities(renderer, gamestate->EntityManager);
    SDL_RenderPresent(Engine->Window->SDLRenderer);
};

//(*entities)

void DrawEntities(Engine_Renderer* renderer, Engine_EntityManager* entityManager)
{
    for (int i = 0; i < entityManager->activeCount; i++)
    {
        int tID = entityManager->entities[entityManager->activeList[i]].ID;
        SDL_SetRenderDrawColor(Engine->Window->SDLRenderer, 0xff, 0xff, 0xff, 0xff);
        renderer->RectsLoaded[tID]->x = entityManager->entities[entityManager->activeList[i]].Position.x;
        renderer->RectsLoaded[tID]->y = entityManager->entities[entityManager->activeList[i]].Position.y;
        SDL_RenderFillRect(Engine->Window->SDLRenderer, renderer->RectsLoaded[tID]);
    }
};
