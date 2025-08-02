#ifndef Engine_Corrdinates_H
#define Engine_Corrdinates_H

//Forward declares
//

//#######################################################//
// -------------------Rotation-------------------------- //
typedef struct Engine_Rotation
{
    float sin, cos;
} Engine_Rotation;


Engine_Rotation Rotation_SinCos(float rotation);


//#######################################################//
// -------------------Vector2--------------------------- //
typedef struct Vector2
{
    float x, y;
} Vector2;

/*
typedef struct Vector2_TEST
{
    float *x,*y;
    float v[2];

    void (*Add)(struct Vector2_TEST*,struct Vector2_TEST);
    void (*Sub)(struct Vector2_TEST*,struct Vector2_TEST);

} Vector2_TEST;
*/

Vector2 Vector2_Initialise(float x, float y);
Vector2 Vector2_VectorAdd(Vector2 vector1, Vector2 vector2);
Vector2 Vector2_VectorSubtract(Vector2 vector1, Vector2 vector2);
Vector2 Vector2_VectorMultiply(Vector2 vector1, Vector2 vector2);
Vector2 Vector2_ScalarAdd(float scalar, Vector2 vector);
Vector2 Vector2_ScalarMuliply(float scalar, Vector2 vector);
Vector2 Vector2_ScalarDivide(float scalar, Vector2 vector2);
Vector2 Vector2_Rotate(Vector2 vector, float radians);
Vector2 Vector2_Skew(Vector2 vector);
Vector2 Vector2_RotationMultiply(Engine_Rotation rotation, Vector2 vector);
Vector2 Vector2_NormalVectorFromAngle(float radaians);
float Vector2_Length(Vector2 vector);
Vector2 Vector_ABS(Vector2 vector);
Vector2 Vector2_Normailised(Vector2 vector);
float Vector2_DotProduct(Vector2 vector1, Vector2 vector2);
float Vector2_CrossProduct(Vector2 vector1, Vector2 vector2);


//#######################################################//
// -------------------HalfSpace------------------------- //
typedef struct HalfSpace
{
    Vector2 Normal;
    float Distance;
} HalfSpace;


HalfSpace HalfSpace_NewPosition(Vector2 normal, Vector2 position);
HalfSpace HalfSpace_NewDistance(Vector2 normal, float distance);


//#######################################################//
// -------------------Matrix2x2------------------------- //
typedef struct Engine_Matrix2x2
{
    Vector2 X;
    Vector2 Y;
} Engine_Matrix2x2;


Engine_Matrix2x2 Matrix2x2_Inititialise();
Engine_Matrix2x2 Matrix2x2_Rotation(float radians);
Vector2 Matrix2x2_VectorMultiply(Engine_Matrix2x2 matrix, Vector2 vector);
Engine_Matrix2x2 Matrix2x2_MatrixMultiply(Engine_Matrix2x2 matrix1, Engine_Matrix2x2 matrix2);


//#######################################################//
// -------------------Matrix3x2------------------------- //
typedef struct Engine_Matrix3x2
{
    Engine_Matrix2x2 RotationMatrix;
    Vector2 Position;

} Engine_Matrix3x2;


Engine_Matrix3x2 Matrix3x2_Inititialise();
Engine_Matrix3x2 Matrix3x2_TranslationVector(Vector2 vector);
Engine_Matrix3x2 Matrix3x2_TranslationXY(float x, float y);
Engine_Matrix3x2 Matrix3x2_Rotate(float radians);
Engine_Matrix3x2 Matrix3x2_TSR(float radians);


#endif //Engine_Corrdinates_H