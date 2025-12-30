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
    switch (gameEntity->PhysicsBody.CollisionShape.CollisionType)
    {
    case 0:
        Engine_AABB* tempAABB = gameEntity->PhysicsBody.CollisionShape.GetData(&gameEntity->PhysicsBody.CollisionShape);
        Engine_AABB drawAABB = (Engine_AABB){Vector2_AddVector(screenPos, tempAABB->maxVector), Vector2_AddVector(screenPos, tempAABB->minVector)};
        RenderState_DrawAABB(renderState->EngineWindow->SDLRenderer, drawAABB);
        break;
    case 1:
        Engine_OBB* tempOBB = gameEntity->PhysicsBody.CollisionShape.GetData(&gameEntity->PhysicsBody.CollisionShape);
        RenderState_DrawOBB(renderState, *tempOBB, gameEntity->PhysicsBody.Transform2D);
        break;
    case 2:
        Engine_Circle* drawCircle = gameEntity->PhysicsBody.CollisionShape.GetData(&gameEntity->PhysicsBody.CollisionShape);
        RenderState_DrawCircle(renderState->EngineWindow->SDLRenderer, drawCircle->radius, screenPos);
        break;
    case 3:
        
        break;
    default:
        break;
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
    float width = AABB_GetWidth(&drawBox);
    float height = AABB_GetHeight(&drawBox);

    RenderState_DrawLine(renderer, drawBox.minVector, (Vector2){drawBox.minVector.x + width, drawBox.minVector.y});
    RenderState_DrawLine(renderer, drawBox.minVector, (Vector2){drawBox.minVector.x, drawBox.minVector.y + height});
    RenderState_DrawLine(renderer, drawBox.maxVector, (Vector2){drawBox.maxVector.x - width, drawBox.maxVector.y});
    RenderState_DrawLine(renderer, drawBox.maxVector, (Vector2){drawBox.maxVector.x, drawBox.maxVector.y - height});
};

// Draw Rotated Square Shapes
void RenderState_DrawOBB(Engine_RenderState* renderState, Engine_OBB drawBox, Engine_Matrix3x2 transform)
{

    Vector2 localCorners[4] = {
        { -drawBox.sizeVector.x, drawBox.sizeVector.y },
        {  drawBox.sizeVector.x, drawBox.sizeVector.y },
        {  drawBox.sizeVector.x,  -drawBox.sizeVector.y },
        { -drawBox.sizeVector.x,  -drawBox.sizeVector.y }};

    Vector2 worldCorners[4];
    for (int i = 0; i < 4; i++)
    {
        worldCorners[i] = Vector2_MultiplyMatrix3x2(transform, localCorners[i]);
    }

    RenderState_DrawLine(renderState->EngineWindow->SDLRenderer,
        RenderState_WorldToScreen(renderState->EngineWindow, worldCorners[0]), 
        RenderState_WorldToScreen(renderState->EngineWindow, worldCorners[1]));
    RenderState_DrawLine(renderState->EngineWindow->SDLRenderer,
        RenderState_WorldToScreen(renderState->EngineWindow, worldCorners[1]), 
        RenderState_WorldToScreen(renderState->EngineWindow, worldCorners[2]));
    RenderState_DrawLine(renderState->EngineWindow->SDLRenderer,
        RenderState_WorldToScreen(renderState->EngineWindow, worldCorners[2]), 
        RenderState_WorldToScreen(renderState->EngineWindow, worldCorners[3]));
    RenderState_DrawLine(renderState->EngineWindow->SDLRenderer,
        RenderState_WorldToScreen(renderState->EngineWindow, worldCorners[3]), 
        RenderState_WorldToScreen(renderState->EngineWindow, worldCorners[0]));
};

void RenderState_DrawCircle(SDL_Renderer* renderer, int radius, Vector2 position)
{
    
    int x = radius-1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);
    SDL_FPoint points[8];

    while (x >= y)
    {
        points[0] = (SDL_FPoint){position.x + x, position.y + y};
        points[1] = (SDL_FPoint){position.x + y, position.y + x};
        points[2] = (SDL_FPoint){position.x - y, position.y + x};
        points[3] = (SDL_FPoint){position.x - x, position.y + y};
        points[4] = (SDL_FPoint){position.x - x, position.y - y};
        points[5] = (SDL_FPoint){position.x - y, position.y - x};
        points[6] = (SDL_FPoint){position.x + y, position.y - x};
        points[7] = (SDL_FPoint){position.x + x, position.y - y};

        if (err <= 0)
        {
            y++;
            err += dy;
            dy += 2;
        }
        
        if (err > 0)
        {
            x--;
            dx += 2;
            err += dx - (radius << 1);
        }
        SDL_RenderPoints(renderer, points, 8);
    }
};

void RenderState_DrawText(SDL_Renderer* renderer, TTF_Font* font, SDL_Texture* textTexture, Engine_RenderObject* renderObject) // Testing functionality, needs change
{
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, renderObject->Data.TextRender.Text, 32, (SDL_Color){0x00, 0x00, 0x00, 0x00}); 
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_DestroySurface(textSurface);

    SDL_FRect tempFRect = {
        .h = renderObject->Data.TextRender.Height, 
        .w = renderObject->Data.TextRender.Width, 
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