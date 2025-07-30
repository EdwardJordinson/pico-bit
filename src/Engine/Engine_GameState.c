#include <Engine/Engine_GameState.h>
#include <Engine/Engine_EventHandler.h>
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
    
    if (AABB_IntersectionAABB(entityManager->entities[0].BoundingBox, entityManager->entities[1].BoundingBox))
    {
        printf("Touching\n");
    }
};