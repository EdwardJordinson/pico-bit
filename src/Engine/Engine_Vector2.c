#include <Engine/Engine_Coordinates.h>
#include <math.h>


Vector2 Vector2_Initialise()
{
    return (Vector2){0.0,0.0};
};

Vector2 Vector2_SetXY(Vector2* srcVector, float x, float y)
{
    srcVector->x = x; srcVector->y = y;
    return *srcVector; 
};

Vector2 Vector2_SetVector(Vector2* srcVector, Vector2 vector)
{
    srcVector->x = vector.x; srcVector->y = vector.y;
    return *srcVector;
};

Vector2 Vector2_AddScalar(Vector2 vector, float scale)
{
    return (Vector2){vector.x + scale, vector.y + scale};
};

Vector2 Vector2_AddXY(Vector2 vector, float x, float y)
{
    return (Vector2){vector.x + x, vector.y + y};
};

Vector2 Vector2_AddVector(Vector2 vector1, Vector2 vector2)
{
    return Vector2_AddXY(vector1, vector2.x, vector2.y);
};

Vector2 Vector2_SubtractScalar(Vector2 vector, float scale)
{
    return (Vector2){vector.x - scale, vector.y - scale};
};

Vector2 Vector2_SubtractXY(Vector2 vector, float x, float y)
{
    
    return (Vector2){vector.x - x, vector.y - y};
};

Vector2 Vector2_SubtractVector(Vector2 vector1, Vector2 vector2)
{
    return Vector2_SubtractXY(vector1, vector2.x, vector2.y);
};

Vector2 Vector2_MuliplyScalar(Vector2 vector, float scale)
{
    return (Vector2){vector.x * scale, vector.y * scale};
};

Vector2 Vector2_MultiplyXY(Vector2 vector, float x, float y)
{
    return (Vector2){vector.x * x, vector.y * y};
};

Vector2 Vector2_MultiplyVector(Vector2 vector1, Vector2 vector2)
{
    return Vector2_MultiplyXY(vector1, vector2.x, vector2.y);
};

Vector2 Vector2_DivideScalar(Vector2 vector, float scale)
{
    return (Vector2){vector.x/scale, vector.y/scale};
};

Vector2 Vector2_DivideXY(Vector2 vector, float x, float y)
{
    return (Vector2){vector.x/x, vector.y/y};
};

Vector2 Vector2_DivideVector(Vector2 vector1, Vector2 vector2)
{
    return Vector2_DivideXY(vector1, vector2.x, vector2.y);
};


//NOT DONE BELOW

Vector2 Vector2_Rotate(Vector2 vector, float radians)
{
    float sine = sinf(radians);
    float cos = cosf(radians);
    return (Vector2){cos * vector.x - sine  * vector.y, sine * vector.x + cos * vector.y};
};

Vector2 Vector2_Skew(Vector2 vector)
{
    return(Vector2){-vector.y,vector.x};
};

Vector2 Vector2_RotationMultiply(Vector2 vector, Engine_Rotation rotation)
{
    return(Vector2){rotation.cos * vector.x - rotation.sin * vector.y, rotation.sin * vector.x + rotation.cos * vector.y};
};

Vector2 Vector2_NormalAngleRadians(float radians)
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

Vector2 Vector2_ABS(Vector2 vector)
{
    return (Vector2){abs(vector.x), abs(vector.y)};
};

Vector2 Vector2_Min(Vector2 vector1, Vector2 vector2)
{

};

Vector2 Vector2_Max(Vector2 vector1, Vector2 vector2)
{
    
};

Vector2 Vector2_Normailised(Vector2 vector)
{
    return Vector2_DivideScalar(vector, Vector2_Length(vector));
};

float Vector2_DotProduct(Vector2 vector1, Vector2 vector2)
{
    return (float)(vector1.x*vector2.x + vector1.y*vector2.y);
};

float Vector2_CrossProduct(Vector2 vector1, Vector2 vector2)
{
    return (float)(vector1.x*vector2.y - vector1.y*vector2.x); 
};


//FIND NEW HOME BELOW

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
