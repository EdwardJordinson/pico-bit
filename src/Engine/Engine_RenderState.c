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
    Draw_Entities(rendererState, gameState->ObjectManager);
    SDL_RenderPresent(rendererState->EngineWindow->SDLRenderer);
};

void Draw_Entities(Engine_RenderState* rendererState, Engine_ObjectManager* objectManager)
{
    for (int i = 0; i < objectManager->ActiveCount; i++)
    {   
        Engine_GameObject* gameObject = ObjectManager_Get(objectManager, i)->Data;
        Engine_RenderObject* renderObject = ObjectManager_Get(rendererState->RenderManager, gameObject->RenderID)->Data;
        SDL_FRect* tempFRect;
        Vector2 tempPosition = RenderState_WorldToScreen(rendererState->EngineWindow, gameObject->Transform2D.Position);
        tempFRect->x = tempPosition.x;
        tempFRect->y = tempPosition.y;
        tempFRect->w = renderObject->Width;
        tempFRect->h = renderObject->Height;

        SDL_SetRenderDrawColor(rendererState->EngineWindow->SDLRenderer, renderObject->Red, renderObject->Green, renderObject->Blue, renderObject->Alpha);
        SDL_RenderFillRect(rendererState->EngineWindow->SDLRenderer, tempFRect);
    }
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