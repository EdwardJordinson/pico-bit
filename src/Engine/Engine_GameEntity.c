#include <Engine/Engine_EntityObject.h>





Engine_GameEntity GameEntity_Initialise()
{

};

void GameEntity_SetDefault(Engine_GameEntity* gameEntity)
{
    gameEntity->RenderID = 0;
	gameEntity->PhysicsBody = PhysicsBody_Initialise();

	gameEntity->Update = Physics_UpdateRigid;

};

void GameEntity_SetConfiguration(Engine_GameEntity* gameEntity, Engine_GameEntity configObject)
{
    
};

void GameEntity_SetPositionXY(Engine_GameEntity* gameEntity, float xPosition, float yPosition)
{
    Vector2_SetXY(&gameEntity->PhysicsBody.Transform2D.Position, xPosition, yPosition);
};

void GameEntity_SetPositionVector(Engine_GameEntity* gameEntity, Vector2 vector)
{
    GameEntity_SetPositionXY(gameEntity, vector.x, vector.y);
};

void GameEntity_SetUpdateFunction(Engine_GameEntity* gameEntity, void* updateFunction)
{
    gameEntity->Update = updateFunction;
};

void GameEntity_SetMass(Engine_GameEntity* gameEntity, float mass)
{
    gameEntity->PhysicsBody.MassData.Mass = mass;
	if (mass == 0.0) gameEntity->PhysicsBody.MassData.InverseMass = 0.0;
	else gameEntity->PhysicsBody.MassData.InverseMass = 1/gameEntity->PhysicsBody.MassData.Mass;
};