#include <Engine/Engine_Matrix.h>
#include <math.h>


Engine_Matrix Matrix_Inititialise2x2()
{
    return (Engine_Matrix){(Vector2){1.0,0.0},(Vector2){0.0,1.0}};
};

Engine_Matrix Matrix_Rotation2x2(float radians)
{
    float cos = cosf(radians);
    float sin = sinf(radians);
    return (Engine_Matrix){(Vector2){cos, -sin},(Vector2){sin,cos}};
};

Vector2 Matrix_VectorMultiply2x2(Engine_Matrix matrix, Vector2 vector)
{
    return (Vector2){matrix.X.x * vector.x + matrix.Y.x * vector.y, matrix.X.y * vector.x + matrix.Y.y * vector.y};
};

Engine_Matrix Matrix_MatrixMultiply2x2(Engine_Matrix matrix1, Engine_Matrix matrix2)
{
    return (Engine_Matrix){Matrix_VectorMultiply2x2(matrix1, matrix2.X), Matrix_VectorMultiply2x2(matrix1, matrix2.Y)};
};

//3 by 2 Matrix
Engine_Matrix3x2 Matrix_Inititialise3x2()
{
    return (Engine_Matrix3x2){(Engine_Matrix)Matrix_Inititialise2x2(), (Vector2)Vector2_Initialise(0.0,0.0)};
};

Engine_Matrix3x2 Matrix_Translation3x2Vector(Vector2 vector)
{
    return (Engine_Matrix3x2){(Engine_Matrix)Matrix_Inititialise2x2(), vector};
};

Engine_Matrix3x2 Matrix_Translation3x2XY(float x, float y)
{
    return Matrix_Translation3x2Vector((Vector2){x,y});
};

Engine_Matrix3x2 Matrix_Rotate3x2(float radians)
{
    return (Engine_Matrix3x2){(Engine_Matrix)Matrix_Rotation2x2(radians), (Vector2)Vector2_Initialise(0.0,0.0)};
};

Engine_Matrix3x2 Matrix_TSR3x2(float radians)
{
    //return (Engine_Matrix3x2){(Engine_Matrix)Matrix_Rotation2x2(radians), (Vector2)Vector2_Initialise(0.0,0.0)};
};