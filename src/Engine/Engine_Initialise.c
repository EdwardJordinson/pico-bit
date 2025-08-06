#include <Engine/Engine_Initialise.h>
#include <Engine/Engine_Globals.h>
#include <Engine/Engine_MainLoop.h>
#include <Engine/Engine_EventProcess.h>
#include <Engine/Engine_GameState.h>
#include <Engine/Engine_Object.h>
#include <Engine/Engine_RenderState.h>
#include <Engine/Engine_RenderManager.h>
#include <Engine/Engine_Window.h>
#include <Engine/Engine_EFD.h>
#include <SDL3/SDL_init.h>
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
    (*engine)->MainLoop->GameState->ObjectManager = malloc(sizeof(Engine_ObjectManager));

    (*engine)->MainLoop->RenderState = malloc(sizeof(Engine_RenderState));
    (*engine)->MainLoop->RenderState->EngineWindow = malloc(sizeof(Engine_Window));
    (*engine)->MainLoop->RenderState->RenderManager = malloc(sizeof(Engine_RenderManager));
};

void Initialise_SDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) != true)
        printf("SDL could not initialise. SDL_Error: %s\n", SDL_GetError());
};

void Initialise_Systems(Engine_Main *engine)
{
    MainLoop_Intitialise(engine->MainLoop);

    EventProcess_Initialise(engine->MainLoop->EventProcess);

    GameState_Initialise(engine->MainLoop->GameState);
    ObjectManager_Initialise(engine->MainLoop->GameState->ObjectManager);

    RenderState_Initialise(engine->MainLoop->RenderState);
    Window_Initialise(engine->MainLoop->RenderState->EngineWindow);
    RenderManager_Initialise(engine->MainLoop->RenderState->RenderManager);
};

EFD_File *Initialise_ReadEFD()
{
    EFD_File *configFile = EFD_LoadFile("bin/demo_scene.efd");
    // char* data = (char*)EFD_ReadDump(configFile, configFile->Dumps);

    return configFile;
};

void Initialise_EFDConfigure(Engine_Main *engine, EFD_File *data)
{
    Engine_ObjectManager *objectManager = engine->MainLoop->GameState->ObjectManager;
    Engine_RenderManager *renderManager = engine->MainLoop->RenderState->RenderManager;

    char *dataString = (char *)EFD_ReadDump(data, data->Dumps);
    char *line = strtok(dataString, "\r\n");
    char *savePointer;
    while ((line != NULL))
    {
        Engine_Object *newObject;
        if (strncmp(line, "Game-", 5) == 0)
        {
            newObject = ObjectManager_Get(objectManager, ObjectManager_Allocate(objectManager));

            char lineCopy[1024];
            strncpy(lineCopy, line, sizeof(lineCopy));
            lineCopy[sizeof(lineCopy) - 1] = '\0';

            char *token = strtok_r(lineCopy, ",", &savePointer);
            while (token)
            {
                if (strncmp(token + 5, "Position", 8) == 0)
                {
                    float tempX = 0.0;
                    float tempY = 0.0;
                    sscanf(token + 8  + 5, "{%f|%f}", &tempX, &tempY);
                    Object_SetPosition(newObject, tempX,tempY);
                }
                else if (strncmp(token, "Velocity", 8) == 0)
                {
                    float tempX = 0.0;
                    float tempY = 0.0;
                    sscanf(token + 8, "{%f|%f}", &tempX, &tempY);
                    newObject->Velocity.x = tempX;
                    newObject->Velocity.y = tempY;
                }
                else if (strncmp(token, "RenderID", 8) == 0)
                {
                    int renderID = 0;
                    sscanf(token + 8, "{%d}", &renderID);
                    newObject->renderID = renderID;
                }
                else if (strncmp(token, "Restitution", 11) == 0)
                {
                    float tempRestitution = 1.0;
                    sscanf(token + 11, "{%f}", &tempRestitution);
                    newObject->Restitution = tempRestitution;
                }
                else if (strncmp(token, "Mass", 4) == 0)
                {
                    float tempMass = 10.0;
                    sscanf(token + 4, "{%f}", &tempMass);
                    newObject->Mass = tempMass;
                }
                // else if (strncmp(token, "CollisionShape{AABB{", 21) == 0)
                //     sscanf(token + 21, "%f,%f,%f,%f}}", &obj.collider.xMin, &obj.collider.yMin, &obj.collider.xMax, &obj.collider.yMax);
                token = strtok_r(NULL, ",", &savePointer);
            }
        }
        
        SDL_FRect *newRect;
        if (strncmp(line, "Render-", 7) == 0)
        {
            newRect = RenderManager_Get(renderManager, RenderManager_Allocate(renderManager));

            char lineCopy[1024];
            strncpy(lineCopy, line, sizeof(lineCopy));
            lineCopy[sizeof(lineCopy) - 1] = '\0';

            char *token = strtok_r(lineCopy, ",", &savePointer);
            while (token)
            {
                if (strncmp(token + 7, "Position", 8) == 0)
                {
                    float tempX = 0.0;
                    float tempY = 0.0;
                    sscanf(token + 8  + 7, "{%f|%f}", &tempX, &tempY);
                    newRect->x = tempX;
                    newRect->y = tempY;
                }
                else if (strncmp(token, "Width", 5) == 0)
                {
                    float tempWidth = 0.0;
                    sscanf(token + 5, "{%f}", &tempWidth);
                    newRect->w = tempWidth;
                }
                else if (strncmp(token, "Height", 6) == 0)
                {
                    float tempHeight = 0.0;
                    sscanf(token + 6, "{%f}", &tempHeight);
                    newRect->h = tempHeight;
                }
                else if (strncmp(token, "Colour", 6) == 0)
                {
                    int tempRed = 1.0;
                    int tempGreen = 1.0;
                    int tempBlue = 1.0;
                    int tempAlpha = 1.0;
                    sscanf(token + 6, "{%d|%d|%d|%d}", &tempRed, &tempGreen, &tempBlue, &tempAlpha);
                    //newRect. = tempRestitution;
                }
                token = strtok_r(NULL, ",", &savePointer);
            }
        }

        line = strtok(NULL, "\r\n");
    }

    
    // int objectID1 = ObjectManager_Allocate(objectManager);
    // int objectID2 = ObjectManager_Allocate(objectManager);
    // Engine_Object* object1 = ObjectManager_Get(objectManager, objectID1);
    // Engine_Object* object2 = ObjectManager_Get(objectManager, objectID2);
    // Object_Setup(object1, 0.0, 0.0);
    // Object_Setup(object2, 0.0,200.0);
    // object1->Mass = 100.0;
    // object2->Velocity.y = -100.0;

    //Engine_RenderManager *renderManger = engine->MainLoop->RenderState->RenderManager;
    //RenderManager_Initialise(renderManger);
    //RenderManager_Allocate(renderManger);

};

void Initialise_Game(Engine_Main *engine)
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
