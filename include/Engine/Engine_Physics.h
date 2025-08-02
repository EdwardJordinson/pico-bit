#ifndef Engine_Physics_H
#define Engine_Physics_H

#include <Engine/Engine_Coordinates.h>

//Forward declares
//

typedef struct Engine_Manifold
{
    bool Hit;
    Vector2 HitSpot;
    float Depth;
    Vector2 Normal;

} Engine_Manifold;


void Physics_InverseMass();

void Physics_CollisionResolve();


#endif //Engine_Physics_H