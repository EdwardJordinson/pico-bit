#include <Engine/Engine_Coordinates.h>
#include <math.h>


Engine_Matrix2x2 Matrix2x2_Inititialise()
{
    return (Engine_Matrix2x2){(Vector2){1.0,0.0},(Vector2){0.0,1.0}}; // Is also the matrix identity
};

Vector2 Matrix2x2_MultiplyVector(Engine_Matrix2x2 matrix, Vector2 vector)
{
    return (Vector2){matrix.X.x * vector.x + matrix.Y.x * vector.y, matrix.X.y * vector.x + matrix.Y.y * vector.y};
};

Engine_Matrix2x2 Matrix2x2_MultiplyMatrix(Engine_Matrix2x2 matrix1, Engine_Matrix2x2 matrix2)
{
    return (Engine_Matrix2x2){Matrix2x2_MultiplyVector(matrix1, matrix2.X), Matrix2x2_MultiplyVector(matrix1, matrix2.Y)};
};

Engine_Matrix2x2 Matrix2x2_Rotation(float radians)
{
    float cos = cosf(radians);
    float sin = sinf(radians);
    return (Engine_Matrix2x2){(Vector2){cos, -sin},(Vector2){sin,cos}};
};

Engine_Matrix2x2 Matrix2x2_Scale(float xScale, float yScale)
{
    return (Engine_Matrix2x2){Vector2_MuliplyScalar((Vector2){1.0,0.0}, xScale), Vector2_MuliplyScalar((Vector2){0.0,1.0}, yScale)};
};