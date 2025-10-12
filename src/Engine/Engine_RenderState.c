#include <Engine/Engine_RenderState.h>
#include <Engine/Engine_RenderObject.h>
#include <Engine/Engine_Window.h>
#include <Engine/Engine_GameState.h>
#include <Engine/Engine_EntityObject.h>
#include <Engine/Engine_Object.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include <stdio.h>


//Handles Draw calls to the window


//Incomplete, object implemenation need work


void RenderState_Initialise(Engine_RenderState* renderState)
{
    //Needs to be intergrated into the efd loader
    renderState->font = TTF_OpenFont("assets/Font_OpenSans/OpenSans-Regular.ttf", 64);
};

void RenderState_Draw(Engine_RenderState* rendererState, Engine_GameState* gameState)
{
    SDL_SetRenderDrawColor(rendererState->EngineWindow->SDLRenderer, 0x80, 0x80, 0x80, 0x80);
    SDL_RenderClear(rendererState->EngineWindow->SDLRenderer);
    RenderState_DrawText(rendererState->EngineWindow->SDLRenderer, rendererState->font, rendererState->textTexture, ObjectManager_Get(rendererState->RenderManager, 2)->Data);
    RenderState_DrawObjects(rendererState, gameState->EntityManager);
    SDL_RenderPresent(rendererState->EngineWindow->SDLRenderer);
};

void RenderState_DrawObjects(Engine_RenderState* renderState, Engine_ObjectManager* entityManager)
{
    for (int i = 0; i < entityManager->ActiveCount; i++)
    {   
        Engine_EntityObject* entityObject = ObjectManager_Get(entityManager, i)->Data;
        void* tempData = EntityObject_GetData(entityObject);
        Engine_RenderObject* renderObject;
        switch (entityObject->EntityType)
        {
        case 1:
            Engine_GameEntity* gameData = tempData;
            renderObject = ObjectManager_Get(renderState->RenderManager, gameData->RenderID)->Data;
            RenderState_DrawGame(renderState, tempData, renderObject);
            break;
        case 2:
            Engine_DisplayEntity* displayData = tempData;
            renderObject = ObjectManager_Get(renderState->RenderManager, displayData->RenderID)->Data;
            RenderState_DrawDisplay(renderState, tempData, renderObject);
            break;
        default:
            break;
        }
    }
};

void RenderState_DrawGame(Engine_RenderState* renderState, Engine_GameEntity* gameEntity, Engine_RenderObject* renderObject)
{
    SDL_SetRenderDrawColor(renderState->EngineWindow->SDLRenderer, renderObject->Red, renderObject->Green, renderObject->Blue, renderObject->Alpha);
    Vector2 screenPos = RenderState_WorldToScreen(renderState->EngineWindow, gameEntity->PhysicsBody.Transform2D.Position);
    if (gameEntity->PhysicsBody.CollisionShape.CollisionType == 0)
    {
        Engine_AABB* tempBox = gameEntity->PhysicsBody.CollisionShape.GetData(&gameEntity->PhysicsBody.CollisionShape);
        Engine_AABB drawBox = (Engine_AABB){Vector2_AddVector(tempBox->maxVector, screenPos), Vector2_AddVector(tempBox->minVector, screenPos)};
        RenderState_DrawAABB(renderState->EngineWindow->SDLRenderer, drawBox);
    }
    else if (gameEntity->PhysicsBody.CollisionShape.CollisionType == 1)
    {
        Engine_OBB* tempBox = gameEntity->PhysicsBody.CollisionShape.GetData(&gameEntity->PhysicsBody.CollisionShape);
        RenderState_DrawOBB(renderState->EngineWindow->SDLRenderer, *tempBox, screenPos);
    }
};

void RenderState_DrawDisplay(Engine_RenderState* renderState, Engine_DisplayEntity* displayEntity, Engine_RenderObject* renderObject)
{
    
};

void RenderState_DrawLine(SDL_Renderer* renderer, Vector2 vector1, Vector2 vector2)
{
    SDL_RenderLine(renderer, vector1.x, vector1.y, vector2.x, vector2.y);
};

void RenderState_DrawAABB(SDL_Renderer* renderer, Engine_AABB drawBox)
{
    float width = AABB_GetWidth(&drawBox) + 1;
    float height = AABB_GetHeight(&drawBox) + 1;

    RenderState_DrawLine(renderer, drawBox.minVector, Vector2_AddXY(drawBox.minVector, width, 0.0f));
    RenderState_DrawLine(renderer, Vector2_AddXY(drawBox.minVector, 0.0f, 1.0f), Vector2_AddXY(drawBox.minVector, 0.0f, height-1.0f));
    RenderState_DrawLine(renderer, drawBox.maxVector, Vector2_SubtractXY(drawBox.maxVector, width, 0.0));
    RenderState_DrawLine(renderer, Vector2_SubtractXY(drawBox.maxVector, 0.0f, 1.0f), Vector2_SubtractXY(drawBox.maxVector, 0.0f, height-1.0f));
};

void RenderState_DrawOBB(SDL_Renderer* renderer, Engine_OBB drawBox, Vector2 position)
{
    float width = drawBox.sizeVector.x + 1;
    float height = drawBox.sizeVector.y + 1;
    /*
    RenderState_DrawLine(renderer, (Vector2){position.x - width, position.y - height}, Vector2_AddXY(drawBox.minVector, width, 0.0f));
    RenderState_DrawLine(renderer, Vector2_AddXY(drawBox.minVector, 0.0f, 1.0f), Vector2_AddXY(drawBox.minVector, 0.0f, height-1.0f));
    RenderState_DrawLine(renderer, drawBox.maxVector, Vector2_SubtractXY(drawBox.maxVector, width, 0.0));
    RenderState_DrawLine(renderer, Vector2_SubtractXY(drawBox.maxVector, 0.0f, 1.0f), Vector2_SubtractXY(drawBox.maxVector, 0.0f, height-1.0f));
    */
};

void RenderState_DrawText(SDL_Renderer* renderer, TTF_Font* font, SDL_Texture* textTexture, Engine_RenderObject* renderObject) // Testing functionality, needs change
{
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, renderObject->RenderData.TextData.Text, 32, (SDL_Color){0x00, 0x00, 0x00, 0x00}); 
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_DestroySurface(textSurface);

    SDL_FRect tempFRect = {
        .h = renderObject->RenderData.TextData.Height, 
        .w = renderObject->RenderData.TextData.Width, 
        .x = renderObject->PositionX,
        .y = renderObject->PositionY
    };

    SDL_RenderTexture(renderer, textTexture, NULL, &tempFRect);
    SDL_DestroyTexture(textTexture);
};

Vector2 RenderState_WorldToScreen(Engine_Window* window, Vector2 position)
{
    position.y = -position.y;
    float half_screen_width = window->width/2.0;
    float half_screen_height = window->height/2.0;

    position.x += half_screen_width;
    position.y += half_screen_height;
    return position;
};