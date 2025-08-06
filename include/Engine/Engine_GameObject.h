#ifndef Engine_GameObject_H
#define Engine_GameObject_H

#include <Engine/Engine_Coordinates.h>
#include <Engine/Engine_Collision.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

//Forward declares
typedef struct Engine_EventHandler Engine_EventHandler;
typedef struct Engine_Manifold Engine_Manifold;
typedef struct Vector2 Vector2;
typedef struct Engine_AABB Engine_AABB;
//

typedef struct Engine_GameObject
{
    int renderID;
    Engine_Matrix3x2 Transform2D;
    Vector2 Velocity; //Movement Direction/Speed
    Engine_AABB CollisionShape;
    float Restitution; //Bouncy-ness
    float Mass; //Mass

    void (*update)(struct Engine_GameObject*,float);

} Engine_GameObject;


#endif //Engine_GameObject_H