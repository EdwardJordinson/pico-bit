#include <Engine/Engine_Physics.h>
#include <Engine/Engine_Collision.h>


Engine_PhysicsBody PhysicsBody_Initialise()
{
    return (Engine_PhysicsBody){AABB_Initialise(), PhysicsMass_Initialise(), PhysicsMaterial_Initialise(), Matrix3x2_Inititialise(), Vector2_Initialise(), Vector2_Initialise()};
};