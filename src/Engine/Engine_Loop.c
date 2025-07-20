#include <Engine/Engine_Loop.h>
#include <Engine/Engine_Globals.h>
#include <Engine/Engine_Entity.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_timer.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>


void RunLoop()
{
    EngineLoop->running = true;

    const int targetFPS = 60;
    const int delayTime = 1000 / targetFPS;

    Uint32 loopTimer = SDL_GetTicks();
    Uint32 startTime;
    int frameCount = 0;
    float frameRate = 0.0f;

    //bool firstFrame = true;

    SDL_Event event;

    while (EngineLoop->running == true)
    {
        startTime = SDL_GetTicks();

        while (SDL_PollEvent(&event) == true)
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                EngineLoop->running = false;
            }
            
            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
            {
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    float xMouse, yMouse;
                    SDL_GetMouseState(&xMouse, &yMouse);
                    if (Entities[0] == NULL)
                    {
                        AddEntity(xMouse, yMouse);
                    }
                    else
                    {
                        UpdateEntity(0, xMouse, yMouse);
                    }
                }
            }

        }

        frameRate = frameCount/((SDL_GetTicks() - loopTimer)/1000.f);
        if (frameRate > 2000000)
        {
            frameRate = 0;
        }

        //PrintConsole(&firstFrame, frameRate, EngineLoop->delta);

        UpdateLoop();
        DrawLoop();
        ++frameCount;

        EngineLoop->delta = SDL_GetTicks() - startTime;
        if ((uint32_t)delayTime > EngineLoop->delta)
        {
            SDL_Delay(delayTime - EngineLoop->delta);
        }
    }
};

void UpdateLoop()
{

};

void DrawLoop()
{ 
    SDL_SetRenderDrawColor(EngineWindow->renderer, 0x80, 0x80, 0x80, 0x80);
    SDL_RenderClear(EngineWindow->renderer);
    DrawEntities();
    SDL_RenderPresent(EngineWindow->renderer);
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

void PrintConsole(bool* firstFrame, int frameRate, Uint32 frameDelta)
{
    if (*firstFrame == true)
    {
        printf("\n\n\n");
        *firstFrame = false;
    }
    printf("\033[2A");
    printf("\r\033[2KFrame Rate : %d\n", frameRate);
    printf("\r\033[2KFrame Delta  : %" PRIu32 "\n",frameDelta);
    fflush(stdout);
};