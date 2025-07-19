#include <Engine/Engine_ControlLoop.h>
#include <Engine/Engine_Window.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <stdio.h>


void RunLoop(Engine_ControlLoop *controlLoop)
{
    controlLoop->running = true;
    SDL_Event event;

    while (controlLoop->running == true)
    {
        while (SDL_PollEvent(&event) == true)
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                controlLoop->running = false;
            }
        }
        UpdateLoop();
        DrawLoop(controlLoop->window);
    }
};

void UpdateLoop()
{

};

void DrawLoop(Engine_Window *engineWindow)
{
    SDL_RenderClear(engineWindow->renderer);
    SDL_RenderTexture(engineWindow->renderer, engineWindow->texture, NULL, NULL);
    SDL_RenderPresent(engineWindow->renderer);
};