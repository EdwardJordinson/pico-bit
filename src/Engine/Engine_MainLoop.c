#include <Engine/Engine_MainLoop.h>
#include <Engine/Engine_EventProcess.h>
#include <Engine/Engine_GameState.h>
#include <Engine/Engine_RenderState.h>
#include <Engine/Engine_RenderObject.h>
#include <Engine/Engine_Object.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_timer.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>


void MainLoop_Intitialise(Engine_MainLoop* mainLoop)
{
    mainLoop->running = false;

};

void MainLoop_Run(Engine_MainLoop* engineLoop)
{
    engineLoop->running = true;

    const float targetFPS = 60.0f;
    const float delayTime = 1000.0f / targetFPS;
    float accumulator, currentTime, lastTime, constantDelay;
    constantDelay = 0.001;
    lastTime = SDL_GetTicks();
    
    float frameTime = SDL_GetTicks();
    int frameCount = 0;
    float frameRate = 0.0f;
    
    while (engineLoop->running == true)
    {   
        EventProcess_Check(engineLoop->EventProcess, engineLoop->GameState, &engineLoop->running);

        accumulator += engineLoop->GameState->delta;
        while(accumulator >= constantDelay)
        {
            GameState_Update(engineLoop->GameState, engineLoop->EventProcess);

            accumulator -= constantDelay;
        }

        RenderState_Draw(engineLoop->RenderState, engineLoop->GameState);

        currentTime = SDL_GetTicks();
        engineLoop->GameState->delta = (currentTime - lastTime)/1000.0f;
        lastTime = currentTime;

        if (engineLoop->GameState->delta < delayTime)
        {
            SDL_Delay(delayTime - engineLoop->GameState->delta);
        } 

        
        //Intergrate into entity types
        frameCount++;
        frameTime += engineLoop->GameState->delta;
        if (frameTime >= 1.0f)
        {
            frameRate = frameCount / frameTime;
            frameCount = 0;
            frameTime = 0.0f;
            /*
            Engine_RenderObject* renderObject = ObjectManager_Get(engineLoop->RenderState->RenderManager, 2)->Data;
            char buffer[32];
            sprintf(buffer, "FPS_Counter: %f", frameRate);
            strcpy(renderObject->RenderData.TextData.Text, buffer);
            */
        }
        
        

    }
};