#include <Engine/Engine_Globals.h>
#include <Engine/Engine_Initialise.h>
#include <Engine/Engine_Shutdown.h>
#include <stdio.h>


//NOTES:
//Multi threading may be needed for Update and Draw
//Read .efd(Engine Form Data) file for game creation.

Engine_Main* Engine;


int main(void)
{
    printf("Engine Start.\n");
    
    Initialise_EngineMemory(&Engine);
    Initialise_SDL();
    Initialise_Systems(Engine);
    Initialise_ReadEFD();
    Initialise_EFDConfigure(Engine);
    Initialise_Game(Engine);

    Engine_Shutdown();

    printf("Engine Shutdown.\n");

    return 0;
}