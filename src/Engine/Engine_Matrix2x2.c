#include <Engine/Engine_Coordinates.h>
#include <math.h>


Engine_Matrix2x2 Matrix2x2_Inititialise()
{
    return (Engine_Matrix2x2){(Vector2){1.0,0.0},(Vector2){0.0,1.0}}; // Is also the matrix identity
};

Engine_Matrix2x2 Matrix2x2_MultiplyMatrix2x2(Engine_Matrix2x2 matrix1, Engine_Matrix2x2 matrix2)
{
    return (Engine_Matrix2x2){Vector2_MultiplyMatrix2x2(matrix1, matrix2.X), Vector2_MultiplyMatrix2x2(matrix1, matrix2.Y)};
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