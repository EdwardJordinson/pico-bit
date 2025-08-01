#include <Engine/Engine_Window.h>
#include <Engine/Engine_Vector2.h>


void Window_Initialise()
{

};

Vector2 Window_WorldToScreen(Vector2 position)
{
    position.y = -position.y;
    float half_screen_width = EngineWindow->width/2.0;
    float half_screen_height = EngineWindow->height/2.0;

    position.x += half_screen_width;
    position.y += half_screen_height;
    return position;
};
