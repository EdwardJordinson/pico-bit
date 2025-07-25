#ifndef Engine_EventHandler_H
#define Engine_EventHandler_H

#include <SDL3/SDL_events.h>
#include <Engine/Engine_Vector2.h>
#include <stdbool.h>

//Forward declares
typedef struct Vector2 Vector2;
//

typedef struct Engine_EventHandler
{
    SDL_Event* SDLEvent;
    Vector2 mouseVector;
    
} Engine_EventHandler;

void Event_Process(Engine_EventHandler* eventHandler, bool* running);


#endif //Engine_EventHandler_H