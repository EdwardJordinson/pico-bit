#include <Engine/Engine_GameState.h>
#include <Engine/Engine_EventHandler.h>
#include <Engine/Engine_Physics.h>
#include <stdio.h>


void GameState_Update(Engine_GameState* gameState, Engine_EventHandler* eventHandler, float deltaTime)
{
    GameState_EntityAllUpdate(gameState->EntityManager, eventHandler->mouseVector, deltaTime);

};

void GameState_EntityAllUpdate(Engine_EntityManager* entityManager, Vector2 mousePosition, float deltaTime)
{
    for (int i = 0; i < entityManager->activeCount; i++)
    {   
        Engine_Entity* tempEntity = EntityManager_Get(entityManager, i);
        //Entity_SetVelocity(tempEntity, mousePosition);
        Entity_UpdateRigid(tempEntity, deltaTime); 
    }

    Engine_Manifold collisionData = Entity_CollisionNormal(&entityManager->entities[0], &entityManager->entities[1]);
    if (collisionData.Hit == true)
    {
        //printf("Touching\n");
        Entity_CollisionResolve(&entityManager->entities[0], &entityManager->entities[1], &collisionData);
    }
};