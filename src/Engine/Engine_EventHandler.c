#include <Engine/Engine_EventHandler.h>
#include <Engine/Engine_GameState.h>


void Event_Process(Engine_EventHandler* eventHandler, Engine_GameState* gameState, bool* running)
{
    while (SDL_PollEvent(eventHandler->SDLEvent) == true)
    {
        switch (eventHandler->SDLEvent->type)
        {
        case SDL_EVENT_QUIT:
            *running = false;
            break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            if (eventHandler->SDLEvent->button.button == SDL_BUTTON_LEFT)
            {
                float xMouse, yMouse;
                SDL_GetMouseState(&xMouse, &yMouse);
                //int entityID = EntityManager_Allocate(gameState->EntityManager);

            }
            else if (eventHandler->SDLEvent->button.button == SDL_BUTTON_RIGHT)
            {

            }
            break;
        case SDL_EVENT_MOUSE_BUTTON_UP:
            
            break;
        case SDL_EVENT_MOUSE_MOTION:
            eventHandler->mouseVector.x = eventHandler->SDLEvent->motion.x;
            eventHandler->mouseVector.y = eventHandler->SDLEvent->motion.y;
            break;
        default:
            break;
        }
    }
};