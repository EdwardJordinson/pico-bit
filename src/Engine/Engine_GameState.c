#include <Engine/Engine_GameState.h>
#include <Engine/Engine_Object.h>
#include <Engine/Engine_GameObject.h>
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
        Engine_GameObject* tempGameObject = ObjectManager_Get(objectManager, i)->Data;
        GameObject_UpdateRigid(tempGameObject, deltaTime); 
    }

    Engine_GameObject* tempGameObject1 = ObjectManager_Get(objectManager, 0)->Data;
    Engine_GameObject* tempGameObject2 = ObjectManager_Get(objectManager, 1)->Data;
    Engine_Manifold collisionData = GameObject_CollisionNormal(tempGameObject1, tempGameObject2);
    if (collisionData.Hit == true)
    {
        GameObject_CollisionResolve(tempGameObject1, tempGameObject2, &collisionData);
    }
};