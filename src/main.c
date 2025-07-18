#include <Engine/Engine_Initialise.h>
#include <Engine/Engine_Window.h>
#include <SDL3/SDL.h>
#include <stdio.h>


int main(int argc, char *argv[])
{
    printf("Engine Start.\n");

    Engine_Window *engineWindow;

    if(SDL_Init(SDL_INIT_VIDEO) != true)
    {
        printf("SDL could not initialise. SDL_Error: %s\n", SDL_GetError());
    }
    
    engineWindow = InitialiseWindow(640, 480);
    
    if(engineWindow->window == NULL)
    {
        printf("Window could not be created. SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        //Get window surface
        engineWindow->surface = SDL_GetWindowSurface(engineWindow->window);

        //Fill the surface white
        SDL_FillSurfaceRect(engineWindow->surface, NULL, SDL_MapRGB(SDL_GetPixelFormatDetails(engineWindow->surface->format), SDL_GetSurfacePalette(engineWindow->surface), 0xFF, 0xFF, 0xFF));
        
        //Update the surface
        SDL_UpdateWindowSurface(engineWindow->window);

        //Hack to get window to stay up
        SDL_Event e; bool quit = false; while( quit == false ){ while(SDL_PollEvent( &e ) ){ if( e.type == SDL_EVENT_QUIT ) quit = true; } }
    }

    ShutdownWindow(engineWindow);
    
    SDL_Quit();

    return 0;
}