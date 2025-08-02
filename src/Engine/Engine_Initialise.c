#include <Engine/Engine_Initialise.h>
#include <Engine/Engine_Globals.h>
#include <Engine/Engine_MainLoop.h>
#include <Engine/Engine_EventProcess.h>
#include <Engine/Engine_GameState.h>
#include <Engine/Engine_Object.h>
#include <Engine/Engine_RenderState.h>
#include <Engine/Engine_RenderManager.h>
#include <Engine/Engine_Window.h>
#include <SDL3/SDL_init.h>
#include <stdio.h>
#include <stdlib.h>

//Redundant, need to move the initcode there own files

void Initialise_EngineMemory(Engine_Main** engine)
{
    (*engine) = malloc(sizeof(Engine_Main));

    (*engine)->MainLoop = malloc(sizeof(Engine_MainLoop));

    (*engine)->MainLoop->EventProcess = malloc(sizeof(Engine_EventProcess));
    (*engine)->MainLoop->EventProcess->SDLEvent = malloc(sizeof(SDL_Event));

    (*engine)->MainLoop->GameState = malloc(sizeof(Engine_GameState));
    (*engine)->MainLoop->GameState->ObjectManager = malloc(sizeof(Engine_ObjectManager));

    (*engine)->MainLoop->RenderState = malloc(sizeof(Engine_RenderState));
    (*engine)->MainLoop->RenderState->EngineWindow = malloc(sizeof(Engine_Window));
    (*engine)->MainLoop->RenderState->RenderManager = malloc(sizeof(Engine_RenderManager));
    
};

void Initialise_SDL()
{
    if(SDL_Init(SDL_INIT_VIDEO) != true) printf("SDL could not initialise. SDL_Error: %s\n", SDL_GetError());
};

void Initialise_Systems(Engine_Main* engine)
{
    MainLoop_Intitialise(engine->MainLoop);

    EventProcess_Initialise(engine->MainLoop->EventProcess);

    GameState_Initialise(engine->MainLoop->GameState);
    ObjectManager_Initialise(engine->MainLoop->GameState->ObjectManager);

    RenderState_Initialise(engine->MainLoop->RenderState);
    Window_Initialise(engine->MainLoop->RenderState->EngineWindow);
    RenderManager_Initialise(engine->MainLoop->RenderState->RenderManager);

};

void Initialise_ReadEFD()
{

};

void Initialise_EFDConfigure(Engine_Main* engine)
{
    Engine_ObjectManager* objectManager = engine->MainLoop->GameState->ObjectManager;
    int objectID1 = ObjectManager_Allocate(objectManager);
    int objectID2 = ObjectManager_Allocate(objectManager);
    Engine_Object* object1 = ObjectManager_Get(objectManager, objectID1);
    Engine_Object* object2 = ObjectManager_Get(objectManager, objectID2);
    Object_Setup(object1, 0.0, 0.0);
    Object_Setup(object2, 0.0,200.0);
    object1->Mass = 100.0;
    object2->Velocity.y = -100.0;

    Engine_RenderManager* renderManger = engine->MainLoop->RenderState->RenderManager;
    RenderManager_Initialise(renderManger);
    RenderManager_Allocate(renderManger);

};

void Initialise_Game(Engine_Main* engine)
{
    MainLoop_Run(engine->MainLoop);

};

/*
void Initialise_GameState(Engine_GameState** gameState)
{
    
    EntityManager_Initialise((*gameState)->EntityManager);
    int entityID1 = EntityManager_Allocate((*gameState)->EntityManager);
    int entityID2 = EntityManager_Allocate((*gameState)->EntityManager);
    Engine_Entity* entity1 = EntityManager_Get((*gameState)->EntityManager, entityID1);
    Engine_Entity* entity2 = EntityManager_Get((*gameState)->EntityManager, entityID2);
    Entity_Setup(entity1, 0.0, 0.0);
    Entity_Setup(entity2, 0.0,200.0);
    entity1->Mass = 100.0;
    entity2->Velocity.y = -100.0;
    

};

void Initialise_RenderState(Engine_RenderState** rendererState)
{
    //RenderManager_Initialise((*rendererState)->RenderManager);
    //RenderManager_Allocate((*rendererState)->RenderManager);

};
*/
