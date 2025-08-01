#ifndef Engine_Vector2_H
#define Engine_Vector2_H


typedef struct Vector2
{
    float x, y;
} Vector2;

typedef struct BasisVector2
{
    Vector2 RIGHT;
    Vector2 UP;
    Vector2 LEFT;
    Vector2 DOWN;
} BasisVector2;

extern BasisVector2 BASISVECTOR2;


void Vector2_InitialiseBasis();

Vector2 Vector2_Initialise(float x, float y);

Vector2 Vector2_VectorAdd(Vector2 vector1, Vector2 vector2);

Vector2 Vector2_VectorSubtract(Vector2 vector1, Vector2 vector2);

Vector2 Vector2_VectorMultiply(Vector2 vector1, Vector2 vector2);

Vector2 Vector2_ScalarAdd(float scalar, Vector2 vector);

Vector2 Vector2_ScalarMuliply(float scalar, Vector2 vector);

Vector2 Vector2_ScalarDivide(float scalar, Vector2 vector2);

float Vector2_Length(Vector2 vector);

Vector2 Vector_ABS(Vector2 vector);

Vector2 Vector2_Normailised(Vector2 vector);

float Vector2_DotProduct(Vector2 vector1, Vector2 vector2);

float Vector2_CrossProduct(Vector2 vector1, Vector2 vector2);

#endif //Engine_Vector2_H