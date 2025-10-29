#ifndef Engine_Math_H
#define Engine_Math_H

//Forward declares
typedef struct Vector2 Vector2;
//


float Math_InterpolationLinear();
void Math_Swap(float* num1, float* num2);
float Math_Clampfloat(float velocity, float low, float high);
Vector2 Math_ClampVector2(Vector2 vector, Vector2 low, Vector2 high);

#endif //Engine_Math_H