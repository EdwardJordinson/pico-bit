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

    
    Engine_GameEntity* tempEntityObject1 = EntityObject_GetData(ObjectManager_Get(objectManager, 0)->Data);
    Engine_GameEntity* tempEntityObject2 = EntityObject_GetData(ObjectManager_Get(objectManager, 1)->Data);
    Engine_PhysicsManifold collisionData = AABB_IntersectionAABB(tempEntityObject1->PhysicsBody.CollisionShape, tempEntityObject1->PhysicsBody.Transform2D.Position, tempEntityObject2->PhysicsBody.CollisionShape, tempEntityObject2->PhysicsBody.Transform2D.Position);
    if (collisionData.Hit == true)
    {
        Physics_CollisionResolve(&tempEntityObject1->PhysicsBody, &tempEntityObject2->PhysicsBody, &collisionData);
    }
};

void GameState_UpdateGameEntity(Engine_GameEntity* gameEntity)
{
    //tempEntityObject->Update(&tempEntityObject->PhysicsBody, deltaTime);
};

void GameState_UpdateDisplayEntity(Engine_DisplayEntity* displayEntity)
{

};