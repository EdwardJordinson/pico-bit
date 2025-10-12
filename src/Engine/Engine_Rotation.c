#include <Engine/Engine_Coordinates.h>
#include <math.h>


Engine_Rotation Rotation_Initialise()
{
    
};

Engine_Rotation Rotation_SinCos(float rotation)
{
    //Engine_Rotation newRotation;
    //newRotation.cos = cosf(rotation);
    //newRotation.sin = sinf(rotation);
    return (Engine_Rotation){sinf(rotation), cosf(rotation)};
};