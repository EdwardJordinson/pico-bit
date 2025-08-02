#ifndef Engine_MainLoop_H
#define Engine_MainLoop_H

#include <stdbool.h>

//Forward declares
typedef struct Engine_EventProcess Engine_EventProcess;
typedef struct Engine_GameState Engine_GameState;
typedef struct Engine_RenderState Engine_RenderState;
//

typedef struct Engine_MainLoop
{
    bool running;
    float delta; //Have gamestate only track this

    Engine_EventProcess* EventProcess;
    Engine_GameState* GameState;
    Engine_RenderState* RenderState;

} Engine_MainLoop;


void MainLoop_Intitialise(Engine_MainLoop* mainLoop);

void MainLoop_Run(Engine_MainLoop* mainLoop);

void MainLoop_PrintConsole(bool* firstFrame, float frameRate, float frameDelta);


#endif //Engine_MainLoop_H