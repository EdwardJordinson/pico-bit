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

    const float targetFPS = 60;
    const float delayTime = 1000 / targetFPS;

    Uint64 runTime = SDL_GetTicks();
    Uint64 lastTime = SDL_GetTicks();
    Uint64 currentTime;

    int frameCount = 0;
    float frameRate = 0.0f;

    bool firstFrame = true;

    while ((*engineLoop)->running == true)
    {   

        frameRate = frameCount/((lastTime - runTime)/1000.f);
        if (frameRate > 500.0f) frameRate = 0.0f;

        PrintConsole(&firstFrame, frameRate, (*engineLoop)->delta);
        
        UpdateCall((*engineLoop)->GameState, (*engineLoop)->SDLEvent);
        DrawCall((*engineLoop)->Renderer, (*engineLoop)->GameState);
        ++frameCount;
        
        currentTime = SDL_GetTicks();
        (*engineLoop)->delta = (currentTime - lastTime)/1000.0f;
        lastTime = currentTime;

        
        if ((*engineLoop)->delta < delayTime)
        {
            SDL_Delay(delayTime - (*engineLoop)->delta);
        }    
    
    }
};

void PrintConsole(bool* firstFrame, float frameRate, float frameDelta)
{
    if (*firstFrame == true)
    {
        printf("\n\n\n");
        *firstFrame = false;
    }
    printf("\033[5A");
    printf("\r\033[2KFrame Rate : %.2f\n", frameRate);
    printf("\r\033[2KFrame Delta  : %.4f\n",frameDelta);
    fflush(stdout);
};