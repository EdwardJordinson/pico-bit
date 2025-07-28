#ifndef Engine_Vector2_H
#define Engine_Vector2_H


typedef struct Vector2 Vector2;
struct Vector2
{
    float x, y;
};

typedef struct Vector2Type
{
    Vector2 (*Create)(float, float);
} Vector2Type;

extern Vector2Type VECTOR2;


void Vector2Type_Initialise(Vector2Type* vector2Type);

Vector2 Vector2_Initialise(float x, float y);

Vector2 Vector2_VectorAdd(Vector2 vector1, Vector2 vector2);

Vector2 Vector2_Subtract(Vector2 vector1, Vector2 vector2);

Vector2 Vector2_ScalarAdd(float scalar, Vector2 vector);

Vector2 Vector2_ScalarMuliply(float scalar, Vector2 vector);

Vector2 Vector2_ScalarDivide(float scalar, Vector2 vector2);

float Vector2_Length(Vector2 vector);

Vector2 Vector2_Normailised(Vector2 vector);

#endif //Engine_Vector2_H