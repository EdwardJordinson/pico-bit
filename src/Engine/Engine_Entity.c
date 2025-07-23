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

    Engine->Loop->GameState->EntitiesLoaded[0] = newEntity;

    return 0;
};

void AddEntity(int xPosition, int yPosition)
{
    int entityID = InitEntity();
    Engine->Loop->GameState->EntitiesLoaded[entityID]->Position.x = xPosition - (Engine->Loop->Renderer->RectsLoaded[entityID]->w/2);
    Engine->Loop->GameState->EntitiesLoaded[entityID]->Position.y = yPosition - (Engine->Loop->Renderer->RectsLoaded[entityID]->h/2);

};

void UpdateEntity(int entityID, int xPosition, int yPosition)
{
    Engine->Loop->GameState->EntitiesLoaded[entityID]->Position.x = xPosition - (Engine->Loop->Renderer->RectsLoaded[entityID]->w/2);
    Engine->Loop->GameState->EntitiesLoaded[entityID]->Position.y = yPosition - (Engine->Loop->Renderer->RectsLoaded[entityID]->h/2);
};