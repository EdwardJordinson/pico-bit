#include <Engine/Engine_ControlLoop.h>
#include <Engine/Engine_Window.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <stdio.h>


void RunLoop(Engine_ControlLoop *controlLoop)
{
    controlLoop->running = true;

    const int fps = 60;
    const int delayTime = 1000 / fps;

    Uint32 startTime;
    SDL_Event event;

    int frameCount = 0;

    while (controlLoop->running == true)
    {
        startTime = SDL_GetTicks();

        while (SDL_PollEvent(&event) == true)
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                controlLoop->running = false;
            }
        }
        UpdateLoop();
        DrawLoop(controlLoop->window);

        controlLoop->delta = SDL_GetTicks() - startTime;
        
        if (delayTime > controlLoop->delta)
        {
            SDL_Delay(delayTime - controlLoop->delta);
        }
        
        //printf("Frame Count: %d\n", frameCount++);
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