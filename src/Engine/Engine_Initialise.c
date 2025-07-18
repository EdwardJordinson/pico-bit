#include <Engine/Engine_Initialise.h>
#include <Engine/Engine_Window.h>
#include <SDL3/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>


Engine_Window *InitialiseWindow(int windowWidth, int windowHeight)
{
    printf("Window Initialise...");

    Engine_Window *engineWindow = malloc(sizeof(Engine_Window));
    

        //Create window
        engineWindow->window = SDL_CreateWindow( 
            "PICO-BIT Engine Window", 
            windowWidth, 
            windowHeight, 
            SDL_WINDOW_OPENGL
        );
    printf("done.\n");
    
    return engineWindow;
};

void ShutdownWindow(Engine_Window *engineWindow)
{
    SDL_DestroyWindow(engineWindow->window);
    
};