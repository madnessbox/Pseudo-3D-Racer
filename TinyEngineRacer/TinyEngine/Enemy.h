#pragma once
#include "Entity.h"

class Enemy : public Entity
{
public:
	Enemy(const Vector& Position, const Vector& Direction)
		: Entity(Position), Direction(Normalize(Direction))
	{
		
	}

	void Update() override;

	Vector Direction;
};