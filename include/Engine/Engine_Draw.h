#ifndef Engine_Draw_H
#define Engine_Draw_H

//Forward declares
typedef struct Engine_GameState Engine_GameState;
typedef struct Engine_Renderer Engine_Renderer;
typedef struct Engine_EntityManager Engine_EntityManager;
//

void DrawCall(Engine_Renderer* renderer, Engine_GameState* gamestate);

void DrawEntities(Engine_Renderer* renderer, Engine_EntityManager* entityManager);

#endif //Engine_Draw_H