#ifndef Engine_RenderState_H
#define Engine_RenderState_H

//Forward declares
typedef struct Engine_Window Engine_Window;
typedef struct Engine_GameState Engine_GameState;
typedef struct Engine_ObjectManager Engine_ObjectManager;
typedef struct Vector2 Vector2;
typedef struct SDL_Renderer SDL_Renderer;
typedef struct Engine_AABB Engine_AABB;
typedef struct TTF_Font TTF_Font;
typedef struct SDL_Texture SDL_Texture;
typedef struct Engine_RenderObject Engine_RenderObject;
typedef struct Engine_GameEntity Engine_GameEntity;
typedef struct Engine_DisplayEntity Engine_DisplayEntity;
typedef struct Engine_OBB Engine_OBB;
//

typedef struct Engine_RenderState
{
    Engine_Window* EngineWindow;
    Engine_ObjectManager* RenderManager;
    TTF_Font* font;
    SDL_Texture* textTexture;

} Engine_RenderState;


void RenderState_Initialise(Engine_RenderState* renderState);
void RenderState_Draw(Engine_RenderState* renderState, Engine_GameState* gameState);
void RenderState_DrawObjects(Engine_RenderState* renderState, Engine_ObjectManager* objectManager);
void RenderState_DrawGame(Engine_RenderState* renderState, Engine_GameEntity* gameEntity, Engine_RenderObject* renderObject);
void RenderState_DrawDisplay(Engine_RenderState* renderState, Engine_DisplayEntity* displayEntity, Engine_RenderObject* renderObject);
void RenderState_DrawLine(SDL_Renderer* renderer, Vector2 vector1, Vector2 vector2);
void RenderState_DrawText(SDL_Renderer* renderer, TTF_Font* font, SDL_Texture* textTexture, Engine_RenderObject* renderObject);
void RenderState_DrawAABB(SDL_Renderer* renderer, Engine_AABB drawBox);
void RenderState_DrawOBB(SDL_Renderer* renderer, Engine_OBB drawBox, Vector2 position);
void RenderState_DrawCircle(SDL_Renderer* renderer, int radius, Vector2 position);
Vector2 RenderState_WorldToScreen(Engine_Window* window, Vector2 position);

#endif //Engine_RenderState_H