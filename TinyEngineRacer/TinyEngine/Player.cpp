#include "Player.h"
#include "TinyEngine.h"
#include "World.h"
#include "Bullet.h"
#include "Type.h"
#include "Enemy.h"
#include "Color.h"
#include "MathUtils.h"
#include "Ray.h"
#include "Cube.h"

Player::Player(const Vector& position) 
	: Entity(position)
{
}

void Player::Update()
{
	engBoundingBox ScreenBox(0, 0, 800, 600);
	Vector movementDelta;

#pragma region Input
	if (engGetKey(Key::D))
	{
		movementDelta.x += 1.f;
	}
	if (engGetKey(Key::A))
	{
		movementDelta.x -= 1.f;
	}
	if (engGetKey(Key::W))
	{
		movementDelta.y -= 1.f;
	}
	if (engGetKey(Key::S))
	{
		movementDelta.y += 1.f;
	}
	if (movementDelta.x != 0.f || movementDelta.y != 0.f)
	{

		movementDelta = Normalize(movementDelta);
		movementDelta = movementDelta * 400.f * engDelta();

		// Do collision checking with screen
		{
			engBoundingBox DeltaBox = BoundingBox;
			DeltaBox.X = position.x + movementDelta.x;

			if (ScreenBox.Contains(DeltaBox))
				position.x += movementDelta.x;
		}

		{
			engBoundingBox DeltaBox = BoundingBox;
			DeltaBox.Y = position.y + movementDelta.y;

			if (ScreenBox.Contains(DeltaBox))
				position.y += movementDelta.y;
		}
	}

#pragma endregion

	BoundingBox.X = position.x;
	BoundingBox.Y = position.y;

	
	IsColliding = false;
}

void Player::Draw()
{
	Entity::Draw();

	if (IsColliding)
		engSetColor(0xFF0000FF);
	else
		engSetColor(0x00FF00FF);

	engDrawRect(position.x, position.y, 32, 32);
	engSetColor(0xFFFFFFFF);
	engDrawRect(position.x + 8, position.y + 8, 16, 16);
}