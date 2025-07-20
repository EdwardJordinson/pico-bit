#include <Engine/Engine_Globals.h>
#include <Engine/Engine_Initialise.h>
#include <Engine/Engine_Window.h>
#include <Engine/Engine_Shutdown.h>
#include <Engine/Engine_Loop.h>
#include <stdio.h>

//NOTES:
//Multi threading may be needed for Update and Draw


Engine_Window *EngineWindow;
Engine_Loop *EngineLoop;


int main(void)
{
    printf("Engine Start.\n");

    InitialiseWindow(640, 480);
    InitialiseLoop();

    RunLoop();

    Shutdown();

    printf("Engine Shutdown.\n");

    return 0;
}