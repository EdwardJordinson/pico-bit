#include <Engine/Engine_Coordinates.h>
#include <math.h>


Engine_Rotation Rotation_Initialise()
{
    
};

Engine_Rotation Rotation_SinCos(float rotation)
{
    Engine_Rotation newRotation;
    newRotation.cos = cosf(rotation);
    newRotation.sin = sinf(rotation);
    return newRotation;
};

Vector2 Rotation_MultiplyVector(Engine_Rotation radians, Vector2 vector)
{

};