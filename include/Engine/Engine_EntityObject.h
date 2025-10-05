#ifndef Engine_EntityObject_H
#define Engine_EntityObject_H

/*
Entity objects are game state/world loaded data. There are two types of entities (Game & Display)
Game are entities in the game world proper, while display are the terminal/hud elements.
The seperation was done because raw game data does not need to be rendered, only parts of the game world displayed via the window/terminals.

*/

#include <Engine/Engine_Coordinates.h>
#include <Engine/Engine_Collision.h>
#include <Engine/Engine_Physics.h>


//Forward declares
typedef struct Engine_EventHandler Engine_EventHandler;
typedef struct Vector2 Vector2;
typedef struct Engine_AABB Engine_AABB;
//

enum EntityType
{
    e_NILL,
    e_GAME,
    e_DISPLAY
};

typedef struct Engine_GameEntity
{
    int RenderID;
    Engine_PhysicsBody PhysicsBody;

    void (*Update)(struct Engine_PhysicsBody*,float);

} Engine_GameEntity;


Engine_GameEntity GameEntity_Initialise();
void GameEntity_SetDefault(Engine_GameEntity* entityObject);
void GameEntity_SetConfiguration(Engine_GameEntity* entityObject, Engine_GameEntity configObject);
void GameEntity_SetPositionXY(Engine_GameEntity* entityObject, float xPosition, float yPosition);
void GameEntity_SetPositionVector(Engine_GameEntity* entityObject, Vector2 vector);
void GameEntity_SetRotationRad(Engine_GameEntity* entityObject, float radians);
void GameEntity_SetRotationVector(Engine_GameEntity* entityObject, Vector2 vector);
void GameEntity_SetUpdateFunction(Engine_GameEntity* entityObject, void* updateFunction);
void GameEntity_SetMass(Engine_GameEntity* entityObject, float mass);


typedef struct Engine_DisplayEntity
{
    int RenderID;
    Vector2 Position;
    float Width;
    float Height;
    char Text[32];

} Engine_DisplayEntity;

//TEMPORARY SOLUTION/THE NATURE OF THE GAME SHOULDNT NEED THESE TWO OBJECTS TO SHARE MEMEORY TOGETHER LIKE THIS.
union EntityData
{
    Engine_GameEntity GameEntity;
    Engine_DisplayEntity DisplayEntity;
};

typedef struct Engine_EntityObject
{
    enum EntityType EntityType;
    union EntityData Data;

    void* (*GetData)(struct Engine_EntityObject*);

} Engine_EntityObject;


Engine_EntityObject EntityObject_Initialise();
void EntityObject_SetDefault(Engine_EntityObject* entityObject);
void EntityObject_SetConfiguration(Engine_EntityObject* entityObject, Engine_EntityObject configObject);
void* EntityObject_GetData(Engine_EntityObject* entityObject);

#endif //Engine_EntityObject_H