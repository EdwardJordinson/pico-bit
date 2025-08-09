#include <Engine/Engine_Initialise.h>
#include <Engine/Engine_Globals.h>
#include <Engine/Engine_MainLoop.h>
#include <Engine/Engine_EventProcess.h>
#include <Engine/Engine_GameState.h>
#include <Engine/Engine_Object.h>
#include <Engine/Engine_GameObject.h>
#include <Engine/Engine_RenderState.h>
#include <Engine/Engine_RenderObject.h>
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
    (*engine)->MainLoop->RenderState->RenderManager = malloc(sizeof(Engine_ObjectManager));
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
    ObjectManager_Initialise(engine->MainLoop->GameState->ObjectManager, sizeof(Engine_GameObject), 16, GameObject_SetDefault);

    RenderState_Initialise(engine->MainLoop->RenderState);
    Window_Initialise(engine->MainLoop->RenderState->EngineWindow);
    ObjectManager_Initialise(engine->MainLoop->RenderState->RenderManager, sizeof(Engine_RenderObject), 8, RenderObject_Configure);
};

EFD_File* Initialise_ReadEFD()
{
    EFD_File* configFile = EFD_LoadFile("bin/demo_scene.efd");
    // char* data = (char*)EFD_ReadDump(configFile, configFile->Dumps);

    return configFile;
};

void Initialise_EFDConfigure(Engine_Main* engine, EFD_File* data)
{
    Engine_ObjectManager* objectManager = engine->MainLoop->GameState->ObjectManager;
    Engine_ObjectManager* renderManager = engine->MainLoop->RenderState->RenderManager;

    char* dataString = (char*)EFD_ReadDump(data, data->Dumps);
    char* line = strtok(dataString, "\r\n");
    char* savePointer;
    while ((line != NULL))
    {
        Engine_Object* newObject;

        if (strncmp(line, "Game-", 5) == 0)
        {
            newObject = ObjectManager_Allocate(objectManager);
            Engine_GameObject* newGameObject = newObject->Data;

            char lineCopy[1024];
            strncpy(lineCopy, line, sizeof(lineCopy));
            lineCopy[sizeof(lineCopy) - 1] = '\0';

            char* token = strtok_r(lineCopy, ",", &savePointer);
            while (token)
            {
                if (strncmp(token + 5, "Position", 8) == 0)
                {
                    float tempX = 0.0; float tempY = 0.0;
                    sscanf(token + 8  + 5, "{%f|%f}", &tempX, &tempY);
                    GameObject_SetPositionXY(newGameObject, tempX, tempY);
                }
                else if (strncmp(token, "Velocity", 8) == 0)
                {
                    float tempX = 0.0; float tempY = 0.0;
                    sscanf(token + 8, "{%f|%f}", &tempX, &tempY);
                    Vector2_SetXY(&newGameObject->Velocity, tempX, tempY);
                }
                else if (strncmp(token, "RenderID", 8) == 0)
                {
                    int renderID = 0;
                    sscanf(token + 8, "{%d}", &renderID);
                    newGameObject->RenderID = renderID;
                }
                else if (strncmp(token, "Restitution", 11) == 0)
                {
                    float tempRestitution = 1.0;
                    sscanf(token + 11, "{%f}", &tempRestitution);
                    newGameObject->Restitution = tempRestitution;
                }
                else if (strncmp(token, "Mass", 4) == 0)
                {
                    float tempMass = 10.0;
                    sscanf(token + 4, "{%f}", &tempMass);
                    newGameObject->Mass = tempMass;
                }
                // else if (strncmp(token, "CollisionShape{AABB{", 21) == 0)
                //     sscanf(token + 21, "%f,%f,%f,%f}}", &obj.collider.xMin, &obj.collider.yMin, &obj.collider.xMax, &obj.collider.yMax);
                token = strtok_r(NULL, ",", &savePointer);
            }
        }
        
        if (strncmp(line, "Render-", 7) == 0)
        {
            newObject = ObjectManager_Allocate(renderManager);
            Engine_RenderObject* newRenderObject = newObject->Data;

            char lineCopy[1024];
            strncpy(lineCopy, line, sizeof(lineCopy));
            lineCopy[sizeof(lineCopy) - 1] = '\0';

            char* token = strtok_r(lineCopy, ",", &savePointer);
            while (token)
            {
                if (strncmp(token + 7, "Position", 8) == 0)
                {
                    float tempX = 0.0; float tempY = 0.0;
                    sscanf(token + 8  + 7, "{%f|%f}", &tempX, &tempY);
                    newRenderObject->PositionX = tempX;
                    newRenderObject->PositionY = tempY;
                }
                else if (strncmp(token, "Width", 5) == 0)
                {
                    float tempWidth = 0.0;
                    sscanf(token + 5, "{%f}", &tempWidth);
                    newRenderObject->Width = tempWidth;
                }
                else if (strncmp(token, "Height", 6) == 0)
                {
                    float tempHeight = 0.0;
                    sscanf(token + 6, "{%f}", &tempHeight);
                    newRenderObject->Height = tempHeight;
                }
                else if (strncmp(token, "Colour", 6) == 0)
                {
                    int tempRed = 1; int tempGreen = 1; int tempBlue = 1; int tempAlpha = 1;
                    sscanf(token + 6, "{%x|%x|%x|%x}", &tempRed, &tempGreen, &tempBlue, &tempAlpha);
                    RenderObject_SetColour(newRenderObject, tempRed, tempBlue, tempGreen, tempAlpha);
                }
                token = strtok_r(NULL, ",", &savePointer);
            }
        }

        line = strtok(NULL, "\r\n");
    }

};

void Initialise_Game(Engine_Main *engine)
{
    MainLoop_Run(engine->MainLoop);
};