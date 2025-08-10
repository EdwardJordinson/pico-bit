#include <Engine/Engine_RenderObject.h>



void RenderObject_Initialise()
{

};

void RenderObject_Configure(Engine_RenderObject* object)
{
    object->RenderObjectType = 0;
    object->PositionX = 0.0; object->PositionY = 0.0;
    object->RenderData.ShapeData.Width = 0.0; object->RenderData.ShapeData.Height = 0.0;
    object->Red = 0.0; object->Green = 0.0; object->Blue = 0.0; object->Alpha = 0.0;
};

void RenderObject_SetPosition(Engine_RenderObject* object, float xPosition, float yPosition)
{
    object->PositionX = xPosition;
    object->PositionY = yPosition;
};

void RenderObject_SetShape(Engine_RenderObject* object, float width, float height)
{
    object->RenderData.ShapeData.Width = width;
    object->RenderData.ShapeData.Height = height;
};

void RenderObject_SetColour(Engine_RenderObject* object, int red, int green, int blue, int alpha)
{
    object->Red = red;
    object->Green = green;
    object->Blue = blue;
    object->Alpha = alpha;
};

void RenderObject_Setup(Engine_RenderObject* object, float xPosition, float yPosition)
{

};

void RenderObject_Update(Engine_RenderObject* renderObject)
{

};

void RenderObject_SetShapeData(Engine_RenderObject* renderObject, float width, float height)
{
    renderObject->RenderObjectType = 1;
    renderObject->RenderData.ShapeData.Width = width;
    renderObject->RenderData.ShapeData.Height = height;
};

void RenderObject_SetTextData(Engine_RenderObject* renderObject, float width, float height, char* text)
{
    renderObject->RenderObjectType = 2;
    renderObject->RenderData.TextData.Width = width;
    renderObject->RenderData.TextData.Height = height;
    *renderObject->RenderData.TextData.Text = *text;
};