#ifndef Engine_Globals_H
#define Engine_Globals_H

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

#endif //Engine_Globals_H