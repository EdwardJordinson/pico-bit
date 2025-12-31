#include <Engine/Engine_Coordinates.h>
#include <math.h>



HalfSpace HalfSpace_NewPosition(Vector2 normal, Vector2 position)
{

};

// Compute the distance of a point to a plane.
float HalfSpace_Distance(HalfSpace halfspace, Vector2 position)
{
    return Vector2_DotProduct(halfspace.Normal, position) - halfspace.Distance;
};

Vector2 HalfSpace_Project(HalfSpace halfspace, Vector2 position)
{   
    return Vector2_MuliplyScalar(Vector2_SubtractVector(position, halfspace.Normal), HalfSpace_Distance(halfspace, position));
};

Vector2 HalfSpace_Intersect(HalfSpace halfspace, Vector2 position, Vector2 qosition)
{
	float dq = HalfSpace_Distance(halfspace, position);
	float dp = HalfSpace_Distance(halfspace, qosition);
	return Vector2_AddVector(qosition, Vector2_MuliplyScalar(Vector2_SubtractVector(position, qosition), (dq / (dq - dp))));
};