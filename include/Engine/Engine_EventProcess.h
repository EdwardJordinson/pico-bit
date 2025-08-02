#ifndef Engine_EventProcess_H
#define Engine_EventProcess_H

//#include <SDL3/SDL_events.h>
#include <stdbool.h>

//Forward declares
typedef struct Engine_GameState Engine_GameState;
//

typedef struct Engine_EventProcess
{
    union SDL_Event* SDLEvent;
    
} Engine_EventProcess;


void EventProcess_Initialise(Engine_EventProcess* eventprocess);

void EventProcess_Check(Engine_EventProcess* eventHandler, Engine_GameState* gameState, bool* running);


#endif //Engine_EventProcess_H