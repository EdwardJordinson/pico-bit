#include <Engine/Engine_Initialise.h>
#include <Engine/Engine_Globals.h>
#include <SDL3/SDL_init.h>
#include <stdio.h>
#include <stdlib.h>


void InitialiseWindow(int windowWidth, int windowHeight)
{
    printf("Window Initialise...");

    if(SDL_Init(SDL_INIT_VIDEO) != true)
    {
        printf("SDL could not initialise. SDL_Error: %s\n", SDL_GetError());
    }

    EngineWindow = malloc(sizeof(Engine_Window));
    EngineWindow->width = windowWidth;
    EngineWindow->height = windowHeight;

    EngineWindow->window = SDL_CreateWindow( 
        "PICO-BIT Engine Window", 
        EngineWindow->width, 
        EngineWindow->height, 
        SDL_WINDOW_OPENGL
        );

    if(EngineWindow->window == NULL)
    {
        printf("Window could not be created. SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        EngineWindow->renderer = SDL_CreateRenderer(EngineWindow->window, NULL);
    }

    printf("done.\n");
};

void InitialiseLoop()
{
    printf("Control Loop Initialise...");

    EngineLoop = malloc(sizeof(Engine_Loop));

    EngineLoop->running = false;
    EngineLoop->delta = 0.0;

    printf("done.\n");
};