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


void RenderObject_Initialise();
void RenderObject_Configure(Engine_RenderObject* renderObject);
void RenderObject_SetPosition(Engine_RenderObject* renderObject, float xPosition, float yPosition);
void RenderObject_SetShape(Engine_RenderObject* renderObject, float width, float height);
void RenderObject_SetColour(Engine_RenderObject* renderObject, int red, int green, int blue, int alpha);
void RenderObject_Setup(Engine_RenderObject* renderObject, float xPosition, float yPosition);
void RenderObject_Update(Engine_RenderObject* objerenderObjectct);


#endif //Engine_RenderObject_H