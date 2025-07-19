#include <Engine/Engine_Shutdown.h>
#include <Engine/Engine_Window.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_init.h>


void Shutdown(Engine_Window *engineWindow)
{
    SDL_DestroyTexture(engineWindow->texture);
    SDL_DestroyRenderer(engineWindow->renderer);
    SDL_DestroyWindow(engineWindow->window);

    SDL_Quit();
};