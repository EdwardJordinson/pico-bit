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

void GameEntity_SetConfiguration(Engine_GameEntity* gameEntity, Engine_GameEntity configEntity)
{
    *gameEntity = configEntity;
};

void GameEntity_SetPositionXY(Engine_GameEntity* gameEntity, float xPosition, float yPosition)
{
    Vector2_SetXY(&gameEntity->PhysicsBody.Transform2D.Position, xPosition, yPosition);
};

void GameEntity_SetPositionVector(Engine_GameEntity* gameEntity, Vector2 vector)
{
    GameEntity_SetPositionXY(gameEntity, vector.x, vector.y);
};

void GameEntity_SetRotationRad(Engine_GameEntity* entityObject, float radians)
{
    Matrix2x2_SetMatrix2x2(&entityObject->PhysicsBody.Transform2D.RotationMatrix, Matrix2x2_Rotation(radians));
};

void GameEntity_SetRotationVector(Engine_GameEntity* entityObject, Vector2 vector)
{

};

void GameEntity_SetUpdateFunction(Engine_GameEntity* gameEntity, void* updateFunction)
{
    gameEntity->Update = updateFunction;
};

void GameEntity_SetMass(Engine_GameEntity* gameEntity, float mass)
{
    gameEntity->PhysicsBody.MassData.Mass = mass;
	if (mass == 0.0f) gameEntity->PhysicsBody.MassData.InverseMass = 0.0f;
	else gameEntity->PhysicsBody.MassData.InverseMass = 1.0f/gameEntity->PhysicsBody.MassData.Mass;
};

void GameEntity_SetInertia(Engine_GameEntity* gameEntity, float inertia)
{
    gameEntity->PhysicsBody.MassData.Inertia = inertia;
	if (inertia == 0.0f) gameEntity->PhysicsBody.MassData.InverseInertia = 0.0f;
	else gameEntity->PhysicsBody.MassData.InverseInertia = 1.0f/gameEntity->PhysicsBody.MassData.Inertia;
};