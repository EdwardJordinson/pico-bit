#include <Engine/Engine_Entity.h>
#include <Engine/Engine_Globals.h>
#include <Engine/Engine_Vector2.h>
#include <stdlib.h>
#include <stdio.h>

//Forward Declare
//

Engine_Entity Entity_Initialise(int id)
{
    return (Engine_Entity){id};
};

void Entity_Setup(Engine_Entity* entity, int xPosition, int yPosition)
{
    entity->Position = Vector2_Initialise(xPosition, yPosition);
    entity->Velocity = Vector2_Initialise(0.0, 0.0);
};

/*
void Entity_Add(int xPosition, int yPosition)
{
    int newID = Engine_Entity_Allocate(Engine->Loop->GameState->EntityManager);
    Engine_Entity* newEntity = Engine_Entity_Get(Engine->Loop->GameState->EntityManager, newID);
    SetupEntity(newEntity, xPosition, yPosition);

};
*/

void Entity_Update(Engine_Entity* entity, int xPosition, int yPosition)
{
    entity->Position = Vector2_Initialise((xPosition+1) - (Engine->MainLoop->RenderState->RectsLoaded[0]->w/2), yPosition - (Engine->MainLoop->RenderState->RectsLoaded[0]->h/2));
};

//###Optimise###
void Entity_Simulate(Engine_Entity* entity, float deltaTime)
{
    //Get direction P - I, then normalise it.
    Vector2 offset = Vector2_Initialise((Engine->MainLoop->RenderState->RectsLoaded[0]->w/2), (Engine->MainLoop->RenderState->RectsLoaded[0]->h/2));
    Vector2 newPos = Vector2_VectorAdd(&entity->Position, &offset);
    Vector2 newDir = Vector2_Subtract(&mousePos, &newPos);
    Vector2 normalDir = Vector2_Normailised(&newDir);
    //Multiply the scalar value of your required velocity
    Vector2 speedDir = Vector2_ScalarMuliply(100, &normalDir);
    Vector2 finalDir = Vector2_VectorAdd(&entity->Velocity, &speedDir);
    printf("%.2f : %.2f\n", normalDir.x, normalDir.y);
    printf("%.2f : %.2f\n", mousePos.x, mousePos.y);
    printf("%.2f : %.2f\n", entity->Position.x, entity->Position.y);

    Vector2 newVector = Vector2_ScalarMuliply(deltaTime, &finalDir);
    entity->Position = Vector2_VectorAdd(&entity->Position, &newVector);
};