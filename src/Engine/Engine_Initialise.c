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
    (*engineGlobals)->Loop->SDLEvent = malloc(sizeof(SDL_Event));
    (*engineGlobals)->Loop->GameState = malloc(sizeof(Engine_GameState));
    (*engineGlobals)->Loop->GameState->EntityManager = malloc(sizeof(Engine_EntityManager));
    (*engineGlobals)->Loop->Renderer = malloc(sizeof(Engine_Renderer));
    
};

void InitialiseEntityManager(Engine_EntityManager* manager)
{
    manager->freeCount = MAX_ENTITY_SIZE;
    manager->activeCount = 0;

    for (int i = 0; i < MAX_ENTITY_SIZE; ++i)
    {
        manager->freeList[i] = MAX_ENTITY_SIZE - 1 - i;
        manager->active[i] = false;
        
    }
};

void InitialiseWindow(Engine_Window** engineWindow)
{
    printf("Window Initialise...");

    if(SDL_Init(SDL_INIT_VIDEO) != true)
    {
        printf("SDL could not initialise. SDL_Error: %s\n", SDL_GetError());
    }

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

void InitialiseEvent(SDL_Event** event)
{

};

void InitialiseGameState(Engine_GameState** gamestate)
{
    
};

void InitialiseRenderer(Engine_Renderer** renderer)
{
    (*renderer)->RectsLoaded[0] = malloc(sizeof(SDL_FRect));
    (*renderer)->RectsLoaded[0]->h = Engine->Window->height/4;
    (*renderer)->RectsLoaded[0]->w = Engine->Window->width/4;
    (*renderer)->RectsLoaded[0]->x = 0;
    (*renderer)->RectsLoaded[0]->y = 0;

};

void InitialiseLoop(Engine_Loop** engineLoop)
{
    printf("Control Loop Initialise...");

    //engineLoop = malloc(sizeof(Engine_Loop));

    (*engineLoop)->running = false;
    (*engineLoop)->delta = 0.0;

    printf("done.\n");
};