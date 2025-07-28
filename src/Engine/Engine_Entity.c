#include <Engine/Engine_Entity.h>
#include <Engine/Engine_EventHandler.h>
#include <Engine/Engine_Vector2.h>
#include <stdlib.h>
#include <stdio.h>


Engine_Entity Entity_Initialise(int id)
{
    return(Engine_Entity){id};
};

void Entity_Setup(Engine_Entity* entity, int xPosition, int yPosition)
{
    entity->Position = VECTOR2.Create(xPosition, yPosition); entity->Velocity = VECTOR2.Create(0.0, 0.0);
};

void Entity_Event(Engine_Entity* entity, Engine_EventHandler* eventHandler)
{
    while (SDL_PollEvent(eventHandler->SDLEvent) == true)
    {
        if (eventHandler->SDLEvent->type == SDL_EVENT_MOUSE_BUTTON_DOWN)
        {
            if (eventHandler->SDLEvent->button.button == SDL_BUTTON_LEFT)
            {
                float xMouse, yMouse;
                SDL_GetMouseState(&xMouse, &yMouse);
                Entity_SetPosition(entity, xMouse, yMouse);
            }
        }
    }
};

void Entity_SetPosition(Engine_Entity* entity, int xPosition, int yPosition)
{
    entity->Position = VECTOR2.Create((xPosition+5)-50, (yPosition+5)-50);
};

void Entity_SetVelocity(Engine_Entity* entity, Vector2 vector)
{
     entity->Velocity = Vector2_ScalarMuliply(
        100, Vector2_Normailised(
            Vector2_Subtract(
                vector, Vector2_VectorAdd(
                    entity->Position, Vector2_Initialise(
                        50, 50)))));//Vector2_VectorAdd(entity->Velocity, ); 

    printf("%.2f : %.2f\n", vector.x, vector.y);
    printf("%.2f : %.2f\n", entity->Velocity.x, entity->Velocity.y);
    printf("%.2f : %.2f\n", entity->Position.x, entity->Position.y);
    
};

void Entity_Simulate(Engine_Entity* entity, float deltaTime)
{
    entity->Position = Vector2_VectorAdd(entity->Position, Vector2_ScalarMuliply(deltaTime, entity->Velocity));
}; 