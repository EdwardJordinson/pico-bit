#ifndef Engine_Window_H
#define Engine_Window_H


//Forward declares
typedef struct SDL_Window SDL_Window;
typedef struct SDL_Renderer SDL_Renderer;
typedef struct Vector2 Vector2;
//

typedef struct Engine_Window
{
    int width;
    int height;

    SDL_Window* SDLWindow;
    SDL_Renderer* SDLRenderer;

} Engine_Window;


void Window_Initialise(Engine_Window* engineWindow);


#endif //Engine_Window_H