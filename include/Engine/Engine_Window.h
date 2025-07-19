#ifndef Engine_Window_H
#define Engine_Window_H

//Forward declares
typedef struct SDL_Window SDL_Window;
typedef struct SDL_Surface SDL_Surface;
typedef struct SDL_Texture SDL_Texture;
typedef struct SDL_Renderer SDL_Renderer;
//

typedef struct Engine_Window
{
    int width;
    int height;

    SDL_Window *window;
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Renderer *renderer;

} Engine_Window;


#endif // Engine_Window_H