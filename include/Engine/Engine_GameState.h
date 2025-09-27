#ifndef Engine_GameState_H
#define Engine_GameState_H

//Forward declares
typedef struct Engine_EventProcess Engine_EventProcess;
typedef struct Engine_ObjectManager Engine_ObjectManager;
typedef struct Engine_GameEntity Engine_GameEntity;
typedef struct Engine_DisplayEntity Engine_DisplayEntity;
//

typedef struct Engine_GameState
{
    float delta;
    Engine_ObjectManager* EntityManager;

} Engine_GameState;


void GameState_Initialise(Engine_GameState* gameState);
void GameState_Update(Engine_GameState* gameState, Engine_EventProcess* eventProcess);
void GameState_EntityAllUpdate(Engine_ObjectManager* objectManager, float deltaTime);
void GameState_UpdateGameEntity(Engine_GameEntity* gameEntity);
void GameState_UpdateDisplayEntity(Engine_DisplayEntity* displayEntity);

#endif //Engine_GameState_H