#include <Engine/Engine_CollisionShape.h>
#include <Engine/Engine_Physics.h>
#include <math.h>




Engine_Circle Circle_Initialise()
{
    return (Engine_Circle){1.0f};
};

void Circle_SetDefault(Engine_Circle* circle)
{
    circle->radius = 50.0f;
};

void Circle_SetConfiguration(Engine_Circle* circle, Engine_Circle configCircle)
{
    *circle = configCircle;
};

void Circle_SetRadius(Engine_Circle* circle, float rad)
{
    circle->radius = rad;
};

void Circle_SetTransform(Engine_Circle* circle, Engine_Matrix3x2 bodyTransform)
{

};