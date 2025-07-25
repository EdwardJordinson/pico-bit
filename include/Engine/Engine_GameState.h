#ifndef Engine_Update_H
#define Engine_Update_H

#include <Engine/Engine_EntityManager.h>

//Forward declares
union SDL_Event;
//

typedef struct Engine_GameState
{
    Engine_EntityManager* EntityManager;

} Engine_GameState;


void Update_Call(Engine_GameState* gamestate, union SDL_Event* event);

void Update_HandleInput(Engine_GameState* gamestate, union SDL_Event* event);

#endif //Engine_Update_H