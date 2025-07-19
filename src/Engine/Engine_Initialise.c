#include <Engine/Engine_Initialise.h>
#include <Engine/Engine_Window.h>
#include <Engine/Engine_ControlLoop.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_init.h>
#include <stdio.h>
#include <stdlib.h>


Engine_Window *InitialiseWindow(int windowWidth, int windowHeight)
{
    printf("Window Initialise...");

    if(SDL_Init(SDL_INIT_VIDEO) != true)
    {
        printf("SDL could not initialise. SDL_Error: %s\n", SDL_GetError());
    }

    Engine_Window *engineWindow = malloc(sizeof(Engine_Window));
    engineWindow->width = windowWidth;
    engineWindow->height = windowHeight;

    engineWindow->window = SDL_CreateWindow( 
        "PICO-BIT Engine Window", 
        engineWindow->width, 
        engineWindow->height, 
        SDL_WINDOW_OPENGL
        );

    if(engineWindow->window == NULL)
    {
        printf("Window could not be created. SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        engineWindow->surface = SDL_GetWindowSurface(engineWindow->window);
        SDL_FillSurfaceRect(engineWindow->surface, NULL, SDL_MapRGB(SDL_GetPixelFormatDetails(engineWindow->surface->format), SDL_GetSurfacePalette(engineWindow->surface), 0x00, 0x00, 0x00));
        SDL_UpdateWindowSurface(engineWindow->window);

        engineWindow->renderer = SDL_CreateRenderer(engineWindow->window, NULL);
        
        engineWindow->texture = SDL_CreateTextureFromSurface(engineWindow->renderer, engineWindow->surface);
        SDL_DestroySurface(engineWindow->surface);
    }

    printf("done.\n");

    return engineWindow;
};

Engine_ControlLoop *InitialiseControlLoop(Engine_Window *engineWindow)
{
    printf("Control Loop Initialise...");

    Engine_ControlLoop *engineControlLoop = malloc(sizeof(Engine_ControlLoop));

    engineControlLoop->running = false;
    engineControlLoop->delta = 0.0;
    engineControlLoop->window = engineWindow;

    printf("done.\n");

    return engineControlLoop;
};