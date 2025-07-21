#ifndef Engine_Draw_H
#define Engine_Draw_H

//Forward declares
typedef struct Engine_GameState Engine_GameState;
typedef struct Engine_Renderer Engine_Renderer;
//

void DrawCall(Engine_Renderer* renderer, Engine_GameState* gamestate);

#endif //Engine_Draw_H