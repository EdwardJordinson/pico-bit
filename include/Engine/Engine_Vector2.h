#ifndef Engine_Vector2_H
#define Engine_Vector2_H


typedef struct Rotation Rotation;

typedef struct Vector2
{
    float x, y;
} Vector2;

typedef struct HalfSpace
{
    Vector2 Normal;
    float Distance;
} HalfSpace;

typedef struct BasisVector2
{
    Vector2 RIGHT;
    Vector2 UP;
    Vector2 LEFT;
    Vector2 DOWN;
} BasisVector2;

extern BasisVector2 BASISVECTOR2;

typedef struct Vector2_TEST
{
    float *x,*y;
    float v[2];

    void (*Add)(struct Vector2_TEST*,struct Vector2_TEST);
    void (*Sub)(struct Vector2_TEST*,struct Vector2_TEST);

} Vector2_TEST;



void Vector2_InitialiseBasis();

Vector2 Vector2_Initialise(float x, float y);

Vector2 Vector2_New();

HalfSpace Vector2_HalfSpacePos(Vector2 normal, Vector2 position);

HalfSpace Vector2_HalfSpaceDist(Vector2 normal, float distance);

Vector2 Vector2_VectorAdd(Vector2 vector1, Vector2 vector2);

Vector2 Vector2_VectorSubtract(Vector2 vector1, Vector2 vector2);

Vector2 Vector2_VectorMultiply(Vector2 vector1, Vector2 vector2);

Vector2 Vector2_ScalarAdd(float scalar, Vector2 vector);

Vector2 Vector2_ScalarMuliply(float scalar, Vector2 vector);

Vector2 Vector2_ScalarDivide(float scalar, Vector2 vector2);

Vector2 Vector2_Rotate(Vector2 vector, float radians);

Vector2 Vector2_Skew(Vector2 vector);

Vector2 Vector2_RotationMultiply(Rotation rotation, Vector2 vector);

Vector2 Vector2_NormalVectorFromAngle(float radaians);

float Vector2_Length(Vector2 vector);

Vector2 Vector_ABS(Vector2 vector);

Vector2 Vector2_Normailised(Vector2 vector);

float Vector2_DotProduct(Vector2 vector1, Vector2 vector2);

float Vector2_CrossProduct(Vector2 vector1, Vector2 vector2);

#endif //Engine_Vector2_H