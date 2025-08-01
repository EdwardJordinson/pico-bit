#ifndef Engine_Physics_H
#define Engine_Physics_H

#include <Engine/Engine_Vector2.h>


typedef struct Engine_Manifold
{
    bool Hit;
    Vector2 HitSpot;
    float Depth;
    Vector2 Normal;

} Engine_Manifold;



#endif //Engine_Physics_H