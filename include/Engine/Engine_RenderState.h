#ifndef Engine_Draw_H
#define Engine_Draw_H

//Forward declares
typedef struct Engine_GameState Engine_GameState;
typedef struct SDL_FRect SDL_FRect;
typedef struct Engine_EntityManager Engine_EntityManager;
//

typedef struct Engine_RenderState
{
    SDL_FRect* RectsLoaded[2];

} Engine_RenderState;


void Draw_Call(Engine_RenderState* renderer, Engine_GameState* gamestate);

void Draw_Entities(Engine_RenderState* renderer, Engine_EntityManager* entityManager);

#endif //Engine_Draw_H