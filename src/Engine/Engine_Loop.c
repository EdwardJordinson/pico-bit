#include <Engine/Engine_Loop.h>
#include <Engine/Engine_Globals.h>
#include <Engine/Engine_Update.h>
#include <Engine/Engine_Draw.h>
#include <SDL3/SDL_timer.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>


void RunLoop(Engine_Loop** engineLoop)
{
    (*engineLoop)->running = true;

    const int targetFPS = 60;
    const int delayTime = 1000 / targetFPS;

    Uint32 loopTimer = SDL_GetTicks();
    Uint32 startTime;
    int frameCount = 0;
    float frameRate = 0.0f;

    //bool firstFrame = true;

    while ((*engineLoop)->running == true)
    {
        startTime = SDL_GetTicks();

        frameRate = frameCount/((SDL_GetTicks() - loopTimer)/1000.f);
        if (frameRate > 2000000)
        {
            frameRate = 0;
        }

        //PrintConsole(&firstFrame, frameRate, EngineLoop->delta);

        UpdateCall((*engineLoop)->GameState, (*engineLoop)->SDLEvent);
        DrawCall((*engineLoop)->Renderer, (*engineLoop)->GameState);
        ++frameCount;

        (*engineLoop)->delta = SDL_GetTicks() - startTime;
        if ((uint32_t)delayTime > (*engineLoop)->delta)
        {
            SDL_Delay(delayTime - (*engineLoop)->delta);
        }
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