#include <Engine/Engine_Shutdown.h>
#include <Engine/Engine_Globals.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>


void Engine_Shutdown()
{
    //SDL_DestroyRenderer(Engine->Window->SDLRenderer);
    //SDL_DestroyWindow(Engine->Window->SDLWindow);

    SDL_Quit();
};