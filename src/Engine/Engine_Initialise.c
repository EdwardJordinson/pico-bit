#include <Engine/Engine_Initialise.h>
#include <Engine/Engine_Globals.h>
#include <SDL3/SDL_init.h>
#include <stdio.h>
#include <stdlib.h>


void InitialiseEngine(Engine_Globals** engineGlobals)
{
    *engineGlobals = malloc(sizeof(Engine_Globals));

    (*engineGlobals)->Window = malloc(sizeof(Engine_Window));
    
    (*engineGlobals)->Loop = malloc(sizeof(Engine_Loop));
    (*engineGlobals)->Loop->UpdateLoop = malloc(sizeof(Engine_Update));
    (*engineGlobals)->Loop->DrawLoop = malloc(sizeof(Engine_Draw));
    
};

void InitialiseWindow(Engine_Window** engineWindow)
{
    printf("Window Initialise...");

    if(SDL_Init(SDL_INIT_VIDEO) != true)
    {
        printf("SDL could not initialise. SDL_Error: %s\n", SDL_GetError());
    }

    //engineWindow = malloc(sizeof(Engine_Window));
    (*engineWindow)->width = 640;
    (*engineWindow)->height = 480;

    (*engineWindow)->SDLWindow = SDL_CreateWindow( 
        "PICO-BIT Engine Window", 
        (*engineWindow)->width, 
        (*engineWindow)->height, 
        SDL_WINDOW_OPENGL
        );

    if((*engineWindow)->SDLWindow == NULL)
    {
        printf("Window could not be created. SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        (*engineWindow)->SDLRenderer = SDL_CreateRenderer((*engineWindow)->SDLWindow, NULL);
    }

    printf("done.\n");
};

void InitialiseLoop(Engine_Loop** engineLoop)
{
    printf("Control Loop Initialise...");

    //engineLoop = malloc(sizeof(Engine_Loop));

    (*engineLoop)->running = false;
    (*engineLoop)->delta = 0.0;

    printf("done.\n");
};