#ifndef Engine_RenderState_H
#define Engine_RenderState_H

//Forward declares
typedef struct Engine_Window Engine_Window;
typedef struct Engine_GameState Engine_GameState;
typedef struct Engine_ObjectManager Engine_ObjectManager;
typedef struct Engine_RenderManager Engine_RenderManager;
typedef struct Vector2 Vector2;
//

typedef struct Engine_RenderState
{
    Engine_Window* EngineWindow;
    Engine_RenderManager* RenderManager;

} Engine_RenderState;


void RenderState_Initialise(Engine_RenderState* renderState);

void RenderState_Draw(Engine_RenderState* renderState, Engine_GameState* gameState);

void Draw_Entities(Engine_RenderState* renderState, Engine_ObjectManager* objectManager);

Vector2 RenderState_WorldToScreen(Engine_Window* window, Vector2 position);

#endif //Engine_RenderState_H