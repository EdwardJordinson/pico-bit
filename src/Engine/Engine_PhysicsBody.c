#include <Engine/Engine_Physics.h>
#include <Engine/Engine_CollisionShape.h>


Engine_PhysicsBody PhysicsBody_Initialise()
{
    return (Engine_PhysicsBody){
        CollisionShape_Initialise(), 
        PhysicsMass_Initialise(), 
        PhysicsMaterial_Initialise(), 
        Matrix3x2_Inititialise(), 
        Vector2_Initialise(),
        0.0f,
        Vector2_Initialise(),
        0.0f};
};

void PhysicsBody_SetTransform(Engine_PhysicsBody* body, Engine_Matrix3x2 newTransform)
{
    

    Vector2 newPos = Vector2_AddVector(body->Transform2D.Position, newTransform.Position);
    Vector2_SetVector(&body->Transform2D.Position, newPos);
    body->CollisionShape.SetTransform(&body->CollisionShape.Data, newTransform);
};