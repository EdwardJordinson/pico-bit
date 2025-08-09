#include <Engine/Engine_RenderState.h>
#include <Engine/Engine_RenderObject.h>
#include <Engine/Engine_Window.h>
#include <Engine/Engine_GameState.h>
#include <Engine/Engine_GameObject.h>
#include <Engine/Engine_Object.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>


//Handles Draw calls to the window


//Incomplete, object implemenation need work


void RenderState_Initialise(Engine_RenderState* renderState)
{

};

void RenderState_Draw(Engine_RenderState* rendererState, Engine_GameState* gameState)
{
    SDL_SetRenderDrawColor(rendererState->EngineWindow->SDLRenderer, 0x80, 0x80, 0x80, 0x80);
    SDL_RenderClear(rendererState->EngineWindow->SDLRenderer);
    RenderState_DrawObjects(rendererState, gameState->ObjectManager);
    SDL_RenderPresent(rendererState->EngineWindow->SDLRenderer);
};

// Need to draw lines of each object collision shape instead of a square
void RenderState_DrawObjects(Engine_RenderState* rendererState, Engine_ObjectManager* objectManager)
{
    for (int i = 0; i < objectManager->ActiveCount; i++)
    {   
        Engine_GameObject* gameObject = ObjectManager_Get(objectManager, i)->Data;
        Engine_RenderObject* renderObject = ObjectManager_Get(rendererState->RenderManager, gameObject->RenderID)->Data;

        SDL_SetRenderDrawColor(rendererState->EngineWindow->SDLRenderer, renderObject->Red, renderObject->Green, renderObject->Blue, renderObject->Alpha);
        Engine_AABB drawBox = AABB_GetPosition(&gameObject->CollisionShape, RenderState_WorldToScreen(rendererState->EngineWindow, gameObject->Transform2D.Position));
        RenderState_DrawAABB(rendererState->EngineWindow->SDLRenderer, drawBox);

    }
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

Vector2 RenderState_WorldToScreen(Engine_Window* window, Vector2 position)
{
    position.y = -position.y;
    float half_screen_width = window->width/2.0;
    float half_screen_height = window->height/2.0;

    position.x += half_screen_width;
    position.y += half_screen_height;
    return position;
};