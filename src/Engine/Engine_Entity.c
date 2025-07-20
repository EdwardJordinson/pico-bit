#include <Engine/Engine_Entity.h>
#include <Engine/Engine_Globals.h>
#include <stdlib.h>




int InitEntity()
{
    Engine_Entity* newEntity = malloc(sizeof(Engine_Entity));
    newEntity->Position.x = 0;
    newEntity->Position.y = 0;

    newEntity->Shape[0].x = 100;
    newEntity->Shape[0].y = -100;

    newEntity->Shape[1].x = 100;
    newEntity->Shape[1].y = 100;

    newEntity->Shape[2].x = -100;
    newEntity->Shape[2].y = 100;

    newEntity->Shape[3].x = -100;
    newEntity->Shape[3].y = -100;

    newEntity->ID = 0;

    return 0;
};

void AddEntity(int xPosition, int yPosition)
{
    int entityID = InitEntity();
    Entities[entityID]->Position.x = xPosition;
    Entities[entityID]->Position.y = yPosition;
    
};

void UpdateEntity(int entityID, int xPosition, int yPosition)
{

};