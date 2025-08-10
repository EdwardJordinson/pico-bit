#include <Engine/Engine_Window.h>
#include <Engine/Engine_Coordinates.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include <stdio.h>


void Window_Initialise(Engine_Window* engineWindow)
{
    printf("Window Initialise...");

    engineWindow->width = 640; //320
    engineWindow->height = 480; //240

    engineWindow->SDLWindow = SDL_CreateWindow( 
        "PICO-BIT Engine Window", 
        engineWindow->width, 
        engineWindow->height, 
        SDL_WINDOW_OPENGL);

    if(engineWindow->SDLWindow == NULL)
    {
        printf("Window could not be created. SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        engineWindow->SDLRenderer = SDL_CreateRenderer(engineWindow->SDLWindow, NULL);
    }

    printf("done.\n");
};


