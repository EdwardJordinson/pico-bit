#include <Engine/Engine_Update.h>
#include <Engine/Engine_Globals.h>
#include <Engine/Engine_Entity.h>
#include <SDL3/SDL_events.h>
#include <stdio.h>


void UpdateCall(Engine_GameState* gamestate, SDL_Event* event)
{
    while (SDL_PollEvent(event) == true)
    {
        if (event->type == SDL_EVENT_QUIT)
        {
            Engine->Loop->running = false;
        }
        if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN)
        {
            if (event->button.button == SDL_BUTTON_LEFT)
            {
                float xMouse, yMouse;
                SDL_GetMouseState(&xMouse, &yMouse);
                if (gamestate->EntitiesLoaded[0] == NULL)
                {
                    AddEntity(xMouse, yMouse);
                }
                else
                {
                    UpdateEntity(0, xMouse, yMouse);
                }
            }
        }
    }

};



