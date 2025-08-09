#include <Engine/Engine_Coordinates.h>


Engine_Matrix3x2 Matrix3x2_Inititialise()
{
    return (Engine_Matrix3x2){(Engine_Matrix2x2)Matrix2x2_Inititialise(), Vector2_Initialise()};
};

Engine_Matrix3x2 Matrix3x2_TranslationXY(float x, float y)
{
    return Matrix3x2_TranslationVector((Vector2){x,y});
};

Engine_Matrix3x2 Matrix3x2_TranslationVector(Vector2 vector)
{
    return (Engine_Matrix3x2){(Engine_Matrix2x2)Matrix2x2_Inititialise(), vector};
};

Engine_Matrix3x2 Matrix3x2_Rotate(float radians)
{
    return (Engine_Matrix3x2){(Engine_Matrix2x2)Matrix2x2_Rotation(radians), Vector2_Initialise()};
};

Engine_Matrix3x2 Matrix3x2_TSR(float radians)
{
    //return (Engine_Matrix3x2){(Engine_Matrix)Matrix_Rotation2x2(radians), (Vector2)Vector2_Initialise(0.0,0.0)};
};