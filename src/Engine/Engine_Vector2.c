#include <Engine/Engine_Vector2.h>
#include <Engine/Engine_Globals.h>
#include <math.h>


Vector2 Vector2_Initialise(float x, float y)
{
    return (Vector2){x, y};
};

Vector2 Vector2_VectorAdd(Vector2* vector1, Vector2* vector2)
{
    return (Vector2){vector1->x + vector2->x, vector1->y + vector2->y};
};

Vector2 Vector2_Subtract(Vector2* vector1, Vector2* vector2)
{
    return (Vector2){vector1->x - vector2->x, vector1->y - vector2->y};
};

Vector2 Vector2_ScalarAdd(float scalar, Vector2* vector)
{
    return (Vector2){scalar+vector->x, scalar+vector->y};
};

Vector2 Vector2_ScalarMuliply(float scalar, Vector2* vector)
{
    return (Vector2){scalar*vector->x, scalar*vector->y};
};

Vector2 Vector2_ScalarDivide(float scalar, Vector2* vector2)
{
    return (Vector2){vector2->x/scalar, vector2->y/scalar};
};

float Vector2_Length(Vector2* vector)
{
    return (float)sqrtf(vector->x * vector->x + vector->y * vector->y);
};

float Vector2_LengthSquared(Vector2* vector)
{
    return (float)(vector->x * vector->x + vector->y * vector->y);
};

Vector2 Vector2_Normailised(Vector2* vector)
{
    return Vector2_ScalarDivide(Vector2_Length(vector), vector);
};