#include <Engine/Engine_Math.h>
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

float Math_Clamp(float velocity, float low, float high)
{
    //v2 clamp(v2 v, v2 lo, v2 hi) { return v2(clamp(v.x, lo.x, hi.x), clamp(v.y, lo.y, hi.y)); }
};