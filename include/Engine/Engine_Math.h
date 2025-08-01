#ifndef Engine_Math_H
#define Engine_Math_H


typedef struct Rotation
{
    float sin;
    float cos;
} Rotation;


float Math_InterpolationLinear();

void Math_Swap(float* num1, float* num2);

Rotation Math_SinCos(float rotation);


#endif //Engine_Math_H