#include <Engine/Engine_Coordinates.h>
#include <Engine/Engine_Math.h>


Engine_Matrix3x2 Matrix3x2_Inititialise()
{
    return (Engine_Matrix3x2){(Engine_Matrix2x2)Matrix2x2_Inititialise(), Vector2_Initialise()};
};

void Matrix3x2_SetMatrix3x2(Engine_Matrix3x2* matrix1, Engine_Matrix3x2 matrix2)
{
    *matrix1 = matrix2;
};

void Matrix3x2_SetPosition(Engine_Matrix3x2* srcMatrix, Vector2 vector)
{
    srcMatrix->Position = vector;
};

void Matrix3x2_SetRotation(Engine_Matrix3x2* srcMatrix, float radians)
{
    
};

void Matrix3x2_SetScale(Engine_Matrix3x2* srcMatrix, Vector2 scale)
{

};

Engine_Matrix3x2 Matrix3x2_TransformVector(Engine_Matrix3x2 matrix1, Vector2 vectorPosition)
{

};

Engine_Matrix3x2 Matrix3x2_TranslationMatrix(Engine_Matrix3x2 matrix1, Engine_Matrix3x2 matrix2)
{

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

Engine_Matrix3x2 Matrix3x2_TSR(Vector2 position, Vector2 scale, float radians)
{   
    Engine_Matrix3x2 newMatrix;


    //return (Engine_Matrix3x2){(Engine_Matrix)Matrix_Rotation2x2(radians), (Vector2)Vector2_Initialise(0.0,0.0)};
};

Engine_Matrix3x2 Matrix3x2_MultiplyMatrix3x2(Engine_Matrix3x2 matrix1, Engine_Matrix3x2 matrix2)
{
    return (Engine_Matrix3x2){Matrix2x2_MultiplyMatrix2x2(matrix1.RotationMatrix, matrix2.RotationMatrix), Vector2_MultiplyMatrix2x2(matrix1.RotationMatrix, matrix2.Position)};
};