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

} Vector2;

typedef struct
{
    Vector2 Position;
    Vector2 Shape[4];
    int ID;

} Engine_Entity;

typedef struct
{

} Engine;


extern Engine_Window* EngineWindow;
extern Engine_Loop* EngineLoop;
extern SDL_FRect* LoadedRects[2];
extern Engine_Entity* Entities[1];

#endif // Engine_Globals_H