#ifndef Engine_RenderObject_H
#define Engine_RenderObject_H

/*
Render objects are render loaded data, this is all loaded data that will be displayed on screen.
Render types are limited and implementation of each is very underdeveloped, as there has not been a need for complex render objects yet.
For now, there is only two (shape & text).
Text handles fonts and text on screen, and shapes are just squares for now.
*/

//Forward declares
//

enum RenderType
{
    r_NILL,
    r_SHAPE,
    r_TEXT
 };

typedef struct RenderObject_Shape
{
    float Width, Height;

} RenderObject_Shape;

typedef struct RenderObject_Text
{
    float Width, Height;
    char Text[32];
} RenderObject_Text;


union RenderData
{
    RenderObject_Shape ShapeData;
    RenderObject_Text TextData;

};

typedef struct Engine_RenderObject
{
    enum RenderType RenderType;
    float PositionX, PositionY;
    int Red, Green, Blue, Alpha;
    union RenderData RenderData;
    
    //float Width, Height;

} Engine_RenderObject;


void RenderObject_Initialise();
void RenderObject_Configure(Engine_RenderObject* renderObject);
void RenderObject_SetPosition(Engine_RenderObject* renderObject, float xPosition, float yPosition);
void RenderObject_SetShape(Engine_RenderObject* renderObject, float width, float height);
void RenderObject_SetColour(Engine_RenderObject* renderObject, int red, int green, int blue, int alpha);
void RenderObject_Setup(Engine_RenderObject* renderObject, float xPosition, float yPosition);
void RenderObject_Update(Engine_RenderObject* objerenderObjectct);

void RenderObject_SetShapeData(Engine_RenderObject* renderObject, float width, float height);
void RenderObject_SetTextData(Engine_RenderObject* renderObject, float width, float height, char* text);

#endif //Engine_RenderObject_H