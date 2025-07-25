#ifndef Engine_Globals_H
#define Engine_Globals_H


/*
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_events.h>
#include <Engine/Engine_GameState.h>
#include <Engine/Engine_RenderState.h>
#include <Engine/Engine_EntityManager.h>
#include <Engine/Engine_Vector2.h>
*/

#include <Engine/Engine_Window.h>
#include <Engine/Engine_MainLoop.h>
#include <stdint.h>
#include <stdbool.h>

//Forward declares
//

//Global engine variables for ease of access (avoid reliance if possible).
typedef struct Engine_Globals
{
    Engine_Window* Window;
    Engine_MainLoop* MainLoop;

} Engine_Globals;
//

extern Engine_Globals* Engine;
extern Vector2 mousePos;

#endif // Engine_Globals_H