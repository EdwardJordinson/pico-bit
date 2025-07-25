#ifndef Engine_RenderState_H
#define Engine_RenderState_H

//Forward declares
typedef struct SDL_Renderer SDL_Renderer;
typedef struct Engine_GameState Engine_GameState;
typedef struct SDL_FRect SDL_FRect;
typedef struct Engine_EntityManager Engine_EntityManager;
//

typedef struct Engine_RenderState
{
    SDL_Renderer* SDLRenderer;
    SDL_FRect* RectsLoaded[2];

} Engine_RenderState;


void RenderState_Draw(Engine_RenderState* renderState, Engine_GameState* gameState);

void Draw_Entities(Engine_RenderState* renderState, Engine_EntityManager* entityManager);

#endif //Engine_RenderState_H