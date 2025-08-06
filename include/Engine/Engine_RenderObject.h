#ifndef Engine_RenderObject_H
#define Engine_RenderObject_H

//Forward declares
//

typedef struct Engine_RenderObject
{
    float PositionX, PositionY;
    float Width, Height;
    int Red, Green, Blue, Alpha;

} Engine_RenderObject;


void RenderObject_Set(Engine_RenderObject* renderObject);

void RenderObject_Update();


#endif //Engine_RenderObject_H