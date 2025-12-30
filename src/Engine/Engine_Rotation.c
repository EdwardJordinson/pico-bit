#include <Engine/Engine_Coordinates.h>
#include <math.h>


Engine_Rotation Rotation_Initialise()
{
    
};

Engine_Rotation Rotation_SinCos(float rotation)
{
    return (Engine_Rotation){sinf(rotation), cosf(rotation)};
};