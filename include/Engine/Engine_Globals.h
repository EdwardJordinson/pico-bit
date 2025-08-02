#ifndef Engine_Globals_H
#define Engine_Globals_H

//Forward declares
typedef struct Engine_MainLoop Engine_MainLoop;
//

typedef struct Engine_Main
{
    Engine_MainLoop* MainLoop;

} Engine_Main;


extern Engine_Main* Engine;


#endif //Engine_Globals_H