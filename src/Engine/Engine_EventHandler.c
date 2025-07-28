#include <Engine/Engine_EventHandler.h>


void Event_Process(Engine_EventHandler* eventHandler, bool* running)
{
    while (SDL_PollEvent(eventHandler->SDLEvent) == true)
    {
        if (eventHandler->SDLEvent->type == SDL_EVENT_QUIT)
        {
           *running = false;
        }
        if (eventHandler->SDLEvent->type == SDL_EVENT_MOUSE_BUTTON_DOWN)
        {
            if (eventHandler->SDLEvent->button.button == SDL_BUTTON_LEFT)
            {
                float xMouse, yMouse;
                SDL_GetMouseState(&xMouse, &yMouse);

                //printf("%d\n", gamestate->EntityManager->activeCount);
                
                /*
                if (gamestate->EntityManager->activeCount == 0)
                {
                    //AddEntity(xMouse, yMouse);
                }
                else
                {
                    //Entity_Update(&gamestate->EntityManager->entities[0], xMouse, yMouse);
                }                
                */
            }
        }
        else if (eventHandler->SDLEvent->type == SDL_EVENT_MOUSE_MOTION)
        {
            eventHandler->mouseVector.x = eventHandler->SDLEvent->motion.x;
            eventHandler->mouseVector.y = eventHandler->SDLEvent->motion.y;
        }
    }
};