#ifndef Engine_Loop_H
#define Engine_Loop_H

#include <stdint.h>
#include <stdbool.h>

//Forward declares
typedef struct Engine_Loop Engine_Loop;
//

void RunLoop(Engine_Loop** engineLoop);

void PrintConsole(bool* firstFrame, int frameRate, uint32_t frameDelta);

#endif //Engine_Loop_H