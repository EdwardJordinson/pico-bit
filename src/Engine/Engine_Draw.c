#include <Engine/Engine_Draw.h>
#include <Engine/Engine_Globals.h>



void DrawCall(Engine_Renderer* renderer, Engine_GameState* gamestate)
{
    SDL_SetRenderDrawColor(Engine->Window->SDLRenderer, 0x80, 0x80, 0x80, 0x80);
    SDL_RenderClear(Engine->Window->SDLRenderer);
    DrawEntities(renderer, gamestate->EntitiesLoaded);
    SDL_RenderPresent(Engine->Window->SDLRenderer);
};

//(*entities)

void DrawEntities(Engine_Renderer* renderer, Engine_Entity* entities[])
{
    if (entities[0] != NULL)
    {
        SDL_SetRenderDrawColor(Engine->Window->SDLRenderer, 0xff, 0xff, 0xff, 0xff);
        renderer->RectsLoaded[entities[0]->ID]->x = entities[0]->Position.x;
        renderer->RectsLoaded[entities[0]->ID]->y = entities[0]->Position.y;
        SDL_RenderFillRect(Engine->Window->SDLRenderer, renderer->RectsLoaded[entities[0]->ID]);
    }

};


/*
void DrawLoop(Engine_Draw** engineDraw)
{ 
    SDL_SetRenderDrawColor(Engine->Window->SDLRenderer, 0x80, 0x80, 0x80, 0x80);
    SDL_RenderClear(Engine->Window->SDLRenderer);
    DrawEntities();
    SDL_RenderPresent(Engine->Window->SDLRenderer);
};

void DrawEntities()
{
    
    if (Entities[0] != NULL)
    {
        SDL_SetRenderDrawColor(EngineWindow->renderer, 0xff, 0xff, 0xff, 0xff);
        LoadedRects[Entities[0]->ID]->x = Entities[0]->Position.x;
        LoadedRects[Entities[0]->ID]->y = Entities[0]->Position.y;
        SDL_RenderFillRect(EngineWindow->renderer, LoadedRects[Entities[0]->ID]);
    }
    
};
*/
