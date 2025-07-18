#ifndef Engine_Window_H
#define Engine_Window_H

typedef struct SDL_Window SDL_Window;
typedef struct SDL_Surface SDL_Surface;

typedef struct Engine_Window
{
    int width;
    int height;

    SDL_Window* window;
    
    SDL_Surface* surface;

} Engine_Window;

#endif // Engine_Window_H