#include <Engine/Engine_Globals.h>
#include <Engine/Engine_Initialise.h>
#include <Engine/Engine_Shutdown.h>
#include <stdio.h>

//NOTES:
//Multi threading may be needed for Update and Draw

//Cleanup init scripts, remove the need to have the global script
//Look at other cleanup options

//Create Event handling system, tracking mouse movement


Engine_Globals* Engine;
Vector2 mousePos = {0.0, 0.0};
Vector2Type VECTOR2;

int main(void)
{
    printf("Engine Start.\n");
    
    Initialise_EngineMemory(&Engine);
    Initialise_Window(&Engine->Window);
    Initialise_EventHandler(&Engine->MainLoop->EventHandler);
    Initialise_GameState(&Engine->MainLoop->GameState);
    Initialise_RenderState(&Engine->MainLoop->RenderState);
    Engine->MainLoop->RenderState->SDLRenderer = Engine->Window->SDLRenderer;
    Initialise_MainLoop(&Engine->MainLoop);

    MainLoop_Run(&Engine->MainLoop);

    Engine_Shutdown();

    printf("Engine Shutdown.\n");

    return 0;
}