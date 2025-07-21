#include <Engine/Engine_Shutdown.h>
#include <Engine/Engine_Globals.h>
#include <SDL3/SDL_init.h>


void Shutdown()
{
    SDL_DestroyRenderer(Engine->Window->SDLRenderer);
    SDL_DestroyWindow(Engine->Window->SDLWindow);

    SDL_Quit();
};