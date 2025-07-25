#ifndef Engine_Initialise_H
#define Engine_Initialise_H

#include <stddef.h>

//Forward declares
typedef struct Engine_Globals Engine_Globals;
typedef struct Engine_Window Engine_Window;
typedef struct Engine_EventHandler Engine_EventHandler;
typedef struct Engine_GameState Engine_GameState;
typedef struct Engine_EntityManager Engine_EntityManager;
typedef struct Engine_RenderState Engine_RenderState;
typedef struct Engine_MainLoop Engine_MainLoop;
//

void Initialise_Engine(Engine_Globals** globals);

void Initialise_Window(Engine_Window** window);

void Initialise_Event(Engine_EventHandler** event);

void Initialise_GameState(Engine_GameState** gameState);

void Initialise_RenderState(Engine_RenderState** renderState);

void Initialise_MainLoop(Engine_MainLoop** mainLoop);

#endif //Engine_Initialise_H