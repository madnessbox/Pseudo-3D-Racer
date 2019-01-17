#pragma once
#include "Entity.h"
class Bullet : public Entity
{
public:
	Bullet(const Vector& position, const Vector& direction)
		: Entity(position), direction(direction)
	{
		BoundingBox.Width = 16;
		BoundingBox.Height = 16;
	}
	void Update() override;

private:
	Vector direction;
	
	float LifeTime = 5.f;
};