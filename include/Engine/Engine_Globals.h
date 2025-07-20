#ifndef Engine_Globals_H
#define Engine_Globals_H

#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include <stdbool.h>

//Global variables will start will capitalised letter

typedef struct
{
    int width;
    int height;

    SDL_Window *window;
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Renderer *renderer;

} Engine_Window;

typedef struct
{
    bool running;
    float delta;

} Engine_Loop;


extern Engine_Window *EngineWindow;
extern Engine_Loop *EngineLoop;


#endif // Engine_Globals_H