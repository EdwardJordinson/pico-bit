#ifndef Engine_Initialise_H
#define Engine_Initialise_H

//Forward declares
typedef struct Engine_Globals Engine_Globals;
typedef struct Engine_Window Engine_Window;
typedef struct Engine_Loop Engine_Loop;
//

void InitialiseEngine(Engine_Globals** engineGlobals);

void InitialiseWindow(Engine_Window** engineWindow);

void InitialiseLoop(Engine_Loop** engineLoop);

#endif //Engine_Initialise_H