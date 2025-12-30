#include <Engine/Engine_Physics.h>
#include <Engine/Engine_Math.h>
#include <math.h>


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

Engine_PhysicsManifold PhysicsManifold_CirclexAABB(Engine_Circle* circle, Engine_Matrix3x2 bodyTransform1, Engine_AABB* aabb, Engine_Matrix3x2 bodyTransform2)
{
    Engine_PhysicsManifold output = PhysicsManifold_Initialise();

    Engine_AABB boxPos = AABB_GetPosition(aabb, bodyTransform2);
	//Engine_AABB boxPos = *aabb;
	Vector2 distance = Math_ClampVector2(bodyTransform1.Position, boxPos.minVector, boxPos.maxVector);
	Vector2 ab = Vector2_SubtractVector(bodyTransform1.Position, distance);
	float d2 = Vector2_DotProduct(ab, ab);
	float r2 = circle->radius * circle->radius;

	if (d2 != 0) {
			// shallow (center of circle not inside of AABB)
			float d = sqrtf(d2);
			Vector2 normal = Vector2_Normailised(ab);
			
			output.Hit = true;
			output.Depth = circle->radius - d;
			output.HitSpot = Vector2_MuliplyScalar(Vector2_AddVector(bodyTransform1.Position, normal), d);
			output.Normal = normal;
		} else {
			// deep (center of circle inside of AABB)
			// clamp circle's center to edge of AABB, then form the manifold
			Vector2 mid = Vector2_MuliplyScalar(Vector2_AddVector(boxPos.minVector, boxPos.maxVector), 0.5f);
			Vector2 e = Vector2_MuliplyScalar(Vector2_SubtractVector(boxPos.maxVector, boxPos.minVector), 0.5f);
			Vector2 d = Vector2_SubtractVector(bodyTransform1.Position, mid);
			Vector2 abs_d = Vector2_ABS(d);

			float x_overlap = e.x - abs_d.x;
			float y_overlap = e.y - abs_d.y;

			float depth;
			Vector2 normal;

			if (x_overlap < y_overlap) {
				depth = x_overlap;
				normal = (Vector2){1.0f, 0};
				normal = Vector2_MuliplyScalar(normal, (d.x < 0 ? 1.0f : -1.0f));
			} else {
				depth = y_overlap;
				normal = (Vector2){0, 1.0f};
				normal = Vector2_MuliplyScalar(normal, (d.y < 0 ? 1.0f : -1.0f));
			}

			output.Hit = true;
			output.Depth = circle->radius + depth;
			output.HitSpot = Vector2_MuliplyScalar(Vector2_SubtractVector(bodyTransform1.Position, normal), depth);
			output.Normal = normal;
		}
	return output;
};

Engine_PhysicsManifold PhysicsManifold_AABBxOBB(Engine_AABB box1, Engine_Matrix3x2 bodyTransform1, Engine_OBB box2, Engine_Matrix3x2 bodyTransform2)
{

};

Engine_PhysicsManifold PhysicsManifold_OBBxOBB(Engine_OBB box1, Engine_Matrix3x2 bodyTransform1, Engine_OBB box2, Engine_Matrix3x2 bodyTransform2)
{

};

Engine_PhysicsManifold PhysicsManifold_OBBxCircle(Engine_AABB box1, Engine_Matrix3x2 bodyTransform1, Engine_OBB box2, Engine_Matrix3x2 bodyTransform2)
{

};

Engine_PhysicsManifold PhysicsManifold_CirclexCircle(Engine_AABB box1, Engine_Matrix3x2 bodyTransform1, Engine_OBB box2, Engine_Matrix3x2 bodyTransform2)
{

};