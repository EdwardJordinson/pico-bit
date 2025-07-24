#ifndef Engine_Entity_H
#define Engine_Entity_H

#include <stdint.h>

//Forward declares
typedef struct Engine_EntityManager Engine_EntityManager;
typedef struct Engine_Entity Engine_Entity;
//

int InitEntity();

void AddEntity(int xPosition, int yPosition);

void UpdateEntity(int entityID, int xPosition, int yPosition);

void SetupEntity(Engine_Entity* entity, int xPosition, int yPosition);

void SimulateEntity(Engine_Entity* entity, float deltaTime);

int Engine_Entity_Allocate(Engine_EntityManager* manager);

void Engine_Entity_Free(Engine_EntityManager* manager, int index);

Engine_Entity* Engine_Entity_Get(Engine_EntityManager* manager, int index);

#endif // Engine_Entity_H