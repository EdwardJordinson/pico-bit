#ifndef Engine_GameObject_H
#define Engine_GameObject_H

#include <Engine/Engine_Coordinates.h>
#include <Engine/Engine_Collision.h>


//Forward declares
typedef struct Engine_EventHandler Engine_EventHandler;
typedef struct Vector2 Vector2;
typedef struct Engine_AABB Engine_AABB;
//

typedef struct Engine_GameObject
{
    int RenderID;
    Engine_Matrix3x2 Transform2D;
    Vector2 Velocity;
    Engine_AABB CollisionShape;
    float Restitution; //Bouncy-ness
    float Mass;

    void (*Update)(struct Engine_GameObject*,float);

} Engine_GameObject;


void GameObject_Initialise();
void GameObject_SetDefault(Engine_GameObject* gameObject);
void GameObject_SetConfiguration(Engine_GameObject* gameObject, Engine_GameObject configObject);
void GameObject_SetPositionXY(Engine_GameObject* gameObject, float xPosition, float yPosition);
void GameObject_SetPositionVector(Engine_GameObject* gameObject, Vector2 vector);
void GameObject_SetUpdateFunction(Engine_GameObject* gameObject, void* updateFunction);


#endif //Engine_GameObject_H