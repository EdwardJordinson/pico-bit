#include <Engine/Engine_GameState.h>
#include <Engine/Engine_EventHandler.h>


void GameState_Update(Engine_GameState* gameState, Engine_EventHandler* eventHandler, float deltaTime)
{
    Entity_Event(&gameState->EntityManager->entities[0], eventHandler);
    Entity_SetVelocity(&gameState->EntityManager->entities[0], eventHandler->mouseVector);
    Entity_Update(&gameState->EntityManager->entities[0], deltaTime);

};
