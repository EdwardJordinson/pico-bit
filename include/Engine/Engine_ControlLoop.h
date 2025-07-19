#ifndef Engine_ControlLoop_H
#define Engine_ControlLoop_H

#include <stdbool.h>

//Forward declares
typedef struct Engine_Window Engine_Window;


typedef struct Engine_ControlLoop
{
    bool running;
    float delta;

    Engine_Window *window;

} Engine_ControlLoop;


void RunLoop(Engine_ControlLoop *engineControlLoop);

void UpdateLoop();

void DrawLoop(Engine_Window *engineWindow);

#endif //Engine_ControlLoop_H