#include <Engine/Engine_GameState.h>
#include <Engine/Engine_Object.h>
#include <Engine/Engine_EventProcess.h>
#include <Engine/Engine_Physics.h>
#include <stdio.h>


void GameState_Initialise(Engine_GameState* gameState)
{
    gameState->delta = 0.0;

};

void GameState_Update(Engine_GameState* gameState, Engine_EventProcess* eventProcess)
{
    GameState_EntityAllUpdate(gameState->ObjectManager, gameState->delta);

};

void GameState_EntityAllUpdate(Engine_ObjectManager* objectManager, float deltaTime)
{
    for (int i = 0; i < objectManager->ActiveCount; i++)
    {   
        Engine_Object* tempObject = ObjectManager_Get(objectManager, i);
        //Entity_SetVelocity(tempEntity, mousePosition);
        Object_UpdateRigid(tempObject, deltaTime); 
    }

    Engine_Manifold collisionData = Object_CollisionNormal(&objectManager->ObjectList[0], &objectManager->ObjectList[1]);
    if (collisionData.Hit == true)
    {
        //printf("Touching\n");
        Object_CollisionResolve(&objectManager->ObjectList[0], &objectManager->ObjectList[1], &collisionData);
    }
};