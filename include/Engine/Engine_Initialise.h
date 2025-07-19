#ifndef Engine_Initialise_H
#define Engine_Initialise_H

//Forward declares
typedef struct Engine_Window Engine_Window;
typedef struct Engine_ControlLoop Engine_ControlLoop;
//

Engine_Window *InitialiseWindow(int windowWidth, int windowHeight);

Engine_ControlLoop *InitialiseControlLoop(Engine_Window* engineWindow);

#endif //Engine_Initialise_H