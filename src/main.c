#include <Engine/Engine_Globals.h>
#include <Engine/Engine_Initialise.h>
#include <Engine/Engine_Shutdown.h>
#include <stdio.h>


//NOTES:
//Multi threading may be needed for Update and Draw
//Read .efd(Engine Form Data) file for game creation.

Engine_Globals* Engine;
Engine_Window* EngineWindow;
BasisVector2 BASISVECTOR2;

int main(void)
{
    printf("Engine Start.\n");
    
    Initialise_EngineMemory(&Engine);
    Initialise_Window(&Engine->Window);
    Initialise_EventHandler(&Engine->MainLoop->EventHandler);
    Initialise_GameState(&Engine->MainLoop->GameState);
    Initialise_RenderState(&Engine->MainLoop->RenderState);
    EngineWindow = Engine->Window;
    Engine->MainLoop->RenderState->SDLRenderer = Engine->Window->SDLRenderer;
    Initialise_MainLoop(&Engine->MainLoop);

    MainLoop_Run(&Engine->MainLoop);

    Engine_Shutdown();

    printf("Engine Shutdown.\n");

    return 0;
}