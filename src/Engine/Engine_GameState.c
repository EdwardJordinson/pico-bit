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
        //tempEntityObject->Update(&tempEntityObject->PhysicsBody, deltaTime);
        switch (tempEntityObject->EntityType)
        {
        case 1:
            //GameState_UpdateGameEntity(tempEntityObject);
            tempGameEntity->Update(&tempGameEntity->PhysicsBody, deltaTime);
            break;
        case 2:
            //GameState_UpdateDisplayEntity(tempGameEntity);
            break;
        default:
            break;
        }
    }

    /*
    Engine_GameEntity* tempEntityObject1 = EntityObject_GetData(ObjectManager_Get(objectManager, 0)->Data);
    Engine_GameEntity* tempEntityObject2 = EntityObject_GetData(ObjectManager_Get(objectManager, 1)->Data);
    Engine_PhysicsManifold collisionData = AABB_IntersectionAABB(tempEntityObject2->PhysicsBody.CollisionShape, tempEntityObject2->PhysicsBody.Transform2D.Position, tempEntityObject1->PhysicsBody.CollisionShape, tempEntityObject1->PhysicsBody.Transform2D.Position);
    if (collisionData.Hit == true)
    {
        Physics_CollisionResolve(&tempEntityObject1->PhysicsBody, &tempEntityObject2->PhysicsBody, &collisionData);
    }  
    */
    Engine_PhysicsBroadPhase broadPhase;
    PhysicsBroadPhase_TEMPPairList(&broadPhase, objectManager);

    if (broadPhase.count != 0)
    {
        printf("Contact!!!\n");
        
        for (int i = 0; i < broadPhase.count; i++)
        {

            Engine_PhysicsBody* tempBody1 = broadPhase.PairList[i].physicsBody1;
            Engine_PhysicsBody* tempBody2 = broadPhase.PairList[i].physicsBody2;
            Engine_PhysicsManifold collisionData = AABB_IntersectionAABB(tempBody2->CollisionShape, tempBody2->Transform2D.Position, tempBody1->CollisionShape, tempBody1->Transform2D.Position);
            Physics_CollisionResolve(tempBody1, tempBody2, &collisionData);
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