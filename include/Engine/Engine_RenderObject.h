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

//Need to make Render resources /render shapes/text

enum RenderType
{
    ro_NILL,
    ro_SQUARE,
    ro_CIRCLE,
    ro_POLYGON,
    ro_TEXT
};

typedef struct RenderObject_Square
{
    float Width, Height;

} RenderObject_Square;

typedef struct RenderObject_Circle
{
    float Radius;

} RenderObject_Circle;

typedef struct RenderObject_Polygon
{
    float Width, Height;

} RenderObject_Polygon;

typedef struct RenderObject_Text
{
    float Width, Height;
    char Text[32];
} RenderObject_Text;


union RenderData
{
    RenderObject_Square SquareRender;
    RenderObject_Circle CircleRender;
    RenderObject_Polygon PolygonRender;
    RenderObject_Text TextRender;

};

typedef struct Engine_RenderObject
{
    enum RenderType RenderType;
    union RenderData Data;
    float PositionX, PositionY;
    int Red, Green, Blue, Alpha;

    void* (*GetData)(struct Engine_RenderObject*);    

} Engine_RenderObject;


Engine_RenderObject RenderObject_Initialise();
void RenderObject_SetDefault(Engine_RenderObject* renderObject);
void RenderObject_SetConfiguration(Engine_RenderObject* renderObject, Engine_RenderObject configObject);
void* RenderObject_GetData(Engine_RenderObject* renderObject);

void RenderObject_SetPosition(Engine_RenderObject* renderObject, float xPosition, float yPosition);
void RenderObject_SetShape(Engine_RenderObject* renderObject, float width, float height);
void RenderObject_SetColour(Engine_RenderObject* renderObject, int red, int green, int blue, int alpha);
void RenderObject_Update(Engine_RenderObject* renderObject);

void RenderObject_SetShapeData(Engine_RenderObject* renderObject, float width, float height);
void RenderObject_SetTextData(Engine_RenderObject* renderObject, float width, float height, char* text);

#endif //Engine_RenderObject_H