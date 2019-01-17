#include "Follower.h"
#include "Player.h"
#include "MathUtils.h"
#include "Color.h"

void Follower::Update()
{
	float OrbitSpeed = Speed / OrbitRadius;
	OrbitAngle += engDelta() * OrbitSpeed;

	if (PlayerToFollow != nullptr)
	{
		Vector OrbitOrigin = PlayerToFollow->position + Vector(16);
		Vector FollowerOrigin = position + Vector(16);
		Vector DirectionFromPlayer = Normalize(FollowerOrigin - OrbitOrigin) * OrbitRadius;
		Vector DirectionPerpendicular = PerpLeft(DirectionFromPlayer);
		Vector OrbitTarget = RotateVector(DirectionFromPlayer, Deg2Rad(45.f));

		DrawVectorFrom(DirectionFromPlayer, OrbitOrigin, RED);
		DrawVectorFrom(DirectionPerpendicular, OrbitOrigin, GREEN);
		DrawVectorFrom(OrbitTarget, OrbitOrigin, BLUE);

		Vector DirectionToOrbit = Normalize((OrbitOrigin + OrbitTarget - Vector(16) - position));
		position += DirectionToOrbit * Speed * engDelta();
	}
}