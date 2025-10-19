#include <Engine/Engine_Initialise.h>
#include <Engine/Engine_Globals.h>
#include <Engine/Engine_MainLoop.h>
#include <Engine/Engine_EventProcess.h>
#include <Engine/Engine_GameState.h>
#include <Engine/Engine_Object.h>
#include <Engine/Engine_EntityObject.h>
#include <Engine/Engine_RenderState.h>
#include <Engine/Engine_RenderObject.h>
#include <Engine/Engine_Window.h>
#include <Engine/Engine_EFD.h>
#include <SDL3/SDL_init.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

// Redundant, need to move the initcode there own files

void Initialise_EngineMemory(Engine_Main **engine)
{
    (*engine) = malloc(sizeof(Engine_Main));

    (*engine)->MainLoop = malloc(sizeof(Engine_MainLoop));

    (*engine)->MainLoop->EventProcess = malloc(sizeof(Engine_EventProcess));
    (*engine)->MainLoop->EventProcess->SDLEvent = malloc(sizeof(SDL_Event));

    (*engine)->MainLoop->GameState = malloc(sizeof(Engine_GameState));
    (*engine)->MainLoop->GameState->EntityManager = malloc(sizeof(Engine_ObjectManager));

    (*engine)->MainLoop->RenderState = malloc(sizeof(Engine_RenderState));
    (*engine)->MainLoop->RenderState->textTexture = malloc(sizeof(SDL_Texture));
    (*engine)->MainLoop->RenderState->EngineWindow = malloc(sizeof(Engine_Window));
    (*engine)->MainLoop->RenderState->RenderManager = malloc(sizeof(Engine_ObjectManager));
};

void Initialise_SDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) != true) printf("SDL could not initialise. SDL_Error: %s\n", SDL_GetError());
    if (TTF_Init() != true) printf("SDL could not initialise. SDL_Error: %s\n", SDL_GetError());

};

void Initialise_Systems(Engine_Main *engine)
{
    MainLoop_Intitialise(engine->MainLoop);

    EventProcess_Initialise(engine->MainLoop->EventProcess);

    GameState_Initialise(engine->MainLoop->GameState);
    ObjectManager_Initialise(engine->MainLoop->GameState->EntityManager, sizeof(Engine_EntityObject), 8, EntityObject_SetDefault);

    Window_Initialise(engine->MainLoop->RenderState->EngineWindow);
    RenderState_Initialise(engine->MainLoop->RenderState); //Brevity: This should be called before Window init
    ObjectManager_Initialise(engine->MainLoop->RenderState->RenderManager, sizeof(Engine_RenderObject), 8, RenderObject_SetDefault);
};

EFD_File* Initialise_ReadEFD()
{
    EFD_File* configFile = EFD_LoadFile("bin/demo_scene.efd");
    // char* data = (char*)EFD_ReadDump(configFile, configFile->Dumps);

    return configFile;
};

//Requires rework, needs dedicated libarary for parsing. Considering cross-compilation with GNU-Prolog
void Initialise_EFDConfigure(Engine_Main* engine, EFD_File* data)
{
    Engine_ObjectManager* entityManager = engine->MainLoop->GameState->EntityManager;
    Engine_ObjectManager* renderManager = engine->MainLoop->RenderState->RenderManager;

    char* dataString = (char*)EFD_ReadDump(data, data->Dumps);
    char* line = strtok(dataString, "\r\n");
    char* savePointer;
    while ((line != NULL))
    {
        Engine_Object* newObject;

        if (strncmp(line, "Entity-", 7) == 0)
        {
            EFD_ParseEntity(entityManager, line);
        }
        if (strncmp(line, "Render-", 7) == 0)
        {
            EFD_ParseRender(renderManager, line);
        }
            
        line = strtok(NULL, "\r\n");
    }

};

void Initialise_Game(Engine_Main *engine)
{
    MainLoop_Run(engine->MainLoop);

};