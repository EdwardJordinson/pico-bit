#include <Engine/Engine_Loop.h>
#include <Engine/Engine_Globals.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_timer.h>
#include <stdio.h>


void RunLoop()
{
    EngineLoop->running = true;

    const int fps = 60;
    const int delayTime = 1000 / fps;

    Uint32 startTime;
    SDL_Event event;

    //int frameCount = 0;

    while (EngineLoop->running == true)
    {
        startTime = SDL_GetTicks();

        while (SDL_PollEvent(&event) == true)
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                EngineLoop->running = false;
            }
        }
        UpdateLoop();
        DrawLoop();

        EngineLoop->delta = SDL_GetTicks() - startTime;
        
        if (delayTime > EngineLoop->delta)
        {
            SDL_Delay(delayTime - EngineLoop->delta);
        }
        
        //printf("Frame Count: %d\n", frameCount++);
    }
};

void UpdateLoop()
{

};

void DrawLoop()
{
    SDL_RenderClear(EngineWindow->renderer);
    SDL_RenderTexture(EngineWindow->renderer, EngineWindow->texture, NULL, NULL);
    SDL_RenderPresent(EngineWindow->renderer);
};