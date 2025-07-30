#include <Engine/Engine_Initialise.h>
#include <Engine/Engine_Globals.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include <stdio.h>
#include <stdlib.h>


void Initialise_EngineMemory(Engine_Globals** engineGlobals)
{
    *engineGlobals = malloc(sizeof(Engine_Globals));

    (*engineGlobals)->Window = malloc(sizeof(Engine_Window));
    
    (*engineGlobals)->MainLoop = malloc(sizeof(Engine_MainLoop));
    (*engineGlobals)->MainLoop->EventHandler = malloc(sizeof(Engine_EventHandler));
    (*engineGlobals)->MainLoop->EventHandler->SDLEvent = malloc(sizeof(SDL_Event));

    (*engineGlobals)->MainLoop->GameState = malloc(sizeof(Engine_GameState));
    (*engineGlobals)->MainLoop->GameState->EntityManager = malloc(sizeof(Engine_EntityManager));
    (*engineGlobals)->MainLoop->RenderState = malloc(sizeof(Engine_RenderState));
    (*engineGlobals)->MainLoop->RenderState->RenderManager = malloc(sizeof(Engine_RenderManager));
    
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

void Initialise_EventHandler(Engine_EventHandler** eventHandler)
{
    (*eventHandler)->mouseVector = Vector2_Initialise(0,0);
    
};

void Initialise_GameState(Engine_GameState** gameState)
{
    Vector2Type_Initialise(&VECTOR2);

    EntityManager_Initialise((*gameState)->EntityManager);
    int entityID1 = EntityManager_Allocate((*gameState)->EntityManager);
    int entityID2 = EntityManager_Allocate((*gameState)->EntityManager);
    Engine_Entity* entity1 = EntityManager_Get((*gameState)->EntityManager, entityID1);
    Engine_Entity* entity2 = EntityManager_Get((*gameState)->EntityManager, entityID2);
    Entity_Setup(entity1, 640/2,480/2);
    Entity_Setup(entity2, 640/2,480/4);
    entity2->Velocity.y = 100.0;

};

void Initialise_RenderState(Engine_RenderState** rendererState)
{
    RenderManager_Initialise((*rendererState)->RenderManager);
    RenderManager_Allocate((*rendererState)->RenderManager);

};

void Initialise_MainLoop(Engine_MainLoop** engineLoop)
{
    printf("Control Loop Initialise...");

    (*engineLoop)->running = false;
    (*engineLoop)->delta = 0.00f;

    printf("done.\n");
};