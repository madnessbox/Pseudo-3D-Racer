#pragma once
#include "Collision.h"
#include "Vector.h"

class World;

class Entity
{
public:
	Entity(const Vector& position, unsigned int Color = 0xFFFFFFF);

	unsigned int Color = 0xFFFFFFFF;

	virtual void Update() = 0;
	virtual void Draw();
	void SetColor(unsigned int Color);
	
	Vector position;

	engBoundingBox BoundingBox;
	World* MyWorld;
};