#include <Engine/Engine_Draw.h>
#include <Engine/Engine_Globals.h>



void DrawCall(Engine_Draw* engineDraw, Engine_Update* engineUpdate)
{
    SDL_SetRenderDrawColor(Engine->Window->SDLRenderer, 0x80, 0x80, 0x80, 0x80);
    SDL_RenderClear(Engine->Window->SDLRenderer);
    SDL_RenderPresent(Engine->Window->SDLRenderer);
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
