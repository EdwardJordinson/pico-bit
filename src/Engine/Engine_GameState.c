#include <Engine/Engine_GameState.h>
#include <Engine/Engine_Globals.h>
#include <Engine/Engine_Entity.h>
#include <SDL3/SDL_events.h>
#include <stdio.h>


void GameState_Update(Engine_GameState* gamestate, SDL_Event* event)
{
    Update_HandleInput(gamestate, event);

    Entity_Simulate(&gamestate->EntityManager->entities[0], Engine->MainLoop->delta);
};

void Update_HandleInput(Engine_GameState* gamestate, union SDL_Event* event)
{
    while (SDL_PollEvent(event) == true)
    {
        if (event->type == SDL_EVENT_QUIT)
        {
            Engine->MainLoop->running = false;
        }
        if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN)
        {
            if (event->button.button == SDL_BUTTON_LEFT)
            {
                float xMouse, yMouse;
                SDL_GetMouseState(&xMouse, &yMouse);

                //printf("%d\n", gamestate->EntityManager->activeCount);

                if (gamestate->EntityManager->activeCount == 0)
                {
                    //AddEntity(xMouse, yMouse);
                }
                else
                {
                    Entity_Update(&gamestate->EntityManager->entities[0], xMouse, yMouse);
                }
            }
        }
        else if (event->type == SDL_EVENT_MOUSE_MOTION)
        {
            mousePos.x = event->motion.x;
            mousePos.y = event->motion.y;
        }
    }
};

