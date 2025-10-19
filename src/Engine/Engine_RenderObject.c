#include <Engine/Engine_RenderObject.h>



Engine_RenderObject RenderObject_Initialise()
{
	return (Engine_RenderObject){
		.RenderType = 0,
		.GetData = RenderObject_GetData
		};
};

void RenderObject_SetDefault(Engine_RenderObject* renderObject)
{
    renderObject->RenderType = 0;
    renderObject->PositionX = 0.0; renderObject->PositionY = 0.0;
    renderObject->Red = 0.0; renderObject->Green = 0.0; renderObject->Blue = 0.0; renderObject->Alpha = 0.0;

    renderObject->GetData = RenderObject_GetData;
    
};

void RenderObject_SetConfiguration(Engine_RenderObject* renderObject, Engine_RenderObject configObject)
{
    *renderObject = configObject;
};

void* RenderObject_GetData(Engine_RenderObject* renderObject)
{
	switch(renderObject->RenderType)
	{
	case 1:
		return &renderObject->Data.SquareRender;
		break;
	case 2:
		return &renderObject->Data.CircleRender;
		break;
	case 3:
		return &renderObject->Data.PolygonRender;
		break;
	case 4:
		return &renderObject->Data.TextRender;
		break;
	}

};

void RenderObject_SetPosition(Engine_RenderObject* object, float xPosition, float yPosition)
{
    object->PositionX = xPosition;
    object->PositionY = yPosition;
};

void RenderObject_SetShape(Engine_RenderObject* object, float width, float height)
{
    object->Data.SquareRender.Width = width;
    object->Data.SquareRender.Height = height;
};

void RenderObject_SetColour(Engine_RenderObject* object, int red, int green, int blue, int alpha)
{
    object->Red = red;
    object->Green = green;
    object->Blue = blue;
    object->Alpha = alpha;
};

void RenderObject_Update(Engine_RenderObject* renderObject)
{

};

//These need their own C script
void RenderObject_SetShapeData(Engine_RenderObject* renderObject, float width, float height)
{
    renderObject->RenderType = 1;
    renderObject->Data.SquareRender.Width = width;
    renderObject->Data.SquareRender.Height = height;
};

void RenderObject_SetTextData(Engine_RenderObject* renderObject, float width, float height, char* text)
{
    renderObject->RenderType = 2;
    renderObject->Data.TextRender.Width = width;
    renderObject->Data.TextRender.Height = height;
    *renderObject->Data.TextRender.Text = *text;
};