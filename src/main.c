#include <Engine/Engine_Initialise.h>
#include <Engine/Engine_Window.h>
#include <Engine/Engine_Shutdown.h>
#include <Engine/Engine_ControlLoop.h>
#include <stdio.h>

//NOTES:
//Extern variables look handy for sharing important stuff like window and renderer || May need a global/constants header file later...
//Multi threading will be needed for Update and Draw

int main(void)
{
    printf("Engine Start.\n");

    Engine_Window *engineWindow = InitialiseWindow(640, 480);
    Engine_ControlLoop *engineControlLoop = InitialiseControlLoop(engineWindow);

    RunLoop(engineControlLoop);

    Shutdown(engineWindow);

    printf("Engine Shutdown.\n");

    return 0;
}