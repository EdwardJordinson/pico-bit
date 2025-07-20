#ifndef Engine_Loop_H
#define Engine_Loop_H

#include <stdint.h>
#include <stdbool.h>

//Forward declares
//

void RunLoop();

void UpdateLoop();

void DrawLoop();

void CreateTarget(int posX, int posY);

void PrintConsole(bool* firstFrame, int frameRate, uint32_t frameDelta);

#endif //Engine_Loop_H