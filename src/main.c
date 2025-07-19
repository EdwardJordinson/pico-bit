#include <Engine/Engine_Initialise.h>
#include <Engine/Engine_Window.h>
#include <Engine/Engine_Shutdown.h>
#include <Engine/Engine_ControlLoop.h>
#include <stdio.h>


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