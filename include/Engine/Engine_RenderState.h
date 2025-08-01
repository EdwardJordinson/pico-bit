#ifndef Engine_RenderState_H
#define Engine_RenderState_H

#include <Engine/Engine_RenderManager.h>

//Forward declares
typedef struct SDL_Renderer SDL_Renderer;
typedef struct Engine_GameState Engine_GameState;
typedef struct Engine_EntityManager Engine_EntityManager;
typedef struct Vector2 Vector2;
//

typedef struct Engine_RenderState
{
    SDL_Renderer* SDLRenderer;
    Engine_RenderManager* RenderManager;

} Engine_RenderState;


void RenderState_Draw(Engine_RenderState* renderState, Engine_GameState* gameState);

void Draw_Entities(Engine_RenderState* renderState, Engine_EntityManager* entityManager);

Vector2 RenderState_WorldToScreen(Vector2 vector2);

#endif //Engine_RenderState_H