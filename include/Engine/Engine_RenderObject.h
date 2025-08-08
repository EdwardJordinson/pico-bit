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
void RenderObject_Configure(Engine_RenderObject* object);
void RenderObject_SetPosition(Engine_RenderObject* object, float xPosition, float yPosition);
void RenderObject_SetShape(Engine_RenderObject* object, float width, float height);
void RenderObject_SetColour(Engine_RenderObject* object, int red, int green, int blue, int alpha);
void RenderObject_Setup(Engine_RenderObject* object, float xPosition, float yPosition);
void RenderObject_Update(Engine_RenderObject* object);


#endif //Engine_RenderObject_H