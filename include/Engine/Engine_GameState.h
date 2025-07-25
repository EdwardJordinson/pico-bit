#ifndef Engine_GameState_H
#define Engine_GameState_H

#include <Engine/Engine_EntityManager.h>

//Forward declares
union SDL_Event;
typedef struct Engine_EventHandler Engine_EventHandler;
//

typedef struct Engine_GameState
{
    Engine_EntityManager* EntityManager;

} Engine_GameState;


void GameState_Update(Engine_GameState* gameState, Engine_EventHandler* eventHandler, float deltaTime);

#endif //Engine_GameState_H