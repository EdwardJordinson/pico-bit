#include <Engine/Engine_Globals.h>
#include <Engine/Engine_Initialise.h>
#include <Engine/Engine_Shutdown.h>
#include <Engine/Engine_EFD.h>
#include <stdio.h>
#include <stdbool.h>


//NOTES:
//Multi threading may be needed for Update and Draw
//Add friction, then AABB BST



Engine_Main* Engine;

bool makeEFD = false;


int main(int argc, char** argv)
{
    if (makeEFD == true)
    {
        
        return 0;
    }
    EFD_WriteFile(argc, argv);

    printf("Engine Start.\n");
    
    Initialise_EngineMemory(&Engine);
    Initialise_SDL();
    Initialise_Systems(Engine);
    EFD_File* data = Initialise_ReadEFD();
    Initialise_EFDConfigure(Engine, data);
    Initialise_Game(Engine);

    Engine_Shutdown();

    printf("Engine Shutdown.\n");

    return 0;
}