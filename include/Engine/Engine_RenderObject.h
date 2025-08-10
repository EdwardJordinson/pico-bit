#ifndef Engine_RenderObject_H
#define Engine_RenderObject_H

//Forward declares
//

enum RenderObjectType
{
    NILL,
    SHAPE,
    TEXT
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
    enum RenderObjectType RenderObjectType;
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