#pragma once
#include "Entity.h"

class Player;

class Follower : public Entity
{
public:
	Follower(const Vector& Position, Player* PlayerToFollow)
		: Entity(Position), PlayerToFollow(PlayerToFollow)
	{}

	void Update() override;

private:
	float Speed = 200.f;
	float OrbitRadius = 100.f;
	float OrbitAngle = 0.f;
	Player* PlayerToFollow = nullptr;
};