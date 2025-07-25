#include <Engine/Engine_Initialise.h>
#include <Engine/Engine_Globals.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include <stdio.h>
#include <stdlib.h>


void Initialise_Engine(Engine_Globals** engineGlobals)
{
    *engineGlobals = malloc(sizeof(Engine_Globals));

    (*engineGlobals)->Window = malloc(sizeof(Engine_Window));
    
    (*engineGlobals)->MainLoop = malloc(sizeof(Engine_MainLoop));
    (*engineGlobals)->MainLoop->EventHandler = malloc(sizeof(Engine_EventHandler));
    (*engineGlobals)->MainLoop->EventHandler->SDLEvent = malloc(sizeof(SDL_Event));

    (*engineGlobals)->MainLoop->GameState = malloc(sizeof(Engine_GameState));
    (*engineGlobals)->MainLoop->GameState->EntityManager = malloc(sizeof(Engine_EntityManager));
    (*engineGlobals)->MainLoop->RenderState = malloc(sizeof(Engine_RenderState));
    
};

void Initialise_Window(Engine_Window** engineWindow)
{
    printf("Window Initialise...");

    if(SDL_Init(SDL_INIT_VIDEO) != true) printf("SDL could not initialise. SDL_Error: %s\n", SDL_GetError());

    (*engineWindow)->width = 640;
    (*engineWindow)->height = 480;

    (*engineWindow)->SDLWindow = SDL_CreateWindow( 
        "PICO-BIT Engine Window", 
        (*engineWindow)->width, 
        (*engineWindow)->height, 
        SDL_WINDOW_OPENGL);

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

void Initialise_Event(Engine_EventHandler** eventHandler)
{
    (*eventHandler)->mouseVector = Vector2_Initialise(0,0);
    
};

void Initialise_GameState(Engine_GameState** gameState)
{
    EntityManager_Initialise((*gameState)->EntityManager);
    int id = EntityManager_Allocate((*gameState)->EntityManager);
    //Engine->Window->width/4, Engine->Window->height/4
};

void Initialise_RenderState(Engine_RenderState** rendererState)
{
    (*rendererState)->RectsLoaded[0] = malloc(sizeof(SDL_FRect));
    (*rendererState)->RectsLoaded[0]->h = 100;
    (*rendererState)->RectsLoaded[0]->w = 100;
    (*rendererState)->RectsLoaded[0]->x = 0;
    (*rendererState)->RectsLoaded[0]->y = 0;

};

void Initialise_MainLoop(Engine_MainLoop** engineLoop)
{
    printf("Control Loop Initialise...");

    //engineLoop = malloc(sizeof(Engine_Loop));

    (*engineLoop)->running = false;
    (*engineLoop)->delta = 0.00f;

    printf("done.\n");
};