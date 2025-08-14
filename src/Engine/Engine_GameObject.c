#include <Engine/Engine_GameObject.h>
#include <Engine/Engine_EventProcess.h>
#include <Engine/Engine_Coordinates.h>
#include <Engine/Engine_Physics.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


Engine_GameObject GameObject_Initialise()
{
	return (Engine_GameObject){0,PhysicsBody_Initialise()};
};

void GameObject_SetDefault(Engine_GameObject* gameObject)
{
	gameObject->RenderID = 0;
	gameObject->PhysicsBody = PhysicsBody_Initialise();

	gameObject->Update = Physics_UpdateRigid;

};

void GameObject_SetConfiguration(Engine_GameObject* gameObject, Engine_GameObject configObject)
{
	*gameObject = configObject;
};

void GameObject_SetPositionXY(Engine_GameObject* gameObject, float xPosition, float yPosition)
{
	Vector2_SetXY(&gameObject->PhysicsBody.Transform2D.Position, xPosition, yPosition);
};

void GameObject_SetPositionVector(Engine_GameObject* gameObject, Vector2 vector)
{
	GameObject_SetPositionXY(gameObject, vector.x, vector.y);
};

void GameObject_SetUpdateFunction(Engine_GameObject* gameObject, void* updateFunction)
{
	gameObject->Update = updateFunction;
};

void GameObject_SetMass(Engine_GameObject* gameObject, float mass)
{
	gameObject->PhysicsBody.MassData.Mass = mass;
	if (mass == 0.0) gameObject->PhysicsBody.MassData.InverseMass = 0.0;
	else gameObject->PhysicsBody.MassData.InverseMass = 1/gameObject->PhysicsBody.MassData.Mass;
};
