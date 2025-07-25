#include <Engine/Engine_Globals.h>
#include <Engine/Engine_Initialise.h>
#include <Engine/Engine_Shutdown.h>
#include <stdio.h>

//NOTES:
//Multi threading may be needed for Update and Draw

//Cleanup init scripts, remove the need to have the global script
//Remove uneeded includes
//Look at other cleanup options

//Cleanup movement for entities, fix segmentation error on left click

//Create Event handling system, tracking mouse movement


Engine_Globals* Engine;
Vector2 mousePos = {0.0, 0.0};

int main(void)
{
    printf("Engine Start.\n");
    
    Initialise_Engine(&Engine);
    Initialise_Window(&Engine->Window);
    //Initialise_Event(&Engine->MainLoop->SDLEvent);
    Initialise_GameState(&Engine->MainLoop->GameState);
    Initialise_RenderState(&Engine->MainLoop->RenderState);
    Initialise_MainLoop(&Engine->MainLoop);

    Engine->MainLoop->RenderState->SDLRenderer = Engine->Window->SDLRenderer;

    MainLoop_Run(&Engine->MainLoop);

    Engine_Shutdown();

    printf("Engine Shutdown.\n");

    return 0;
}