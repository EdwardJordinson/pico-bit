#include <Engine/Engine_Shutdown.h>
#include <Engine/Engine_Globals.h>
#include <SDL3/SDL_init.h>


void Shutdown()
{
    SDL_DestroyRenderer(EngineWindow->renderer);
    SDL_DestroyWindow(EngineWindow->window);

    SDL_Quit();
};