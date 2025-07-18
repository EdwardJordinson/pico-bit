#ifndef Engine_Initialise_H
#define Engine_Initialise_H

typedef struct Engine_Window Engine_Window;

Engine_Window *InitialiseWindow(int windowWidth, int windowHeight);

void ShutdownWindow(Engine_Window *engineWindow);

#endif