#include <Engine/Engine_Math.h>
#include <Engine/Engine_Coordinates.h>
#include <math.h>


float Math_InterpolationLinear()
{

};

void Math_Swap(float* num1, float* num2)
{
    float temp = *num1;
    *num1 = *num2;
    *num2 = temp;
};

float Math_Clampfloat(float velocity, float low, float high)
{
    return fmin(fmax(velocity, low), high);
};


Vector2 Math_ClampVector2(Vector2 velocity, Vector2 low, Vector2 high)
{
    return (Vector2){Math_Clampfloat(velocity.x, low.x, high.x), Math_Clampfloat(velocity.y, low.y, high.y)};
};