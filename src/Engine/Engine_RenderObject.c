#include <Engine/Engine_RenderObject.h>



void RenderObject_Initialise()
{

};

void RenderObject_Configure(Engine_RenderObject* object)
{
    object->PositionX = 0.0; object->PositionY = 0.0;
    object->Width = 0.0; object->Height = 0.0;
    object->Red = 0.0; object->Green = 0.0; object->Blue = 0.0; object->Alpha = 0.0;
};

void RenderObject_SetPosition(Engine_RenderObject* object, float xPosition, float yPosition)
{
    object->PositionX = 0.0;
    object->PositionY = 0.0;
};

void RenderObject_SetShape(Engine_RenderObject* object, float width, float height)
{
    object->Width = 0.0;
    object->Height = 0.0;
};

void RenderObject_SetColour(Engine_RenderObject* object, int red, int green, int blue, int alpha)
{
    object->Red = 0.0;
    object->Green = 0.0;
    object->Blue = 0.0;
    object->Alpha = 0.0;
};

void RenderObject_Setup(Engine_RenderObject* object, float xPosition, float yPosition)
{

};

void RenderObject_Update(Engine_RenderObject* renderObject)
{

};