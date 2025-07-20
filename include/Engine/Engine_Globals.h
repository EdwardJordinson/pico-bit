#ifndef Engine_Globals_H
#define Engine_Globals_H

#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_rect.h>
#include <stdint.h>
#include <stdbool.h>

//Global variables will start will capitalised letter

typedef struct
{
    int width;
    int height;

    SDL_Window* window;
    SDL_Renderer* renderer;

} Engine_Window;

typedef struct
{
    bool running;
    uint32_t delta;

} Engine_Loop;

typedef struct
{
    int x, y;

} Window_Position;

typedef struct
{
    Window_Position position;
    SDL_FRect* renderBody;

} Render_Target;

extern Engine_Window* EngineWindow;
extern Engine_Loop* EngineLoop;
extern Render_Target* RenderTargets[1];

#endif // Engine_Globals_H