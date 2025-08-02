#include <Engine/Engine_Coordinates.h>
#include <math.h>


Vector2 Vector2_Initialise(float x, float y)
{
    return (Vector2){x, y};
};

HalfSpace Vector2_HalfSpacePos(Vector2 normal, Vector2 position)
{
    HalfSpace newPlane;
    newPlane.Normal = normal;
    newPlane.Distance = Vector2_DotProduct(normal, position);
    return newPlane;
};

HalfSpace Vector2_HalfSpaceDist(Vector2 normal, float distance)
{
    HalfSpace newPlane;
    newPlane.Normal = normal;
    newPlane.Distance = distance;
    return newPlane;
};

Vector2 Vector2_VectorAdd(Vector2 vector1, Vector2 vector2)
{
    return (Vector2){vector1.x+vector2.x, vector1.y+vector2.y};
};

Vector2 Vector2_VectorSubtract(Vector2 vector1, Vector2 vector2)
{
    return (Vector2){vector1.x-vector2.x, vector1.y-vector2.y};
};

Vector2 Vector2_VectorMultiply(Vector2 vector1, Vector2 vector2)
{
    return (Vector2){vector1.x*vector2.x, vector1.y*vector2.y}; 
};

Vector2 Vector2_ScalarAdd(float scalar, Vector2 vector)
{
    return (Vector2){scalar+vector.x, scalar+vector.y};
};

Vector2 Vector2_ScalarMuliply(float scalar, Vector2 vector)
{
    return (Vector2){scalar*vector.x, scalar*vector.y};
};

Vector2 Vector2_ScalarDivide(float scalar, Vector2 vector2)
{
    return (Vector2){vector2.x/scalar, vector2.y/scalar};
};

Vector2 Vector2_Rotate(Vector2 vector, float radians)
{
    float sine = sinf(radians);
    float cos = cosf(radians);
    return (Vector2){cos * vector.x - sine  * vector.y, sine * vector.x + cos * vector.y};
};

Vector2 Vector2_Skew(Vector2 vector)
{
    return (Vector2){-vector.y,vector.x};
};

Vector2 Vector2_RotationMultiply(Engine_Rotation rotation, Vector2 vector)
{
    return(Vector2){rotation.cos * vector.x - rotation.sin * vector.y, rotation.sin * vector.x + rotation.cos * vector.y};
};

Vector2 Vector2_NormalVectorFromAngle(float radians)
{
    return (Vector2){cosf(radians), sinf(radians)};
};

float Vector2_Length(Vector2 vector)
{
    return (float)sqrtf(vector.x*vector.x + vector.y*vector.y);
};

float Vector2_LengthSquared(Vector2 vector)
{
    return (float)(vector.x*vector.x + vector.y*vector.y);
};

Vector2 Vector_ABS(Vector2 vector)
{
    return (Vector2){abs(vector.x), abs(vector.y)};
};

Vector2 Vector2_Normailised(Vector2 vector)
{
    return Vector2_ScalarDivide(Vector2_Length(vector), vector);
};

float Vector2_DotProduct(Vector2 vector1, Vector2 vector2)
{
    return (float)(vector1.x*vector2.x + vector1.y*vector2.y);
};

float Vector2_CrossProduct(Vector2 vector1, Vector2 vector2)
{
    return (float)(vector1.x*vector2.y - vector1.y*vector2.x); 
};