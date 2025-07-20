#include <Game/Game_Box.h>
#include <Engine/Engine_Globals.h>


typedef struct Game_Box
{
    Window_Position* boxPosition;
    SDL_FRect* renderBody;

};


Game_Box* InstanceBox(int posX, int posY)
{
    //Window_Position newPosition = {posX, posY};
    //SDL_FRect newFRect = {EngineWindow->width/2, EngineWindow->height/2, EngineWindow->width/4, EngineWindow->height/4};
    //Game_Box newBox = {&newPosition, &newFRect};
    //return &newBox;
};