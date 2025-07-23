#ifndef Engine_Globals_H
#define Engine_Globals_H

#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_events.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_ENTITY_SIZE 512

typedef struct Vector2
{
    int x, y;
} Vector2;

typedef struct Engine_Entity
{
    Vector2 Position;
    Vector2 Shape[4];
    int ID;

} Engine_Entity;

typedef struct Engine_EntityManager
{
    Engine_Entity entities[MAX_ENTITY_SIZE];
    int freeList[MAX_ENTITY_SIZE];
    int freeCount;
    bool active[MAX_ENTITY_SIZE];
    int activeList[MAX_ENTITY_SIZE];
    int activeCount;

} Engine_EntityManager;

typedef struct Engine_Window
{
    int width;
    int height;

    SDL_Window* SDLWindow;
    SDL_Renderer* SDLRenderer;

} Engine_Window;

typedef struct Engine_GameState
{
    Engine_EntityManager* EntityManager;

} Engine_GameState;

typedef struct Engine_Renderer
{
    SDL_FRect* RectsLoaded[2];

} Engine_Renderer;

typedef struct Engine_Loop
{
    bool running;
    uint32_t delta;

    SDL_Event* SDLEvent;
    Engine_GameState* GameState;
    Engine_Renderer* Renderer;

} Engine_Loop;

typedef struct Engine_Globals
{
    Engine_Window* Window;
    Engine_Loop* Loop;

} Engine_Globals;

extern Engine_Globals* Engine;

#endif // Engine_Globals_H