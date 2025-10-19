#include <Engine/Engine_Physics.h>


Engine_PhysicsManifold PhysicsManifold_Initialise()
{
    return (Engine_PhysicsManifold){false, (Vector2){0.0,0.0}, 0.0, (Vector2){0.0,0.0}};
};

Engine_PhysicsManifold PhysicsManifold_AABBxAABB(Vector2 mid_1, Vector2 e1, Vector2 direction, float directionx, float directiony)
{
    Engine_PhysicsManifold output = PhysicsManifold_Initialise();

	Vector2 normal;
	float depth;
	Vector2 p;

	if (directionx < directiony) 
	{
		depth = directionx;
		if (direction.x < 0)
		{
			normal = (Vector2){-1.0f, 0};
			p = Vector2_SubtractVector(mid_1, (Vector2){e1.x, 0.0});
		}
		else
		{
			normal = (Vector2){1.0f, 0};
			p = Vector2_AddVector(mid_1, (Vector2){e1.x, 0.0});
		}
	}
	else
	{
		depth = directiony;
		if (direction.y < 0) 
        {
			normal = (Vector2){0, -1.0f};
			p = Vector2_SubtractVector(mid_1, (Vector2){0, e1.y});
		}
		else
		{
			normal = (Vector2){0, 1.0f};
			p = Vector2_AddVector(mid_1, (Vector2){0, e1.y});
		}
	}

	output.Hit = true;
	output.HitSpot = p;
	output.Depth = depth;
	output.Normal = normal;
	return output;
};

Engine_PhysicsManifold PhysicsManifold_CirclexAABB(Engine_Circle* circle, Engine_AABB* aabb)
{

}