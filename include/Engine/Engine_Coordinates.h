#ifndef Engine_Corrdinates_H
#define Engine_Corrdinates_H

//Forward declares
typedef struct Vector2 Vector2;
typedef struct Engine_Matrix2x2 Engine_Matrix2x2;
typedef struct Engine_Matrix3x2 Engine_Matrix3x2;
//

//#######################################################//
// -------------------Rotation-------------------------- //
typedef struct Engine_Rotation
{
    float sin, cos;
} Engine_Rotation;


Engine_Rotation Rotation_Initialise();
Engine_Rotation Rotation_SinCos(float rotation);


//#######################################################//
// -------------------Vector2--------------------------- //
typedef struct Vector2
{
    float x, y;
} Vector2;


Vector2 Vector2_Initialise();
Vector2 Vector2_SetXY(Vector2* srcVector, float x, float y);
Vector2 Vector2_SetVector(Vector2* srcVector, Vector2 vector);
Vector2 Vector2_AddScalar(Vector2 vector, float scale);
Vector2 Vector2_AddXY(Vector2 vector, float x, float y);
Vector2 Vector2_AddVector(Vector2 vector2, Vector2 vector1);
Vector2 Vector2_SubtractScalar(Vector2 vector, float scale);
Vector2 Vector2_SubtractXY(Vector2 vector, float x, float y);
Vector2 Vector2_SubtractVector(Vector2 vector1, Vector2 vector2);
Vector2 Vector2_MuliplyScalar(Vector2 vector, float scale);
Vector2 Vector2_MultiplyXY(Vector2 vector, float x, float y);
Vector2 Vector2_MultiplyVector(Vector2 vector1, Vector2 vector2);
Vector2 Vector2_MultiplyRotation(Engine_Rotation radians, Vector2 vector);
Vector2 Vector2_MultiplyMatrix2x2(Engine_Matrix2x2 matrix, Vector2 vector);
Vector2 Vector2_MultiplyMatrix3x2(Engine_Matrix3x2 matrix, Vector2 vector);
Vector2 Vector2_DivideScalar(Vector2 vector, float scale);
Vector2 Vector2_DivideXY(Vector2 vector, float x, float y);
Vector2 Vector2_DivideVector(Vector2 vector1, Vector2 vector2);
Vector2 Vector2_Rotate(Vector2 vector, float radians);
Vector2 Vector2_Skew(Vector2 vector);
Vector2 Vector2_RotationMultiply(Vector2 vector, Engine_Rotation rotation);
Vector2 Vector2_NormalAngleRadians(float radaians);
float Vector2_Length(Vector2 vector);
Vector2 Vector2_ABS(Vector2 vector);
Vector2 Vector2_Min(Vector2 vector1, Vector2 vector2);
Vector2 Vector2_Max(Vector2 vector1, Vector2 vector2);
Vector2 Vector2_Normailised(Vector2 vector);
float Vector2_DotProduct(Vector2 vector1, Vector2 vector2);
float Vector2_CrossProduct(Vector2 vector1, Vector2 vector2);


//#######################################################//
// -------------------Matrix2x2------------------------- //
typedef struct Engine_Matrix2x2
{
    Vector2 X;
    Vector2 Y;
} Engine_Matrix2x2;


Engine_Matrix2x2 Matrix2x2_Inititialise();
Engine_Matrix2x2 Matrix2x2_MultiplyMatrix2x2(Engine_Matrix2x2 matrix1, Engine_Matrix2x2 matrix2);
Engine_Matrix2x2 Matrix2x2_Rotation(float radians);
Engine_Matrix2x2 Matrix2x2_Scale(float xScale, float yScale);



//#######################################################//
// -------------------Matrix3x2------------------------- //
typedef struct Engine_Matrix3x2
{
    Engine_Matrix2x2 RotationMatrix;
    Vector2 Position;

} Engine_Matrix3x2;


Engine_Matrix3x2 Matrix3x2_Inititialise();
void Matrix3x2_SetTransform(Engine_Matrix3x2* matrix1, Engine_Matrix3x2 matrix2);
Engine_Matrix3x2 Matrix3x2_TransformVector(Engine_Matrix3x2 matrix1, Vector2 vectorPosition);
Engine_Matrix3x2 Matrix3x2_TranslationMatrix(Engine_Matrix3x2 matrix1, Engine_Matrix3x2 matrix2);
Engine_Matrix3x2 Matrix3x2_TranslationXY(float x, float y);
Engine_Matrix3x2 Matrix3x2_TranslationVector(Vector2 vector);
Engine_Matrix3x2 Matrix3x2_Rotate(float radians);
Engine_Matrix3x2 Matrix3x2_TSR(Vector2 position, Vector2 scale, float radians);
Engine_Matrix3x2 Matrix3x2_MultiplyMatrix3x2(Engine_Matrix3x2 matrix1, Engine_Matrix3x2 matrix2);


//#######################################################//
// -------------------HalfSpace------------------------- //
typedef struct HalfSpace
{
    Vector2 Normal;
    float Distance;
} HalfSpace;


HalfSpace HalfSpace_NewPosition(Vector2 normal, Vector2 position);
HalfSpace HalfSpace_NewDistance(Vector2 normal, float distance);


#endif //Engine_Corrdinates_H