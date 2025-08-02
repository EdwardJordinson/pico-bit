#ifndef Engine_Initialise_H
#define Engine_Initialise_H

#include <stddef.h>

//Forward declares
typedef struct Engine_Main Engine_Main;
//


void Initialise_EngineMemory(Engine_Main** engine);

void Initialise_SDL();

void Initialise_Systems(Engine_Main* engine);

void Initialise_ReadEFD();

void Initialise_EFDConfigure(Engine_Main* engine);

void Initialise_Game(Engine_Main* engine);


#endif //Engine_Initialise_H