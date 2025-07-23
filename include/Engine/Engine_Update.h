#ifndef Engine_Update_H
#define Engine_Update_H

//Forward declares
typedef struct Engine_GameState Engine_GameState;
union SDL_Event;
//

void UpdateCall(Engine_GameState* gamestate, union SDL_Event* event);

#endif //Engine_Update_H