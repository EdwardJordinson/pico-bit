#include <Engine/Engine_Coordinates.h>
#include <math.h>


Engine_Rotation Math_SinCos(float rotation)
{
    Engine_Rotation newRotation;
    newRotation.cos = cosf(rotation);
    newRotation.sin = sinf(rotation);
    return newRotation;
};