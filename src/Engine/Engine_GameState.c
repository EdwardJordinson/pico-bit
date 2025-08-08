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
        //Engine_Object* tempObject = ObjectManager_Get(objectManager, i);
        Engine_Object* tempObject = ObjectManager_Get(objectManager, i);
        Engine_GameObject* tempGameObject = tempObject->Data;
        GameObject_UpdateRigid(tempGameObject, deltaTime); 
    }

    Engine_Object* tempObject1 = ObjectManager_Get(objectManager, 0);
    Engine_GameObject* tempGameObject1 = tempObject1->Data;
    Engine_Object* tempObject2 = ObjectManager_Get(objectManager, 1);
    Engine_GameObject* tempGameObject2 = tempObject2->Data;
    Engine_Manifold collisionData = GameObject_CollisionNormal(tempGameObject1, tempGameObject2);
    if (collisionData.Hit == true)
    {
        //printf("Touching\n");
        GameObject_CollisionResolve(tempGameObject1, tempGameObject2, &collisionData);
    }
};