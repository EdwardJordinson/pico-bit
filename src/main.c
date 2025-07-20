#include <Engine/Engine_Globals.h>
#include <Engine/Engine_Initialise.h>
#include <Engine/Engine_Window.h>
#include <Engine/Engine_Shutdown.h>
#include <Engine/Engine_Loop.h>
#include <stdlib.h>
#include <stdio.h>

//NOTES:
//Multi threading may be needed for Update and Draw


Engine_Window* EngineWindow;
Engine_Loop* EngineLoop;
SDL_FRect* LoadedRects[2];
Engine_Entity* Entities[1];


int main(void)
{
    printf("Engine Start.\n");

    InitialiseWindow(640, 480);
    InitialiseLoop();


    LoadedRects[0] = malloc(sizeof(SDL_FRect));
    LoadedRects[0]->h = EngineWindow->height/4;
    LoadedRects[0]->w = EngineWindow->width/4;
    LoadedRects[0]->x = 0;
    LoadedRects[0]->y = 0;


    //Entities[0] = NULL;

    RunLoop();

    free(LoadedRects[0]);

    Shutdown();

    printf("Engine Shutdown.\n");

    return 0;
}