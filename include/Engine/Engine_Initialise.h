#ifndef Engine_Initialise_H
#define Engine_Initialise_H

#include <stddef.h>

//Forward declares
typedef struct Engine_Globals Engine_Globals;
typedef struct Engine_EntityManager Engine_EntityManager;
typedef struct Engine_Window Engine_Window;
union SDL_Event;
typedef struct Engine_GameState Engine_GameState;
typedef struct Engine_Renderer Engine_Renderer;
typedef struct Engine_Loop Engine_Loop;
//

void InitialiseEngine(Engine_Globals** globals);

void InitialiseEntityManager(Engine_EntityManager* pool);

void InitialiseWindow(Engine_Window** window);

void InitialiseEvent(union SDL_Event** event);

void InitialiseGameState(Engine_GameState** gamestate);

void InitialiseRenderer(Engine_Renderer** renderer);

void InitialiseLoop(Engine_Loop** engineLoop);

#endif //Engine_Initialise_H