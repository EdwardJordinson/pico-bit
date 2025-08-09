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
    Vector2_SetXY(&gameObject->Transform2D.Position, 0.0,0.0);
    Vector2_SetXY(&gameObject->Velocity, 0.0,0.0);
    AABB_SetMaxMin(&gameObject->CollisionShape,(Vector2){50.0,50.0},(Vector2){-50.0,-50.0});
	gameObject->Restitution = 1.0;
	gameObject->Mass = 10.0;
	gameObject->Update = Physics_UpdateRigid;

};

void GameObject_SetConfiguration(Engine_GameObject* gameObject, Engine_GameObject configObject)
{
	*gameObject = configObject;
};

void GameObject_SetPositionXY(Engine_GameObject* gameObject, float xPosition, float yPosition)
{
    Vector2_SetXY(&gameObject->Transform2D.Position, xPosition+gameObject->CollisionShape.minVector.x, yPosition+gameObject->CollisionShape.minVector.y);
};

void GameObject_SetPositionVector(Engine_GameObject* gameObject, Vector2 vector)
{
	GameObject_SetPositionXY(gameObject, vector.x, vector.y);
};

void GameObject_SetUpdateFunction(Engine_GameObject* gameObject, void* updateFunction)
{
	gameObject->Update = updateFunction;
};