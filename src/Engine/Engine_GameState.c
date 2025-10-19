#include <Engine/Engine_GameState.h>
#include <Engine/Engine_Object.h>
#include <Engine/Engine_EntityObject.h>
#include <Engine/Engine_EventProcess.h>
#include <Engine/Engine_Physics.h>
#include <stdio.h>


void GameState_Initialise(Engine_GameState* gameState)
{
    gameState->delta = 0.0;

};

void GameState_Update(Engine_GameState* gameState, Engine_EventProcess* eventProcess)
{
    GameState_EntityAllUpdate(gameState->EntityManager, gameState->delta);

};

void GameState_EntityAllUpdate(Engine_ObjectManager* objectManager, float deltaTime)
{
    for (int i = 0; i < objectManager->ActiveCount; i++)
    {   
        Engine_EntityObject* tempEntityObject = ObjectManager_Get(objectManager, i)->Data;
        Engine_GameEntity* tempGameEntity = EntityObject_GetData(tempEntityObject);
        switch (tempEntityObject->EntityType)
        {
        case 1:
            tempGameEntity->Update(&tempGameEntity->PhysicsBody, deltaTime);
            break;
        case 2:
            break;
        default:
            break;
        }
    }
    

    Engine_PhysicsBroadPhase broadPhase;
    PhysicsBroadPhase_TEMPPairList(&broadPhase, objectManager);

    if (broadPhase.count != 0)
    {
        printf("Contact!!!\n");
        
        for (int i = 0; i < broadPhase.count; i++)
        {
            Engine_PhysicsBody* tempBody1 = broadPhase.PairList[i].physicsBody1;
            Engine_PhysicsBody* tempBody2 = broadPhase.PairList[i].physicsBody2;
            Physics_CollisionResolve(tempBody2, tempBody1, &broadPhase.PairList[i].manifold);
        }
    }

};

void GameState_UpdateGameEntity(Engine_GameEntity* gameEntity)
{
    //tempEntityObject->Update(&tempEntityObject->PhysicsBody, deltaTime);
};

void GameState_UpdateDisplayEntity(Engine_DisplayEntity* displayEntity)
{

};