#include <Engine/Engine_GameObject.h>
#include <Engine/Engine_EventProcess.h>
#include <Engine/Engine_Coordinates.h>
#include <Engine/Engine_Physics.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


void GameObject_Initialise()
{ //Set values to defaults -> Creation pipeline
    //return(Engine_GameObject){};

};

void GameObject_SetDefault(Engine_GameObject* gameObject)
{
	gameObject->Transform2D = Matrix3x2_Inititialise();
	gameObject->Velocity = Vector2_Initialise();
	gameObject->CollisionShape = AABB_Initialise();
	gameObject->Restitution = 1.0;
	gameObject->Mass = 1.0;
	gameObject->InverseMass = 1/gameObject->Mass;
	gameObject->Update = Physics_UpdateRigid;

};

void GameObject_SetConfiguration(Engine_GameObject* gameObject, Engine_GameObject configObject)
{
	*gameObject = configObject;
};

void GameObject_SetPositionXY(Engine_GameObject* gameObject, float xPosition, float yPosition)
{
	Vector2_SetXY(&gameObject->Transform2D.Position, xPosition, yPosition);
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
	gameObject->Mass = mass;
	if (mass == 0.0) gameObject->InverseMass = 0.0;
	else gameObject->InverseMass = 1/gameObject->Mass;
};
