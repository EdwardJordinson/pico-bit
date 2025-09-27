#include <Engine/Engine_EventProcess.h>
#include <Engine/Engine_GameState.h>
#include <SDL3/SDL_events.h>


void EventProcess_Initialise(Engine_EventProcess* eventprocess)
{

};

void EventProcess_Check(Engine_EventProcess* eventProcess, Engine_GameState* gameState, bool* running)
{
    while (SDL_PollEvent(eventProcess->SDLEvent) == true)
    {
        switch (eventProcess->SDLEvent->type)
        {
        case SDL_EVENT_QUIT:
            *running = false;
            break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            if (eventProcess->SDLEvent->button.button == SDL_BUTTON_LEFT)
            {
                float xMouse, yMouse;
                SDL_GetMouseState(&xMouse, &yMouse);
                
            }
            else if (eventProcess->SDLEvent->button.button == SDL_BUTTON_RIGHT)
            {

            }
            break;
        case SDL_EVENT_MOUSE_BUTTON_UP:
            
            break;
        case SDL_EVENT_MOUSE_MOTION:
            break;
        default:
            break;
        }
    }
};