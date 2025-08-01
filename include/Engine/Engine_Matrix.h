#ifndef Engine_Matrix_H
#define Engine_Matrix_H

#include <Engine/Engine_Vector2.h>
//Forward declares
//

typedef struct Engine_Matrix
{
    Vector2 X;
    Vector2 Y;
} Engine_Matrix;

typedef struct Engine_Matrix3x2
{
    Engine_Matrix RotationMatrix;
    Vector2 Position;

} Engine_Matrix3x2;


Engine_Matrix Matrix_Inititialise2x2();

Engine_Matrix Matrix_Rotation2x2(float radians);

Vector2 Matrix_VectorMultiply2x2(Engine_Matrix matrix, Vector2 vector);

Engine_Matrix Matrix_MatrixMultiply2x2(Engine_Matrix matrix1, Engine_Matrix matrix2);


Engine_Matrix3x2 Matrix_Inititialise3x2();

Engine_Matrix3x2 Matrix_Translation3x2Vector(Vector2 vector);

Engine_Matrix3x2 Matrix_Translation3x2XY(float x, float y);

Engine_Matrix3x2 Matrix_Rotate3x2(float radians);

Engine_Matrix3x2 Matrix_TSR3x2(float radians);

#endif //Engine_Matrix_H