#include <Engine/Engine_MainLoop.h>
#include <Engine/Engine_EventProcess.h>
#include <Engine/Engine_GameState.h>
#include <Engine/Engine_RenderState.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_timer.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>


void MainLoop_Intitialise(Engine_MainLoop* mainLoop)
{
    mainLoop->running = false;
    mainLoop->delta = 0.0;

};

void MainLoop_Run(Engine_MainLoop* engineLoop)
{
    engineLoop->running = true;

    const float targetFPS = 60;
    const float delayTime = 1000 / targetFPS;

    Uint64 runTime = SDL_GetTicks();
    Uint64 lastTime = SDL_GetTicks();
    Uint64 currentTime;

    int frameCount = 0;
    float frameRate = 0.0f;

    bool firstFrame = true;

    while (engineLoop->running == true)
    {   
        EventProcess_Check(engineLoop->EventProcess, engineLoop->GameState, &engineLoop->running);

        frameRate = frameCount/((lastTime - runTime)/1000.f);
        if (frameRate > 5000.0f) frameRate = 0.0f;

        //Make this output to the screen with SDL_ttf
        //MainLoop_PrintConsole(&firstFrame, frameRate, (*engineLoop)->delta);
        
        GameState_Update(engineLoop->GameState, engineLoop->EventProcess, engineLoop->delta);
        RenderState_Draw(engineLoop->RenderState, engineLoop->GameState);
        ++frameCount;
        
        currentTime = SDL_GetTicks();
        engineLoop->delta = (currentTime - lastTime)/1000.0f;
        lastTime = currentTime;

        if (engineLoop->delta < delayTime)
        {
            //SDL_Delay(delayTime - (*engineLoop)->delta);
        }    
    }
};

void MainLoop_PrintConsole(bool* firstFrame, float frameRate, float frameDelta)
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