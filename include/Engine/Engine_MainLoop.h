#ifndef Engine_MainLoop_H
#define Engine_MainLoop_H

#include <Engine/Engine_GameState.h>
#include <Engine/Engine_RenderState.h>
#include <SDL3/SDL_events.h>
#include <stdint.h>
#include <stdbool.h>

//Forward declares
union SDL_Event;
//

typedef struct Engine_MainLoop
{
    bool running;
    float delta;

    SDL_Event* SDLEvent;
    Engine_GameState* GameState;
    Engine_RenderState* RenderState;

} Engine_MainLoop;


void MainLoop_Run(Engine_MainLoop** engineLoop);

void MainLoop_PrintConsole(bool* firstFrame, float frameRate, float frameDelta);

#endif //Engine_MainLoop_H