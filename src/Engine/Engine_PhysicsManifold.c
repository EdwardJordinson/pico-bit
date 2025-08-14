#include <Engine/Engine_Physics.h>


Engine_PhysicsManifold Manifold_Initialise()
{
    return (Engine_PhysicsManifold){false, (Vector2){0.0,0.0}, 0.0, (Vector2){0.0,0.0}};
};
