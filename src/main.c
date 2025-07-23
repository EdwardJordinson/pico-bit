#include <Engine/Engine_Globals.h>
#include <Engine/Engine_Initialise.h>
#include <Engine/Engine_Window.h>
#include <Engine/Engine_Shutdown.h>
#include <Engine/Engine_Loop.h>
#include <stdlib.h>
#include <stdio.h>

//NOTES:
//Multi threading may be needed for Update and Draw

Engine_Globals* Engine;

int main(void)
{
    printf("Engine Start.\n");

    InitialiseEngine(&Engine);
    InitialiseEntityManager(Engine->Loop->GameState->EntityManager);
    InitialiseWindow(&Engine->Window);
    //InitialiseEvent(&Engine->Loop->SDLEvent);
    //InitialiseGameState(&Engine->Loop->GameState);
    InitialiseRenderer(&Engine->Loop->Renderer);
    InitialiseLoop(&Engine->Loop);

    RunLoop(&Engine->Loop);

    Shutdown();

    printf("Engine Shutdown.\n");

    return 0;
}