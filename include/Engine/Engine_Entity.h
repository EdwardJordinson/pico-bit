#ifndef Engine_Entity_H
#define Engine_Entity_H

#include <Engine/Engine_Vector2.h>
#include <stdint.h>

//Forward declares
//

typedef struct Engine_Entity
{
    int ID;
    Vector2 Position;
    Vector2 Velocity;
    Vector2 Shape[4];

} Engine_Entity;


Engine_Entity Entity_Initialise(int id);

void Entity_Setup(Engine_Entity* entity, int xPosition, int yPosition);

void Entity_Update(Engine_Entity* entity, int xPosition, int yPosition);

void Entity_Simulate(Engine_Entity* entity, float deltaTime);

#endif // Engine_Entity_H