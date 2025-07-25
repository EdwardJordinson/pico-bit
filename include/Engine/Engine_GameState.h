#ifndef Engine_GameState_H
#define Engine_GameState_H

#include <Engine/Engine_EntityManager.h>

//Forward declares
union SDL_Event;
//

typedef struct Engine_GameState
{
    Engine_EntityManager* EntityManager;

} Engine_GameState;


void GameState_Update(Engine_GameState* gamestate, union SDL_Event* event);

void Update_HandleInput(Engine_GameState* gamestate, union SDL_Event* event);

#endif //Engine_GameState_H